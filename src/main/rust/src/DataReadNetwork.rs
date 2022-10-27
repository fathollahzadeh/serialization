#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

use std::{io, env};
use std::borrow::Borrow;
use crate::runtime::ObjectReader::ObjectReader;
use crate::runtime::ObjectWriter::ObjectWriter;
use crate::tweetStructs::TweetStatus::TweetStatus;
use priority_queue::PriorityQueue;
use std::cmp::Reverse;
use crate::Const::{NETWORK_PAGESIZE, NodeType};
use crate::util::Const;
use crate::util::ObjectNetworkIndex::ObjectNetworkIndex;
use crate::util::Network::Network;
use std::{thread, time};
use std::net::{TcpListener, TcpStream, Shutdown};
use std::io::{Cursor, Read, Write};
use std::ops::DerefMut;
use std::str::from_utf8;
use bson::{doc, Document};
use byteorder::ReadBytesExt;
use std::sync::atomic::{AtomicUsize, Ordering};
use crossbeam_queue::{ArrayQueue, SegQueue};
use crossbeam_utils::thread::scope;
use rand::{thread_rng, Rng};
use rand::distributions::uniform::SampleBorrow;
use std::sync::{Arc, Mutex};
use std::thread::Thread;


mod tweetStructs;
mod runtime;
mod util;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let inDataPath: &str = args[1].as_str();
    let outDataPath: &str = args[2].as_str();
    let method: &str = args[3].as_str();
    let config: String = args[4].to_string();
    let plan: &str = args[5].as_str();

    let mut network = Network::new(config);
    let mut machineInfo = network.getCurrentMachine();
    let mut reader = ObjectReader::new1(inDataPath, method);
    let mut nodeType = machineInfo.getNodeType();
    static mut queues: Vec<ArrayQueue<Vec<TweetStatus>>> = vec![];
    static mut statuses: Vec<bool> = vec![];

    if nodeType == NodeType::LEAF {
        let stream = initClient(machineInfo.root(), machineInfo.port()).ok().unwrap();
        let mut list: Vec<TweetStatus> = vec![];
        reader.readObjects(0, machineInfo.nrow(), &mut list);
        list.sort_by(|cu, ot| cu.getOrder().cmp(&ot.getOrder()));
        let mut writer = ObjectWriter::new2(method, machineInfo.nrow(), Const::NETWORK_PAGESIZE as usize);
        for rd in list {
            writer.writeObjectToNetworkPage(rd, &mut stream.try_clone().unwrap());
        }
        writer.flushToNetwork(&mut stream.try_clone().unwrap());
    } else if nodeType == NodeType::MIDDLE {
        let serverSocket = TcpListener::bind(format!("{}:{}", machineInfo.ip(), machineInfo.port())).unwrap();
        unsafe {
            let mut streams = vec![];

            for i in 0..machineInfo.leaves().len() + 1 {
                let queue = ArrayQueue::new(Const::NETWORK_CLIENT_QUEUE_SIZE);
                queues.push(queue);
                statuses.push(true);
            }
            for i in 0..machineInfo.leaves().len() {
                let stream = serverSocket.incoming().next().unwrap();
                let stream = stream.unwrap();
                streams.push(stream.try_clone().unwrap());
                let method = reader.method().clone();
                thread::spawn(move || {
                    NetworkReadTask(stream, method, queues.get(i).unwrap());
                    statuses[i] = false;
                });
            }
            thread::spawn(move || {
                let index = queues.len() - 1;
                LocalReadTask(&mut reader, queues.get(index).unwrap());
                statuses[index] = false;
            });

            let mut writer = ObjectWriter::new2(method, machineInfo.getTotalNRow(), Const::NETWORK_PAGESIZE as usize);
            let stream = initClient(machineInfo.root(), machineInfo.port()).ok().unwrap();
            ExternalSortTask(&mut queues, &mut statuses, true, writer, false, Some(&mut stream.try_clone().unwrap()));


            let ack = b"1";
            for stream in streams {
                stream.try_clone().unwrap().write(ack);
            }
        }
    } else if nodeType == NodeType::ROOT {
        let serverSocket = TcpListener::bind(format!("{}:{}", machineInfo.ip(), machineInfo.port())).unwrap();
        unsafe {
            let mut streams = vec![];
            for i in 0..machineInfo.leaves().len() + 1 {
                let queue = ArrayQueue::new(Const::NETWORK_CLIENT_QUEUE_SIZE);
                queues.push(queue);
                statuses.push(true);
            }
            for i in 0..machineInfo.leaves().len() {
                let stream = serverSocket.incoming().next().unwrap();
                let stream = stream.unwrap();
                streams.push(stream.try_clone().unwrap());
                let method = reader.method().clone();
                thread::spawn(move || {
                    NetworkReadTask(stream, method, queues.get(i).unwrap());
                    statuses[i] = false;
                });
            }
            thread::spawn(move || {
                let index = queues.len() - 1;
                LocalReadTask(&mut reader, queues.get(index).unwrap());
                statuses[index] = false;
            });

            let writer = ObjectWriter::new1(outDataPath, method, machineInfo.getTotalNRow());
            if plan.to_lowercase().eq("d2d") || plan.to_lowercase().eq("m2d") {
                ExternalSortTask(&mut queues, &statuses, true, writer, true, None);
            } else {
                ExternalSortTask(&mut queues, &statuses, false, writer, false, None);
            }

            let ack = b"1";
            for stream in streams {
                stream.try_clone().unwrap().write(ack);
            }
        }
    }
    Ok(())
}

fn initClient(ip: &str, port: u16) -> Result<TcpStream, Box<dyn std::error::Error>> {
    let delay = time::Duration::from_secs(1);
    for i in 0..1000 {
        match TcpStream::connect(format!("{}:{}", ip, port)) {
            Ok(mut stream) => {
                return Ok(stream);
            }
            _ => { thread::sleep(delay) }
        }
    }

    Err(Box::from(format!("Client can't start >> {}:{}", ip, port)))
}

fn NetworkReadTask(mut stream: TcpStream, method: u16, queue: &ArrayQueue<Vec<TweetStatus>>) {
    let mut i32_data = [0 as u8; 4];
    let ack = b"1";
    let mut c = 0;

    while true {
        stream.write(&ack.clone());
        stream.read_exact(&mut i32_data).unwrap();
        let pageSize = i32::from_be_bytes(i32_data);
        if pageSize == -1 {
            break;
        }
        let mut relativePosition: usize = 0;
        let mut list: Vec<TweetStatus> = vec![];
        while relativePosition < pageSize as usize {
            stream.read_exact(&mut i32_data).unwrap();
            let objectSize = i32::from_be_bytes(i32_data);
            let mut buffer = vec![0u8; objectSize as usize];
            stream.read_exact(&mut buffer);
            let buff_data = buffer.as_slice();

            match method {
                Const::JSON => {
                    list.push(serde_json::from_slice(buff_data).unwrap());
                }
                Const::BINCODE => {
                    list.push(bincode::deserialize(&buff_data).unwrap())
                }
                Const::MESSAGEPACK => {
                    list.push(rmp_serde::from_slice(&buff_data).unwrap())
                }
                Const::BSON => {
                    let doc = Document::from_reader(&mut Cursor::new(&buff_data[..])).unwrap();
                    let bson_data = bson::bson!(doc);
                    list.push(bson::from_bson(bson_data).unwrap())
                }
                Const::FLEXBUF => {
                    list.push(flexbuffers::from_slice(&buff_data).unwrap())
                }
                _ => {
                    println!("The method is not support!!");
                    return;
                }
            }

            relativePosition = relativePosition + 4 + objectSize as usize;
        }
        while queue.is_full() {}
        c +=list.len();
        queue.push(list);

    }

    println!(" c={}", c);
}

fn LocalReadTask(reader: &mut ObjectReader, queue: &ArrayQueue<Vec<TweetStatus>>) {
    let mut list: Vec<TweetStatus> = vec![];
    let nrow = reader.getRlen();
    reader.readObjects(0, nrow, &mut list);
    list.sort_by(|cu, ot| cu.getOrder().cmp(&ot.getOrder()));
    let mut c = 0;
    for ch in list.chunks_mut(Const::NETWORK_LOCAL_READ_LENGTH as usize) {
        while queue.is_full() {}
        let tmp = ch.to_vec();
        c += tmp.len();
        queue.push(tmp);
    }
    println!("local c={}",c);
}

fn ExternalSortTask(queues: &mut Vec<ArrayQueue<Vec<TweetStatus>>>, statuses: &Vec<bool>, is_write: bool, mut writer: ObjectWriter, onDisk: bool, stream: Option<&TcpStream>) {
    let mut dataList: Vec<TweetStatus> = vec![];
    let numberOfClients = queues.len();
    let mut pageObjectCounter: Vec<u64> = vec![0; numberOfClients];
    let mut queue: PriorityQueue<ObjectNetworkIndex, Reverse<usize>> = PriorityQueue::new();

    // reading objects from the first pages and adding them to a priority queue
    for i in 0..numberOfClients as u32 {
        while queues[i as usize].is_empty() {}
        let mut listReadFromFile = queues[i as usize].pop().unwrap();
        pageObjectCounter[i as usize] = listReadFromFile.len() as u64;
        for rd in listReadFromFile {
            let order = rd.getOrder();
            let objectNetworkIndex = ObjectNetworkIndex::new(rd, i);
            queue.push(objectNetworkIndex, Reverse(order));
        }
    }
    println!("Network External Sort: First page reading is done! ");
    let mut c = 0;
    let mut c1 = 0;
    let mut c2 = 0;
    let mut c3 = 0;
    while !queue.is_empty() {
        let tmpObjectNetworkIndex: ObjectNetworkIndex = queue.pop().unwrap().0;
        let clientNumber = tmpObjectNetworkIndex.getClientIndex() as usize;

        // reduce the number of objects read from that file.
        pageObjectCounter[clientNumber] = pageObjectCounter[clientNumber] - 1;

        // If needed load more objects from files.
        // if zero load the next page from file and add objects.
        if pageObjectCounter[clientNumber] == 0 {
            let mut listReadFromFile: Vec<TweetStatus> = vec![];
            if !queues[clientNumber].is_empty() {
                listReadFromFile = queues[clientNumber].pop().unwrap();
            } else {
                while statuses[clientNumber] && queues[clientNumber].is_empty() {}
                if !queues[clientNumber].is_empty() {
                    listReadFromFile = queues[clientNumber].pop().unwrap();
                }
            }
            if listReadFromFile.len() > 0 {
                pageObjectCounter[clientNumber] = listReadFromFile.len() as u64;
                for rd in listReadFromFile {
                    let order = rd.getOrder();
                    let objectNetworkIndex = ObjectNetworkIndex::new(rd, clientNumber as u32);
                    queue.push(objectNetworkIndex, Reverse(order));

                }
            }
        }
        if is_write {
            if onDisk { writer.writeObjectToFile(&tmpObjectNetworkIndex.getObject()); } else {
                writer.writeObjectToNetworkPage(tmpObjectNetworkIndex.getObject(), &mut Option::from(stream.unwrap().try_clone()).unwrap().unwrap());
            }
        } else {
            dataList.push(tmpObjectNetworkIndex.getObject());
        }
        c +=1;
        if clientNumber == 0 {
            c1 +=1;
        }
        if clientNumber == 1 {
            c2 +=1;
        }
        if clientNumber == 2 {
            c3 +=1;
        }
    }

    println!("Network External Sort: Done! c={}  c1={}  c2={}  c3={}  q1={} q1c={} q2={} q1c={} q3={} q1c={}", c, c1, c2, c3, queues[0].len(), queues[0].capacity(),
             queues[1].len(), queues[1].capacity(),queues[2].len(), queues[2].capacity(),);
    if is_write {
        if onDisk { writer.flush(); } else {
            writer.flushToNetwork(&mut Option::from(stream.unwrap().try_clone()).unwrap().unwrap());
        }
    }
}