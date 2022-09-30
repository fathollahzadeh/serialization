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
use bytes::BytesMut;


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
    static mut queues: Vec<ArrayQueue<Vec<u8>>> = vec![];
    static mut queues_size: Vec<ArrayQueue<i32>> = vec![];
    static mut statuses: Vec<bool> = vec![];

    if nodeType == NodeType::LEAF {
        let mut stream = initClient(machineInfo.root(), machineInfo.port()).ok().unwrap();
        let mut pages: Vec<Vec<u8>> = vec![];
        let mut pagesSize: Vec<i32> = vec![];
        reader.readAllPages( &mut pages, &mut pagesSize);

        let mut writer = ObjectWriter::new2(method, machineInfo.nrow(), Const::NETWORK_PAGESIZE as usize);
        let mut index = 0;
        for bb in pages {
            writer.writeToNetworkPage(bb, pagesSize[index], &mut stream.try_clone().unwrap());
            println!("+++++++++++++++++++ {}  {}", index, pagesSize[index]);
            index += 1;
        }

        println!("DDDDDDDDDDDDDDDDDDDDDDDDDDD");
        let mut ack_data = [0 as u8; 1];
        let mut endOfNetwork: i32 = -1;
        let ack = b"1";

        stream.read_exact(&mut ack_data).unwrap();
        println!("ACK read=  1");
        if &ack_data != ack {
            println!("flushToNetwork Err!");
        }
        else {
            println!("SCK write -1");
            stream.write(&endOfNetwork.to_be_bytes()).unwrap();

            println!("ACK read 1");
            stream.read_exact(&mut ack_data).unwrap();
            if &ack_data != ack {
                println!("flushToNetwork Err!");
            }
        }
    } else if nodeType == NodeType::MIDDLE {
        let serverSocket = TcpListener::bind(format!("{}:{}", machineInfo.ip(), machineInfo.port())).unwrap();
        unsafe {
            let mut streams = vec![];

            for i in 0..machineInfo.leaves().len() + 1 {
                let queue = ArrayQueue::new(Const::NETWORK_CLIENT_QUEUE_SIZE);
                let queue_size = ArrayQueue::new(Const::NETWORK_CLIENT_QUEUE_SIZE);
                queues.push(queue);
                queues_size.push(queue_size);
                statuses.push(true);
            }
            for i in 0..machineInfo.leaves().len() {
                let stream = serverSocket.incoming().next().unwrap();
                let stream = stream.unwrap();
                streams.push(stream.try_clone().unwrap());
                let method = reader.method().clone();
                thread::spawn(move || {
                    NetworkReadTask(stream, method, queues.get(i).unwrap(), queues_size.get(i).unwrap());
                    statuses[i] = false;
                });
            }
            thread::spawn(move || {
                let index = queues.len() - 1;
                LocalReadTask(&mut reader, queues.get(index).unwrap(), queues_size.get(index).unwrap());
                statuses[index] = false;
            });

            let mut writer = ObjectWriter::new2(method, machineInfo.getTotalNRow(), Const::NETWORK_PAGESIZE as usize);
            let stream = initClient(machineInfo.root(), machineInfo.port()).ok().unwrap();
            ExternalSortTask(&mut queues, &mut queues_size, &mut statuses,  true, writer, false, Some(&mut stream.try_clone().unwrap()));


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
                let queue_size = ArrayQueue::new(Const::NETWORK_CLIENT_QUEUE_SIZE);
                queues.push(queue);
                queues_size.push(queue_size);
                statuses.push(true);
            }
            for i in 0..machineInfo.leaves().len() {
                let stream = serverSocket.incoming().next().unwrap();
                println!("AAAAAAAAAAA");
                let stream = stream.unwrap();
                streams.push(stream.try_clone().unwrap());
                let method = reader.method().clone();
                thread::spawn(move || {
                    NetworkReadTask(stream, method, queues.get(i).unwrap(), queues_size.get(i).unwrap());
                    statuses[i] = false;
                });
            }
           thread::spawn(move || {
                let index = queues.len() - 1;
                LocalReadTask(&mut reader, queues.get(index).unwrap(), queues_size.get(index).unwrap());
                statuses[index] = false;
            });

            let writer = ObjectWriter::new1(outDataPath, method, machineInfo.getTotalNRow());
            if plan.to_lowercase().eq("d2d") || plan.to_lowercase().eq("m2d") {
                ExternalSortTask(&mut queues, &mut queues_size, &statuses, true, writer, true, None);
            } else {
                ExternalSortTask(&mut queues, &mut queues_size, &statuses, false, writer, false, None);
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

fn NetworkReadTask(mut stream: TcpStream, method: u16, queue: &ArrayQueue<Vec<u8>>, queue_size: &ArrayQueue<i32>) {
    let mut i32_data = [0 as u8; 4];
    let ack = b"1";

    while true {
        stream.write(&ack.clone());
        stream.read_exact(&mut i32_data).unwrap();
        let pageSize = i32::from_be_bytes(i32_data);
        if pageSize == -1 {
            break;
        }
        let mut buffer = vec![0u8; pageSize as usize];
        stream.read_exact(&mut buffer).unwrap();
        while queue.is_full() || queue_size.is_full(){}
        queue.push(buffer);
        queue_size.push(pageSize);
    }
}

fn LocalReadTask(reader: &mut ObjectReader, queue: &ArrayQueue<Vec<u8>>, queue_size: &ArrayQueue<i32>) {
    let mut list: Vec<Vec<u8>> = vec![];
    let mut pagesSize: Vec<i32> = vec![];
    reader.readAllPages(&mut list, &mut pagesSize);
    let mut index = 0;
    for bb in list {
        while queue.is_full() || queue_size.is_full() {}
        queue.push(bb);
        queue_size.push(pagesSize[index]);
        index +=1;
    }
}

fn ExternalSortTask(queues: &mut Vec<ArrayQueue<Vec<u8>>>, queues_size: &mut Vec<ArrayQueue<i32>>, statuses: &Vec<bool>, is_write: bool, mut writer: ObjectWriter, onDisk: bool, stream: Option<&TcpStream>) {
    let numberOfClients = queues.len();
    let mut flag:bool = true;

    while flag {
        flag = false;
        for i in 0..numberOfClients as usize {
            while statuses[i] && (queues[i].is_empty() || queues_size[i].is_empty()){}
            if !queues[i].is_empty() && !queues_size[i].is_empty() {
                if is_write {
                    if onDisk {
                       writer.writeNetworkPageToFile(queues[i].pop().unwrap());
                       queues_size[i].pop().unwrap();
                    }
                    else {
                        writer.writeToNetworkPage(queues[i].pop().unwrap(),queues_size[i].pop().unwrap() ,&mut Option::from(stream.unwrap().try_clone()).unwrap().unwrap());
                    }
                }
                flag = true;
            }
        }
    }
    println!("Network External Sort Transfer: Done!");
    if is_write {
        if onDisk { writer.flushNetworkPageWriter(); }
        else {
            let mut stream = Option::from(stream.unwrap().try_clone()).unwrap().unwrap();
            let mut ack_data = [0 as u8; 1];
            let mut endOfNetwork: i32 = -1;
            let ack = b"1";

            stream.read_exact(&mut ack_data).unwrap();
            if &ack_data != ack {
                println!("flushToNetwork Err!");
            }
            else {
                stream.write(&endOfNetwork.to_be_bytes()).unwrap();
                stream.read_exact(&mut ack_data).unwrap();
                if &ack_data != ack {
                    println!("flushToNetwork Err!");
                }
            }
        }
    }
}