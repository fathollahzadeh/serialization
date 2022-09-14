use bytes::{BytesMut, BufMut, Buf};
use std::fs::{File, OpenOptions};
use crate::tweetStructs::TweetStatus::TweetStatus;
//use std::convert::TryInto;
use std::io::Write;
use crate::util::Const;

pub struct ObjectWriter {
    outStreamRegularFile: File,
    outIndexFile: File,
    currentPageNumber: u32,
    currentOffset: u64,
    row: u64,
    method: u16,
    pageBuffer: BytesMut,
    rlen: u64,
    pageIndex: Vec<u32>,
    objectIndex: Vec<u32>,
    objectLength: Vec<u32>,
    pagePosition: Vec<u64>,
    currentPagePosition: u64,
}

impl ObjectWriter {
    pub fn new1(fname: &str, method: &str, rlen: u64) -> Self {
        let indexFileName: String = format!("{}.{}", fname.clone(), "index");
        Self {
            outStreamRegularFile: OpenOptions::new().write(true).create(true).open(fname).unwrap(),
            outIndexFile: OpenOptions::new().write(true).create(true).open(indexFileName).unwrap(),
            currentPageNumber: 0,
            currentOffset: 0,
            pageBuffer: BytesMut::with_capacity((2 * Const::PAGESIZE) as usize),
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

    // pub fn new2(method: &str, rlen: u64, pageSize: usize) -> Self {
    //     Self {
    //         outStreamRegularFile: None,
    //         outIndexFile: None,
    //         currentPageNumber: 0,
    //         currentOffset: 0,
    //         pageBuffer: BytesMut::with_capacity(2 * pageSize),
    //         rlen: rlen,
    //         row: 0,
    //         pageIndex: vec![],
    //         objectIndex: vec![],
    //         objectLength: vec![],
    //         pagePosition: vec![],
    //         method: Const::getMethodID(method),
    //         currentPagePosition: 0,
    //     }
    // }

    pub fn serializeObject(&mut self, object: TweetStatus) {
        match self.method {
            Const::JSON => {
                self.pageBuffer.put_slice(serde_json::to_string(&object).unwrap().as_bytes());
            }
            Const::BINCODE => {
                self.pageBuffer.put_slice(bincode::serialize(&object).unwrap().as_slice());
            }
            Const::MESSAGEPACK => {
                self.pageBuffer.put_slice(rmp_serde::to_vec(&object).unwrap().as_slice());
            }
            Const::BSON => {
                let mut buf = Vec::new();
                bson::to_bson(&object).unwrap().as_document().unwrap().to_writer(&mut buf).ok();
                self.pageBuffer.put_slice(buf.as_slice());
            }
            Const::FLEXBUF => {
                self.pageBuffer.put_slice(flexbuffers::to_vec(&object).unwrap().as_slice());
            }
            _ => {}
        }
    }

    pub fn writeObjectToFile(&mut self, object: TweetStatus) {
        let object_size: u32;
        let mut last_len: u32 = self.pageBuffer.len().try_into().unwrap();
        match self.method {
            Const::JSON => {
                self.pageBuffer.put_slice(serde_json::to_string(&object).unwrap().as_bytes());
            }
            Const::BINCODE => {
                self.pageBuffer.put_slice(bincode::serialize(&object).unwrap().as_slice());
            }
            Const::MESSAGEPACK => {
                self.pageBuffer.put_slice(rmp_serde::to_vec(&object).unwrap().as_slice());
            }
            Const::BSON => {
                let mut buf = Vec::new();
                bson::to_bson(&object).unwrap().as_document().unwrap().to_writer(&mut buf).ok();
                self.pageBuffer.put_slice(buf.as_slice());
            }
            Const::FLEXBUF => {
                self.pageBuffer.put_slice(flexbuffers::to_vec(&object).unwrap().as_slice());
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