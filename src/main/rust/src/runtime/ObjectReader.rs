use bytes::{BytesMut, BufMut, Buf};
use std::io;
use std::fs::{File, OpenOptions};
use crate::tweetStructs::TweetStatus::TweetStatus;
use std::io::{BufReader, BufRead, Seek, SeekFrom, Read, Cursor};
use std::cmp::min;
use std::collections::HashMap;
use rand::seq::index::IndexVec;
use std::panic::resume_unwind;
use bson::{Bson, Document, Deserializer, Serializer};
use serde::{Deserialize, Serialize};
use crate::util::Const;

pub struct ObjectReader {
    currentPageNumber: u32,
    currentOffset: u64,
    row: u64,
    rlen: u64,
    method: u16,
    pageBuffer: BytesMut,
    objectInEachPage: HashMap<u64, u64>,
    inStreamRegularFile: Option<File>,
    pageIndex: Vec<u32>,
    objectIndex: Vec<u32>,
    objectLength: Vec<u32>,
    pagePosition: Vec<u64>,
    currentPagePosition: u64,
}

impl ObjectReader {
    pub fn new1(&mut self, fname: &str, method: &str) -> Self {
        ObjectReader::readIndexesFromFile(pageIndex, self.objectIndex, self.objectLength, self.pagePosition, fname.clone());
        Self {
            inStreamRegularFile: Option::from(OpenOptions::new().read(true).open(fname).unwrap()),
            currentPageNumber: 0,
            currentOffset: 0,
            pageBuffer: BytesMut::with_capacity((2 * Const::PAGESIZE) as usize),
            rlen: rlen,
            row: 0,
            pageIndex: ObjectReader:: vec![],
            objectIndex: vec![],
            objectLength: vec![],
            pagePosition: vec![],
            method: Const::getMethodID(method),
            currentPagePosition: 0,
            objectInEachPage: Default::default(),
        }

    }

    fn readIndexesFromFile(mut pageIndex: Vec<u32>, mut objectIndex: Vec<u32>, mut objectLength: Vec<u32>, mut pagePosition: Vec<u64>, fname: &str) {
        let indexFileName: String = format!("{}.{}", fname, "index");
        let file = File::open(indexFileName)?;
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
    }
}

//self.outRegularFile = OpenOptions::new()
// 			.read(true)
// 			.open(&self.file_name).unwrap();
//
// 		self.current_page_number = 0;
//
// 		self.readIndexesFromFile();
//
// 		self.io_time = Duration::new(0, 0);
// 		self.index_time = Duration::new(0, 0);
//
// 		self.total_of_objects = self.object_index.len().try_into().unwrap();
//
// 		//calculate object in each page:
// 		for u in &self.page_index {
// 			if !self.object_in_each_page.contains_key(&u) {
// 				self.object_in_each_page.insert(u.clone(), 0);
// 			}
// 			let value = self.object_in_each_page[u] + 1;
// 			self.object_in_each_page.insert(u.clone(), value);
// 		}
// 		Ok(())

// ObjectReader(const string & fname, const string &method);

// long currentPageNumber;
//     int currentOffset;
//     int row;
//     int rlen;
//     int method;
//     char *pageBuffer;
//     int *pageIndex;
//     int *objectIndex;
//     int *objectLength;
//     map<int, int> objectInEachPage;
//     ifstream inStreamRegularFile;
