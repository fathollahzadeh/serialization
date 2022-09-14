use bytes::{BytesMut, BufMut, Buf};
use std::io;
use std::fs::{File, OpenOptions};
use crate::tweetStructs::TweetStatus::TweetStatus;
use std::io::{BufReader, BufRead, Seek, SeekFrom, Read, Cursor, Write};
use std::cmp::min;
use std::collections::HashMap;
use rand::seq::index::IndexVec;
use std::panic::resume_unwind;
use bson::{Bson, Document, Deserializer, Serializer};
use serde::{Deserialize, Serialize};
use crate::util::Const;
use crate::util::Const::PAGESIZE;

pub struct ObjectReader {
    currentPageNumber: u32,
    currentOffset: u32,
    row: u32,
    rlen: u32,
    method: u16,
    pageBuffer: BytesMut,
    objectInEachPage: HashMap<u32, u32>,
    inStreamRegularFile: File,
    pageIndex: Vec<u32>,
    objectIndex: Vec<u32>,
    objectLength: Vec<u32>,
    pagePosition: Vec<u64>,
    currentPagePosition: u64,
}

impl ObjectReader {
    pub fn new1(fname: &str, method: &str) -> Self {
        let mut tmpPageIndex: Vec<u32> = vec![];
        let mut tmpObjectIndex: Vec<u32> = vec![];
        let mut tmpObjectLength: Vec<u32> = vec![];
        let mut tmpPagePosition: Vec<u64> = vec![];

        ObjectReader::readIndexesFromFile(&mut tmpPageIndex, &mut tmpObjectIndex, &mut tmpObjectLength, &mut tmpPagePosition, fname.clone()).ok();
        Self {
            inStreamRegularFile: OpenOptions::new().read(true).open(fname).unwrap(),
            currentPageNumber: 0,
            currentOffset: 0,
            pageBuffer: BytesMut::with_capacity((2 * Const::PAGESIZE) as usize),
            rlen: tmpPageIndex.len().try_into().unwrap(),
            row: 0,
            pageIndex: tmpPageIndex,
            objectIndex: tmpObjectIndex,
            objectLength: tmpObjectLength,
            pagePosition: tmpPagePosition,
            method: Const::getMethodID(method),
            currentPagePosition: 0,
            objectInEachPage: Default::default(),
        }
    }

    fn readIndexesFromFile(pageIndex: &mut Vec<u32>, objectIndex: &mut Vec<u32>, objectLength: &mut Vec<u32>, pagePosition: &mut Vec<u64>, fname: &str) -> io::Result<()> {
        let indexFileName: String = format!("{}.{}", fname, "index");
        let mut file = File::open(indexFileName)?;
        let file_size = file.metadata().unwrap().len();

        let mut reader = BufReader::with_capacity(file_size as usize, file);
        let buf = reader.fill_buf().unwrap();

        let mut index_buffer_init = BytesMut::with_capacity(buf.len());
        index_buffer_init.extend_from_slice(buf);
        let mut index_buffer = index_buffer_init.freeze();

        // get page index from file:
        let index_size = index_buffer.get_u32();
        for u in 1..index_size + 1 {
            pageIndex.push(index_buffer.get_u32());
        }
        // get object index from file:
        let index_size = index_buffer.get_u32();

        for u in 1..index_size + 1 {
            objectIndex.push(index_buffer.get_u32());
        }
        // get object length from file:
        let index_size = index_buffer.get_u32();
        for u in 1..index_size + 1 {
            objectLength.push(index_buffer.get_u32());
        }

        // get object position from file:
        let index_size = index_buffer.get_u64();
        for u in 1..index_size + 1 {
            pagePosition.push(index_buffer.get_u64());
        }
        file.flush();
        Ok(())
    }

    //int readObjects(int i, int n, TweetStatus ** objectList);
    pub fn readObjects(&mut self, i: u32, n: u32, objectList: &mut Vec<TweetStatus>) -> u32 {
        let listSize = min(i + n, self.rlen);
        let mut index = 0;
        for j in i..listSize {
            objectList.push(self.readObject(j as usize).unwrap());
            index += 1;
        }
        return index;
    }

    pub fn readObject(&mut self, i: usize) -> Result<TweetStatus, Box<dyn std::error::Error>> {
        let pindex = self.pageIndex[i];
        self.readPageFromFile(pindex);

        // get Object size:
        let lenght_each_object: u32 = self.objectLength[i];
        let start = self.objectIndex[i];
        let end = start + lenght_each_object;
        let buff_data = self.pageBuffer.get(start as usize..end as usize).unwrap();

        match self.method {
            Const::JSON => {
                Ok(serde_json::from_slice(buff_data).unwrap())
            }
            Const::BINCODE => {
                Ok(bincode::deserialize(&buff_data).unwrap())
            }
            Const::MESSAGEPACK => {
                Ok(rmp_serde::from_slice(&buff_data).unwrap())
            }
            Const::BSON => {
                let doc = Document::from_reader(&mut Cursor::new(&buff_data[..])).unwrap();
                let bson_data = bson::bson!(doc);
                Ok(bson::from_bson(bson_data).unwrap())
            }
            Const::FLEXBUF => {
                Ok(flexbuffers::from_slice(&buff_data).unwrap())
            }
            _ => {
                Err(Box::from("The method is not support!!"))
            }
        }
    }

    fn readPageFromFile(&mut self, id: u32) {
        //If page is already in RAM: Use from RAM:
        if self.currentPageNumber == id {
            return;
        }
        //Page not in RAM: Disk IO:
        else {
            let newPosition: u64 = self.pagePosition[(id - 1) as usize];
            self.inStreamRegularFile.seek(SeekFrom::Start(newPosition));
            let mut reader = BufReader::with_capacity(PAGESIZE as usize, &self.inStreamRegularFile);
            let buffer = reader.fill_buf().unwrap();
            self.pageBuffer = BytesMut::with_capacity(buffer.len());
            self.pageBuffer.extend_from_slice(buffer);
        }
    }

    pub fn flush(&mut self){
        self.inStreamRegularFile.flush();
    }
}