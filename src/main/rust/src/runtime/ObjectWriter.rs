use bytes::{BytesMut, BufMut, Buf};
use std::fs::{File, OpenOptions};
use std::hash::Hasher;
use crate::tweetStructs::TweetStatus::TweetStatus;
use std::io::{Read, Write};
use std::net::TcpStream;
use std::process::exit;
use crate::util::Const;

pub struct ObjectWriter {
    outStreamRegularFile: File,
    outIndexFile: File,
    currentPageNumber: u32,
    currentOffset: u32,
    row: u32,
    method: u16,
    pageBuffer: BytesMut,
    rlen: u32,
    pageIndex: Vec<u32>,
    objectIndex: Vec<u32>,
    objectLength: Vec<u32>,
    pagePosition: Vec<u64>,
    currentPagePosition: u64,
}

impl ObjectWriter {
    pub fn new1(fname: &str, method: &str, rlen: u32) -> Self {
        let indexFileName: String = format!("{}.{}", fname.clone(), "index");
        Self {
            outStreamRegularFile: OpenOptions::new().write(true).create(true).open(fname).unwrap(),
            outIndexFile: OpenOptions::new().write(true).create(true).open(indexFileName).unwrap(),
            currentPageNumber: 1,
            currentOffset: 0,
            pageBuffer: BytesMut::with_capacity((2u32 * Const::PAGESIZE) as usize),
            rlen: rlen,
            row: 0,
            pageIndex: vec![],
            objectIndex: vec![],
            objectLength: vec![],
            pagePosition: vec![],
            method: Const::getMethodID(method),
            currentPagePosition: 0,
        }
    }

    pub fn new2(method: &str, rlen: u32, pageSize: usize) -> Self {
        Self {
            outStreamRegularFile: OpenOptions::new().write(true).create(true).open("data/tmp.txt").unwrap(),
            outIndexFile: OpenOptions::new().write(true).create(true).open("data/tmp.txt.index").unwrap(),
            currentPageNumber: 1,
            currentOffset: 0,
            pageBuffer: BytesMut::with_capacity(2 * pageSize),
            rlen: rlen,
            row: 0,
            pageIndex: vec![],
            objectIndex: vec![],
            objectLength: vec![],
            pagePosition: vec![],
            method: Const::getMethodID(method),
            currentPagePosition: 0,
        }
    }

    pub fn serializeObject(&mut self, object: &TweetStatus){
        match self.method {
            Const::JSON => {
                serde_json::to_string(object).unwrap().as_bytes();
            }
            Const::BINCODE => {
                bincode::serialize(object).unwrap().as_slice();
            }
            Const::MESSAGEPACK => {
                rmp_serde::to_vec(object).unwrap().as_slice();
            }
            Const::BSON => {
                let mut buf = Vec::new();
                bson::to_bson(object).unwrap().as_document().unwrap().to_writer(&mut buf).ok();
                buf.as_slice();
            }
            Const::FLEXBUF => {
                flexbuffers::to_vec(object).unwrap().as_slice();
            }
            _ => {}
        }
    }
    pub fn writeObjectToFile(&mut self, object: &TweetStatus) {
        let object_size: u32;
        let mut last_len: u32 = self.pageBuffer.len().try_into().unwrap();
        match self.method {
            Const::JSON => {
                self.pageBuffer.put_slice(serde_json::to_string(object).unwrap().as_bytes());
            }
            Const::BINCODE => {
                self.pageBuffer.put_slice(bincode::serialize(object).unwrap().as_slice());
            }
            Const::MESSAGEPACK => {
                self.pageBuffer.put_slice(rmp_serde::to_vec(object).unwrap().as_slice());
            }
            Const::BSON => {
                let mut buf = Vec::new();
                bson::to_bson(object).unwrap().as_document().unwrap().to_writer(&mut buf).ok();
                self.pageBuffer.put_slice(buf.as_slice());
            }
            Const::FLEXBUF => {
                self.pageBuffer.put_slice(flexbuffers::to_vec(object).unwrap().as_slice());
            }
            _ => {}
        }

        let curren_len: u32 = self.pageBuffer.len().try_into().unwrap();
        object_size = curren_len - last_len;

        //check capacity of the current page size
        //if current page is full should be write to the file
        if curren_len > Const::PAGESIZE {
            let tbuffer = self.pageBuffer.split_to(last_len.try_into().unwrap());
            //Write in file:
            self.outStreamRegularFile.write_all(&tbuffer).ok();
            self.pagePosition.push(self.currentPagePosition);
            self.currentPagePosition += tbuffer.len() as u64;
            self.currentPageNumber += 1;
            last_len = 0;
        }
        self.pageIndex.push(self.currentPageNumber);
        self.objectIndex.push(last_len);
        self.objectLength.push(object_size);
        self.row += 1;
    }

    pub fn writeObjectToNetworkPage(&mut self, object: TweetStatus, stream: &mut TcpStream) {
        let object_size: i32;
        let mut last_len: i32 = self.pageBuffer.len().try_into().unwrap();

        match self.method {
            Const::JSON => {
                let data = serde_json::to_string(&object).unwrap();
                self.pageBuffer.put_i32(data.len() as i32);
                self.pageBuffer.put_slice(data.as_bytes());
            }
            Const::BINCODE => {
                let data = bincode::serialize(&object).unwrap();
                self.pageBuffer.put_i32(data.len() as i32);
                self.pageBuffer.put_slice(data.as_slice());
            }
            Const::MESSAGEPACK => {
                let data = rmp_serde::to_vec(&object).unwrap();
                self.pageBuffer.put_i32(data.len() as i32);
                self.pageBuffer.put_slice(data.as_slice());
            }
            Const::BSON => {
                let mut buf = Vec::new();
                bson::to_bson(&object).unwrap().as_document().unwrap().to_writer(&mut buf).ok();
                self.pageBuffer.put_i32(buf.len() as i32);
                self.pageBuffer.put_slice(buf.as_slice());
            }
            Const::FLEXBUF => {
                let data = flexbuffers::to_vec(&object).unwrap();
                self.pageBuffer.put_i32(data.len() as i32);
                self.pageBuffer.put_slice(data.as_slice());
            }
            _ => {}
        }
        let curren_len: i32 = self.pageBuffer.len() as i32;

        if curren_len > Const::NETWORK_PAGESIZE as i32 {
            let tbuffer = self.pageBuffer.split_to(last_len.try_into().unwrap());
            let mut ack_data = [0 as u8; 1];
            let ack = b"1";
            match stream.read_exact(&mut ack_data) {
                Ok(_) => {
                    if &ack_data != ack {
                        println!("writeObjectToNetworkPage!");
                        return;
                    }
                    stream.write(&last_len.to_be_bytes());
                    stream.write(tbuffer.bytes()).unwrap();
                    last_len = 0;
                }
                _ => {
                    println!("writeObjectToNetworkPage (pattern)!");
                    return;
                }
            }
        }
    }

    pub fn writeToNetworkPage(&mut self, page: Vec<u8>, pageSize: i32, stream: &mut TcpStream) {
        let mut ack_data = [0 as u8; 1];
        let ack = b"1";
        match stream.read_exact(&mut ack_data) {
            Ok(_) => {
                if &ack_data != ack {
                    println!("writeObjectToNetworkPage Bytes!");
                    return;
                }
                stream.write(&pageSize.to_be_bytes()).unwrap();
                stream.write(&page).unwrap();
            }
            _ => {
                println!("writeObjectToNetworkPage Bytes (pattern)!");
                return;
            }
        }
    }

    pub fn writeNetworkPageToFile(&mut self, page: Vec<u8>) {
        //Write in file:
        self.outStreamRegularFile.write_all(&page).ok();
    }


    pub fn writeObjectBufferToFile(&mut self, buffer: &[u8]) {
        let object_size: u32 = buffer.len() as u32;
        let mut last_len: u32 = self.pageBuffer.len().try_into().unwrap();
        self.pageBuffer.put_slice(buffer);
        let curren_len: u32 = self.pageBuffer.len().try_into().unwrap();

        //check capacity of the current page size
        //if current page is full should be write to the file
        if curren_len > Const::PAGESIZE {
            let tbuffer = self.pageBuffer.split_to(last_len.try_into().unwrap());
            //Write in file:
            self.outStreamRegularFile.write_all(&tbuffer).ok();
            self.pagePosition.push(self.currentPagePosition);
            self.currentPagePosition += tbuffer.len() as u64;
            self.currentPageNumber += 1;
            last_len = 0;
        }
        self.pageIndex.push(self.currentPageNumber);
        self.objectIndex.push(last_len);
        self.objectLength.push(object_size);
        self.row += 1;
    }

    pub fn flush(&mut self) {
        self.outStreamRegularFile.write_all(self.pageBuffer.bytes()).ok();
        self.pagePosition.push(self.currentPagePosition);

        //Write PageIndex Vector to the File:
        self.writeIndex32ToFile(self.pageIndex.to_owned());

        //Write objectIndex Vector to the File:
        self.writeIndex32ToFile(self.objectIndex.to_owned());

        //Write objectLength Vector to the File:
        self.writeIndex32ToFile(self.objectLength.to_owned());

        //Write pagePosition  Vector to the File:
        self.writeIndex64ToFile(self.pagePosition.to_owned());

        self.outIndexFile.flush().ok();
        self.outStreamRegularFile.flush().ok();
    }

    pub fn flushToNetwork(&mut self, stream: &mut TcpStream) {
        let mut ack_data = [0 as u8; 1];
        let mut endOfNetwork: i32 = -1;
        let ack = b"1";
        match stream.read_exact(&mut ack_data) {
            Ok(_) => {
                if &ack_data != ack {
                    println!("flushToNetwork!");
                    return;
                }
                stream.write(&self.pageBuffer.len().to_be_bytes());
                stream.write(self.pageBuffer.bytes()).unwrap();

                match stream.read_exact(&mut ack_data) {
                    Ok(_) => {
                        if &ack_data != ack {
                            println!("flushToNetwork!");
                            return;
                        }

                        stream.write(&endOfNetwork.to_be_bytes());

                        match stream.read_exact(&mut ack_data) {
                            Ok(_) => {
                                if &ack_data != ack {
                                    println!("flushToNetwork!");
                                    return;
                                }
                                stream.read_exact(&mut ack_data);
                            }
                            _ => {
                                println!("flushToNetwork (pattern)!");
                                return;
                            }
                        }
                    }
                    _ => {
                        println!("flushToNetwork (pattern)!");
                        return;
                    }
                }
            }
            _ => {
                println!("flushToNetwork (pattern)!");
                return;
            }
        }
    }

    pub fn flushNetworkPageWriter(&mut self) {
        self.outIndexFile.flush().unwrap();
        self.outStreamRegularFile.flush().unwrap();
    }

    fn writeIndex32ToFile(&mut self, index_vector: Vec<u32>) {
        let buffer_size = (self.rlen + 1) * 4;
        let mut buffer: BytesMut = BytesMut::with_capacity(buffer_size as usize);

        buffer.put_u32((index_vector.len()).try_into().unwrap());

        for i in index_vector {
            buffer.put_u32(i);
        }
        self.outIndexFile.write_all(buffer.bytes()).ok();
    }

    fn writeIndex64ToFile(&mut self, index_vector: Vec<u64>) {
        let buffer_size = (self.rlen + 1) * 8;
        let mut buffer: BytesMut = BytesMut::with_capacity(buffer_size as usize);

        buffer.put_u64((index_vector.len()).try_into().unwrap());

        for i in index_vector {
            buffer.put_u64(i);
        }
        self.outIndexFile.write_all(buffer.bytes()).ok();
    }
}