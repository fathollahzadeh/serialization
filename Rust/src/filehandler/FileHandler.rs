use std::collections::HashMap;
use bytes::{BytesMut, BufMut, Buf};
use std::io;
use std::fs::{File, OpenOptions};
use crate::tweetStructs::TweetStatus::TweetStatus;
use std::time::{Duration, Instant};
use std::convert::TryInto;
use std::io::Write;


//#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct FileHandler {
    file_name: String,
    index_file_name: String,
    current_page_number: i64,
    current_offset: i64,
    page_size: i64,
    page_buffer: BytesMut,

    count_object: i64,

    //total number of objects in serialized file:
    total_of_objects: i64,

    //Output: For Writing:
    // randOutStreamRegularFile:Option<RandomAccessFile>,
    outRegularFile: File,//Option<File>,

    ///Output: For Index Writing:
    outIndexFile: File,//Option<File>,


    //Page index:
    page_index: Vec<i64>,

    //Object index:
    object_index: Vec<i64>,

    //Object in each page:
    object_in_each_page: HashMap<i64, i64>,

    //benchmark times:
    io_time: Duration,
    index_time: Duration,

    //Network Experiments:
    network_page_size: i64,

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
            6 => mth = "TOML",
            7 => mth = "Pickle",
            8 => mth = "RON",
            9 => mth = "BSON",
            10 => mth = "Avro",
            11 => mth = "JSON5",
            12 => mth = "Postcard",
            13 => mth = "URL",
            14 => mth = "S-expressions",
            15 => mth = "D-Bus",
            16 => mth = "FlexBuffers",
            _ => { mth = "" }
        }
        let ifn: String = format!("{}.{}", fileName.clone(), "index");
        FileHandler {
            file_name: fileName.clone(),
            index_file_name: ifn.clone(),
            current_page_number: 0,
            current_offset: 0,
            page_size: 256 * 1024,
            page_buffer: BytesMut::with_capacity(256 * 1024), // page size = 256K
            count_object: 0,
            total_of_objects: 0,
            outRegularFile: OpenOptions::new().write(true).create(true).open(fileName).unwrap(),
            outIndexFile: OpenOptions::new().write(true).create(true).open(ifn).unwrap(),
            page_index: vec![],
            object_index: vec![],
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
        let buffer;
        match self.method.as_str() {
            "JSON" => {
                buffer = serde_json::to_string(&object).unwrap();
            }
            "Bincode" => { buffer = "".to_string(); }
            "CBOR" => { buffer = "".to_string(); }
            "YAML" => { buffer = "".to_string(); }
            "MessagePack" => { buffer = "".to_string(); }
            "TOML" => { buffer = "".to_string(); }
            "Pickle" => { buffer = "".to_string(); }
            "RON" => { buffer = "".to_string(); }
            "BSON" => { buffer = "".to_string(); }
            "Avro" => { buffer = "".to_string(); }
            "JSON5" => { buffer = "".to_string(); }
            "Postcard" => { buffer = "".to_string(); }
            "URL" => { buffer = "".to_string(); }
            "S-expressions" => { buffer = "".to_string(); }
            "D-Bus" => { buffer = "".to_string(); }
            "FlexBuffers" => { buffer = "".to_string(); }
            _ => { buffer = "".to_string(); }
        }
        let object_size: i64 = buffer.len().try_into().unwrap();

        //check capacity of the current page size
        //if current page is full should be write to the file and then reset the page
        if ((self.current_offset + object_size + 8) > self.page_size) {

            //Write in file:
            let tmpTime = Instant::now();
            self.outRegularFile.write_all(self.page_buffer.bytes());
            self.io_time += tmpTime.elapsed();

            self.current_page_number += 1;
            self.current_offset = 0;
            self.page_buffer.clear();
        }
        self.page_buffer.put_i64(object_size);
        self.page_buffer.put_slice(buffer.as_bytes());
        self.page_index.push(self.current_page_number);
        self.object_index.push(self.current_offset);
        self.current_offset += object_size;
        self.count_object += 1;
    }

    fn writeIndexToFile(&mut self, index_vector: Vec<i64>) {

        let buffer_size=(index_vector.len()+1)*8;
        let mut buffer:BytesMut= BytesMut::with_capacity(buffer_size);

        buffer.put_i64((index_vector.len()).try_into().unwrap());

        for i in index_vector {
            buffer.put_i64(i);
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

        //Close Index file:
        self.outIndexFile.flush();

        //Close Serialized Data file:
        self.outRegularFile.flush();
    }
}

