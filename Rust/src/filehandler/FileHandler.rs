use std::collections::HashMap;
use bytes::{BytesMut, BufMut, Buf};
use std::io;
use std::fs::{File, OpenOptions};
use crate::tweetStructs::TweetStatus::TweetStatus;
use std::time::{Duration, Instant};
use std::convert::TryInto;
use std::io::Write;
use std::borrow::Borrow;
use serde::Serialize;


//#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct FileHandler {
    file_name: String,
    index_file_name: String,
    current_page_number: u64,
    current_offset: u64,
    page_size: u64,
    page_buffer: BytesMut,

    count_object: u64,

    //total number of objects in serialized file:
    total_of_objects: u64,

    //Output: For Writing:
    // randOutStreamRegularFile:Option<RandomAccessFile>,
    outRegularFile: File,//Option<File>,

    ///Output: For Index Writing:
    outIndexFile: File,//Option<File>,


    //Page index:
    page_index: Vec<u64>,

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
            3 => mth = "CBOR",
            4 => mth = "YAML",
            5 => mth = "MessagePack",
            6 => mth = "Pickle",
            7 => mth = "RON",
            8 => mth = "BSON",
            9 => mth = "JSON5",
            10 => mth = "FlexBuffers",
            _ => { mth = "" }

        }
        let ifn: String = format!("{}.{}", fileName.clone(), "index");
        FileHandler {
            file_name: fileName.clone(),
            index_file_name: ifn.clone(),
            current_page_number: 0,
            current_offset: 0,
            page_size: 256 * 1024,
            page_buffer: BytesMut::with_capacity(2 * 256 * 1024), // page size = 256K
            count_object: 0,
            total_of_objects: 0,
            outRegularFile: OpenOptions::new().write(true).create(true).open(fileName).unwrap(),
            outIndexFile: OpenOptions::new().write(true).create(true).open(ifn).unwrap(),
            page_index: vec![],
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

        self.current_page_number = 0;

        self.io_time = Duration::new(0, 0);
        self.index_time = Duration::new(0, 0);

        Ok(())
    }
    pub fn appendObjectToFile(&mut self, object: TweetStatus) {
        let object_size: u64;
        let last_len: u64 = self.page_buffer.len().try_into().unwrap();
        match self.method.as_str() {
            "JSON" => {//1
                self.page_buffer.put_slice(serde_json::to_string(&object).unwrap().as_bytes());
            }
            "Bincode" => { //2
                self.page_buffer.put_slice(bincode::serialize(&object).unwrap().as_slice());
            }
            "CBOR" => {//3
                self.page_buffer.put_slice(serde_cbor::to_vec(&object).unwrap().as_slice());
            }
            "YAML" => { //4
                self.page_buffer.put_slice(serde_yaml::to_string(&object).unwrap().as_bytes());
            }
            "MessagePack" => {//5
                self.page_buffer.put_slice(rmp_serde::to_vec(&object).unwrap().as_slice());
            }
             "Pickle" => { //6
                 self.page_buffer.put_slice(serde_pickle::to_vec(&object,false).unwrap().as_slice());
             }
             "RON" => { //7
                 self.page_buffer.put_slice(ron::to_string(&object).unwrap().as_bytes());
             }
             "BSON" => {//8
                   self.page_buffer.put_slice(bson::to_bson(&object).unwrap().to_string().as_bytes());
               }
             "JSON5" => {//9
                 self.page_buffer.put_slice(json5::to_string(&object).unwrap().as_bytes());
             }
             "FlexBuffers" => {//10
                 self.page_buffer.put_slice( flexbuffers::to_vec(&object).unwrap().as_slice());
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
            self.current_page_number += 1;
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

        //Write PageIndex Vector to the File:
        self.writeIndexToFile(self.page_index.to_owned());

        //Write objectIndex Vector to the File:
        self.writeIndexToFile(self.object_index.to_owned());

        //Write objectLength Vector to the File:
        self.writeIndexToFile(self.object_length.to_owned());

        //Close Index file:
        self.outIndexFile.flush();

        //Close Serialized Data file:
        self.outRegularFile.flush();
    }
}

