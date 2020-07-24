use std::collections::HashMap;
use bytes::{BytesMut, BufMut, Buf, Bytes};
use std::io;
use std::fs::{File, OpenOptions};
use crate::tweetStructs::TweetStatus::TweetStatus;
use std::time::{Duration, Instant};
use std::convert::TryInto;
use std::io::{Write, BufReader, BufRead, Seek, SeekFrom, Read, Cursor};
use std::borrow::Borrow;
use std::cmp::min;
use rand::seq::index::IndexVec;
use std::panic::resume_unwind;
use bson::{Bson, Document, Deserializer, Serializer};
use serde::{Deserialize, Serialize};

pub struct FileHandler {
    file_name: String,
    index_file_name: String,
    current_page_number: u64,
    current_offset: u64,
    page_size: u64,
    page_buffer: BytesMut,
    count_object: u64,

    current_page_position: u64,
    //total number of objects in serialized file:
    total_of_objects: u64,

    //Output: For Writing:
    outRegularFile: File,

    ///Output: For Index Writing:
    outIndexFile: File,

    //Page index:
    page_index: Vec<u64>,

    //Page Position:
    page_position: Vec<u64>,

    //Object index:
    object_index: Vec<u64>,

    object_length: Vec<u64>,

    //Object in each page:
    object_in_each_page: HashMap<u64, u64>,

    //benchmark times:
    io_time: Duration,
    index_time: Duration,

    //Network Experiments:
    network_page_size: u64,

    serialization_type: i32,

    method: String,
}

impl FileHandler {
    pub fn new(fileName: String, serializationType: i32) -> FileHandler {
        let mth;
        match serializationType {
            1 => mth = "JSON",
            2 => mth = "Bincode",
            3 => mth = "MessagePack",
            4 => mth = "BSON",
            5 => mth = "FlexBuffers",
            _ => { mth = "" }
        }
        let ifn: String = format!("{}.{}", fileName.clone(), "index");
        FileHandler {
            file_name: fileName.clone(),
            index_file_name: ifn.clone(),
            current_page_number: 1,
            current_offset: 0,
            page_size: 256 * 1024,
            page_buffer: BytesMut::with_capacity(2 * 256 * 1024), // page size = 256K
            count_object: 0,
            current_page_position: 0,
            total_of_objects: 0,
            outRegularFile: OpenOptions::new().write(true).create(true).open(fileName).unwrap(),
            outIndexFile: OpenOptions::new().write(true).create(true).open(ifn).unwrap(),
            page_index: vec![],
            page_position: vec![],
            object_index: vec![],
            object_length: vec![],
            object_in_each_page: Default::default(),
            io_time: Duration::new(0, 0),
            index_time: Duration::new(0, 0),
            network_page_size: 0,
            serialization_type: serializationType,
            method: String::from(mth),

        }
    }
    pub fn prepareToWrite(&mut self) -> io::Result<()> {
        self.outRegularFile = OpenOptions::new()
            .write(true)
            .create(true)
            .truncate(true)
            .open(&self.file_name).unwrap();


        let index_file_name: String = format!("{}.{}", self.file_name, "index");
        let outIndexFile = Some(OpenOptions::new()
            .write(true)
            .create(true)
            .truncate(true)
            .open(index_file_name).unwrap());

        self.current_page_number = 1;

        self.io_time = Duration::new(0, 0);
        self.index_time = Duration::new(0, 0);

        Ok(())
    }
    pub fn prepareToRead(&mut self) -> io::Result<()> {
        self.outRegularFile = OpenOptions::new()
            .read(true)
            .open(&self.file_name).unwrap();

        self.current_page_number = 0;

        self.readIndexesFromFile();

        self.io_time = Duration::new(0, 0);
        self.index_time = Duration::new(0, 0);

        self.total_of_objects = self.object_index.len().try_into().unwrap();

        //calculate object in each page:
        for u in &self.page_index {
            if !self.object_in_each_page.contains_key(&u) {
                self.object_in_each_page.insert(u.clone(), 0);
            }
            let value = self.object_in_each_page[u] + 1;
            self.object_in_each_page.insert(u.clone(), value);
        }
        Ok(())
    }

    pub fn appendObjectToFile(&mut self, object: TweetStatus) {
        let object_size: u64;
        let mut last_len: u64 = self.page_buffer.len().try_into().unwrap();
        match self.method.as_str() {
            "JSON" => {//1
                self.page_buffer.put_slice(serde_json::to_string(&object).unwrap().as_bytes());
            }
            "Bincode" => { //2
                self.page_buffer.put_slice(bincode::serialize(&object).unwrap().as_slice());
            }
            "MessagePack" => {//3
                self.page_buffer.put_slice(rmp_serde::to_vec(&object).unwrap().as_slice());
            }
            "BSON" => {//4
                let mut buf = Vec::new();
                bson::to_bson(&object).unwrap().as_document().unwrap().to_writer(&mut buf);
                self.page_buffer.put_slice(buf.as_slice());
            }
            "FlexBuffers" => {//5
                self.page_buffer.put_slice(flexbuffers::to_vec(&object).unwrap().as_slice());
            }
            _ => {}
        }

        let curren_len: u64 = self.page_buffer.len().try_into().unwrap();
        object_size = curren_len - last_len;

        //check capacity of the current page size
        //if current page is full should be write to the file
        if curren_len > self.page_size {
            let tbuffer = self.page_buffer.split_to(last_len.try_into().unwrap());
            //Write in file:
            let tmpTime = Instant::now();
            self.outRegularFile.write_all(&tbuffer);
            self.io_time += tmpTime.elapsed();
            self.page_position.push(self.current_page_position);
            self.current_page_position += tbuffer.len() as u64;
            self.current_page_number += 1;
            last_len = 0;
        }
        self.page_index.push(self.current_page_number);
        self.object_index.push(last_len);
        self.object_length.push(object_size);
        self.count_object += 1;
    }
    fn writeIndexToFile(&mut self, index_vector: Vec<u64>) {
        let buffer_size = (index_vector.len() + 1) * 8;
        let mut buffer: BytesMut = BytesMut::with_capacity(buffer_size);

        buffer.put_u64((index_vector.len()).try_into().unwrap());

        for i in index_vector {
            buffer.put_u64(i);
        }

        let tmpTime = Instant::now();
        self.outIndexFile.write_all(buffer.bytes());
        self.io_time += tmpTime.elapsed();
    }
    pub fn appendObjectToFileFlush(&mut self) {

        //Write last page in file:
        let tmpTime = Instant::now();
        self.outRegularFile.write_all(self.page_buffer.bytes());
        self.io_time += tmpTime.elapsed();
        self.page_position.push(self.current_page_position);

        //Write PageIndex Vector to the File:
        self.writeIndexToFile(self.page_index.to_owned());

        //Write objectIndex Vector to the File:
        self.writeIndexToFile(self.object_index.to_owned());

        //Write objectLength Vector to the File:
        self.writeIndexToFile(self.object_length.to_owned());

        //Write objectLength Vector to the File:
        self.writeIndexToFile(self.page_position.to_owned());

        //Close Index file:
        self.outIndexFile.flush();

        //Close Serialized Data file:
        self.outRegularFile.flush();
    }
    pub fn getio_time(&self) -> Duration {
        return self.io_time;
    }
    fn readIndexesFromFile(&mut self) -> io::Result<()> {
        let ifn: String = format!("{}.{}", self.file_name, "index");
        let file = File::open(ifn)?;
        let file_size = file.metadata().unwrap().len();

        let mut reader = BufReader::with_capacity(file_size as usize, file);
        let buf = reader.fill_buf().unwrap();


        let mut index_buffer_init = BytesMut::with_capacity(buf.len());
        index_buffer_init.extend_from_slice(buf);
        let mut index_buffer = index_buffer_init.freeze();

        // get page index from file:
        let index_size = index_buffer.get_u64();
        for u in 1..index_size + 1 {
            self.page_index.push(index_buffer.get_u64());
        }
        // get object index from file:
        let index_size = index_buffer.get_u64();

        for u in 1..index_size + 1 {
            self.object_index.push(index_buffer.get_u64());
        }
        // get object length from file:
        let index_size = index_buffer.get_u64();
        for u in 1..index_size + 1 {
            self.object_length.push(index_buffer.get_u64());
        }

        // get object position from file:
        let index_size = index_buffer.get_u64();
        for u in 1..index_size + 1 {
            self.page_position.push(index_buffer.get_u64());
        }

        Ok(())
    }
    fn readPageFromFile(&mut self, id: u64) {

        //If page is already in RAM: Use from RAM:
        if self.current_page_number == id {
            return;
        }
        //Page not in RAM: Disk IO:
        else {
            let newPosition: u64 = self.page_position[(id - 1) as usize];//(id - 1) * self.page_size;

            // Disk I/O
            let tmpTime = Instant::now();
            self.outRegularFile.seek(SeekFrom::Start(newPosition));
            let mut reader = BufReader::with_capacity(self.page_size as usize, &self.outRegularFile);
            let buffer = reader.fill_buf().unwrap();

            // Time Calculation
            self.io_time += tmpTime.elapsed();

            self.page_buffer = BytesMut::with_capacity(buffer.len());
            self.page_buffer.extend_from_slice(buffer);
        }
    }
    pub fn getObjectsFromFile(&mut self, i: u64, n: u64, objectList: &mut Vec<TweetStatus>) {
        let list_size = min(i + n, self.total_of_objects);

        //Iterate over all objects that you aspire to read.
        for j in i..list_size {
            // get Object page from file:
            let pindex = self.page_index[j as usize];
            self.readPageFromFile(pindex);

            // get Object size:
            let lenght_each_object: u64 = self.object_length[j as usize];
            let start = self.object_index[j as usize];
            let end = start + lenght_each_object;
            let buff_data = self.page_buffer.get(start as usize..end as usize).unwrap();

            let myDeserlizedObject: TweetStatus;

            match self.method.as_str() {
                "JSON" => {

                    myDeserlizedObject = serde_json::from_slice(buff_data).unwrap();
                    objectList.push(myDeserlizedObject);
                }
                "Bincode" => {
                    myDeserlizedObject = bincode::deserialize(&buff_data).unwrap();
                    objectList.push(myDeserlizedObject);
                }
                "MessagePack" => {
                    myDeserlizedObject = rmp_serde::from_read_ref(&buff_data).unwrap();
                    objectList.push(myDeserlizedObject);
                }
                "BSON" => {
                    let doc = Document::from_reader(&mut Cursor::new(&buff_data[..])).unwrap();
                    let bson_data = bson::bson!(doc);
                    myDeserlizedObject = bson::from_bson(bson_data).unwrap();
                    objectList.push(myDeserlizedObject);
                }
                "FlexBuffers" => {
                    myDeserlizedObject = flexbuffers::from_slice(&buff_data).unwrap();
                    objectList.push(myDeserlizedObject);
                }
                _ => {}
            }
        }
    }

    pub fn getTotalOfObjects(&self) -> u64 {
        return self.total_of_objects;
    }

    pub fn getObjectInEachPage(&self) -> HashMap<u64, u64> {
        return self.object_in_each_page.to_owned();
    }
}