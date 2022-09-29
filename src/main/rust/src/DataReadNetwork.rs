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
use std::thread;
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
    let mut queues: Vec<ArrayQueue<Vec<TweetStatus>>> = vec![];
    let mut arc_queues = Arc::new((Mutex::new(queues)));
    let mut statuses: Vec<bool> = vec![true; machineInfo.leaves().len() + 1];
    let mut arc_statuses = Arc::new((Mutex::new(statuses)));
    let mut job = Arc::new(Mutex::new(0 as usize));

    println!("Current Machine IP={}  root={}  port={}", machineInfo.ip(), machineInfo.root(), machineInfo.port());
    if nodeType == NodeType::LEAF {
        println!("LEAF Start !!!!!!!!!!!!!   {}", machineInfo.root());
        let stream = TcpStream::connect("10.10.10.180:9090").unwrap();//format!("{}:{}", machineInfo.root(), machineInfo.port())
        println!("OOOOOOOOOk");
        let mut list: Vec<TweetStatus> = vec![];
        reader.readObjects(0, machineInfo.nrow(), &mut list);
        list.sort_by(|cu, ot| cu.getOrder().cmp(&ot.getOrder()));
        let mut writer = ObjectWriter::new2(method, machineInfo.nrow(), Const::NETWORK_PAGESIZE as usize);
        for rd in list {
            writer.writeObjectToNetworkPage(rd, &mut stream.try_clone().unwrap());
        }
    } else if nodeType == NodeType::MIDDLE {
        println!("MIDDLE Start !!!!!!!!!!!!!11");
        let serverSocket = TcpListener::bind("0.0.0.0:9090").unwrap(); //format!("0.0.0.0:{}", machineInfo.port())

        for i in 0..machineInfo.leaves().len() + 1 {
            let queue = ArrayQueue::new(Const::NETWORK_CLIENT_QUEUE_SIZE);
            arc_queues.lock().unwrap().push(queue);
        }
        crossbeam::scope(|scope| {
            for stream in serverSocket.incoming() {
                let stream = stream.unwrap();
                println!("ACCEPT!!!!!!1");
                scope.spawn(|_| {
                    let index = *job.lock().unwrap();
                    NetworkReadTask(stream, reader.method(), arc_queues.lock().unwrap().get(index).unwrap());
                    let status = &mut arc_statuses.lock().unwrap()[index];
                    *status = false;
                });
                *job.lock().unwrap() += 1;
            }

            scope.spawn(|_| {
                let index = *job.lock().unwrap();
                LocalReadTask(inDataPath.clone(), method.clone(), arc_queues.lock().unwrap().get(index).unwrap());
                let status = &mut arc_statuses.lock().unwrap()[index];
                *status = false;
            });

            let mut writer = ObjectWriter::new2(method, machineInfo.getTotalNRow(), Const::NETWORK_PAGESIZE as usize);
            println!("CCCCCCCCCCCCCCCCCCCCCCCc");

            match TcpStream::connect(format!("{}:{}", machineInfo.root(), machineInfo.port())) {
                Ok(mut stream) => {
                    ExternalSortTask(&arc_queues, &arc_statuses, true, writer, false, Some(&mut stream.try_clone().unwrap()));
                }
                Err(e) => {
                    println!("Failed to connect to root: {}", e);
                }
            }
        }).unwrap();
    } else if nodeType == NodeType::ROOT {
        println!("ROOT Start !!!!!!!!!!!!!11");
        let serverSocket = TcpListener::bind("0.0.0.0:9090").unwrap(); //format!("0.0.0.0:{}", machineInfo.port())
        for i in 0..machineInfo.leaves().len() + 1 {
            let queue = ArrayQueue::new(Const::NETWORK_CLIENT_QUEUE_SIZE);
            arc_queues.lock().unwrap().push(queue);
        }

        crossbeam::scope(|scope| {
            for stream in serverSocket.incoming() {
                println!("ACCEPT!!!!!!1");
                let stream = stream.unwrap();
                scope.spawn(|_| {
                    let index = *job.lock().unwrap();
                    NetworkReadTask(stream, reader.method(), arc_queues.lock().unwrap().get(index).unwrap());
                    let status = &mut arc_statuses.lock().unwrap()[index];
                    *status = false;
                });
                *job.lock().unwrap() += 1;
            }
            scope.spawn(|_| {
                let index = *job.lock().unwrap();
                LocalReadTask(inDataPath.clone(), method.clone(), arc_queues.lock().unwrap().get(index).unwrap());
                let status = &mut arc_statuses.lock().unwrap()[index];
                *status = false;
            });
            println!("CCCCCCCCCCCCCCCCCCCCCCCc");

            let writer = ObjectWriter::new1(outDataPath, method, machineInfo.getTotalNRow());
            if plan.to_lowercase().eq("m2d") {
                ExternalSortTask(&arc_queues, &arc_statuses, true, writer, true, None);
            } else {
                ExternalSortTask(&arc_queues, &arc_statuses, false, writer, false, None);
            }
        }).unwrap();
    }

    Ok(())
}

fn NetworkReadTask(mut stream: TcpStream, method: u16, queue: &ArrayQueue<Vec<TweetStatus>>) {
    let mut ack_data = [0 as u8; 1];
    let mut i32_data = [0 as u8; 4];
    let ack = b"1";

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
        queue.push(list);
    }
}

fn LocalReadTask(inDataPath: &str, method: &str, queue: &ArrayQueue<Vec<TweetStatus>>) {
    let mut reader = ObjectReader::new1(inDataPath, method);
    let mut list: Vec<TweetStatus> = vec![];
    let nrow = reader.getRlen();
    reader.readObjects(0, nrow, &mut list);
    list.sort_by(|cu, ot| cu.getOrder().cmp(&ot.getOrder()));

    let chunks = (nrow as f32 / Const::NETWORK_LOCAL_READ_LENGTH as f32).ceil() as usize;
    for ch in list.chunks_mut(chunks) {
        while queue.is_full() {}
        queue.push(ch.to_vec());
    }
}

fn ExternalSortTask(queues: &Arc<Mutex<Vec<ArrayQueue<Vec<TweetStatus>>>>>, statuses: &Arc<Mutex<Vec<bool>>>, is_write: bool, mut writer: ObjectWriter, onDisk: bool, stream: Option<&TcpStream>) {
    let mut dataList: Vec<TweetStatus> = vec![];
    let numberOfClients = queues.lock().unwrap().len(); //queues.len();
    let mut pageObjectCounter: Vec<u64> = vec![0; numberOfClients];
    let mut queue: PriorityQueue<ObjectNetworkIndex, Reverse<usize>> = PriorityQueue::new();

    // reading objects from the first pages and adding them to a priority queue
    for i in 0..numberOfClients as u32 {
        let mut listReadFromFile = queues.lock().unwrap()[i as usize].pop().unwrap();
        pageObjectCounter[i as usize] = listReadFromFile.len() as u64;
        for rd in listReadFromFile {
            let order = rd.getOrder();
            let objectNetworkIndex = ObjectNetworkIndex::new(rd, i);
            queue.push(objectNetworkIndex, Reverse(order));
        }
    }
    println!("Network External Sort: First page reading is done! ");
    while !queue.is_empty() {
        let tmpObjectNetworkIndex: ObjectNetworkIndex = queue.pop().unwrap().0;
        let clientNumber = tmpObjectNetworkIndex.getClientIndex() as usize;

        // reduce the number of objects read from that file.
        pageObjectCounter[clientNumber] -= 1;

        // If needed load more objects from files.
        // if zero load the next page from file and add objects.
        if pageObjectCounter[clientNumber] == 0 {
            let mut listReadFromFile: Vec<TweetStatus> = vec![];
            if !queues.lock().unwrap().get(clientNumber).unwrap().is_empty() {
                listReadFromFile = queues.lock().unwrap()[clientNumber].pop().unwrap();
            } else {
                while *statuses.lock().unwrap().get(clientNumber).unwrap() && !queues.lock().unwrap().get(clientNumber).unwrap().is_empty() {}
                if !&queues.lock().unwrap().get(clientNumber).unwrap().is_empty() {
                    listReadFromFile = queues.lock().unwrap()[clientNumber].pop().unwrap();
                }
            }
            if listReadFromFile.len() > 0 {
                pageObjectCounter[clientNumber as usize] = listReadFromFile.len() as u64;
                for rd in listReadFromFile {
                    let order = rd.getOrder();
                    let objectNetworkIndex = ObjectNetworkIndex::new(rd, clientNumber as u32);
                    queue.push(objectNetworkIndex, Reverse(order));
                }
            }
        }
        if is_write {
            if onDisk { writer.writeObjectToFile(tmpObjectNetworkIndex.getObject()); } else {
                writer.writeObjectToNetworkPage(tmpObjectNetworkIndex.getObject(), &mut Option::from(stream.unwrap().try_clone()).unwrap().unwrap());
            }
        } else {
            dataList.push(tmpObjectNetworkIndex.getObject());
        }
    }
    println!("Network External Sort: Done!");
    if is_write {
        if onDisk { writer.flush(); } else {
            writer.flushToNetwork(&mut Option::from(stream.unwrap().try_clone()).unwrap().unwrap());
        }
    }
}