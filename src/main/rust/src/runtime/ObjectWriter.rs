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

pub struct ObjectWriter {
    outStreamRegularFile:File,
    outIndexFile: File,
    currentPageNumber: u64,
    currentOffset: u64,
    row: u64,
    method: u16,
    pageBuffer:BytesMut,
    rlen: u64,
    pageIndex: Vec<u32>,
    objectIndex: Vec<u32>
}

impl ObjectWriter {

    pub fn new(fname: String, method: String, rlen: u64) -> ObjectWriter{
        
    }

    //ObjectWriter(const string &method, int rlen, int pageSize);
    pub fn new(method: String, rlen: u64, pageSize: i32) -> ObjectWriter{

    }

    // pub fn new(method: String, rlen: u64, pageSize:u32) -> ObjectWriter{
    //
    // }


    // pub fn new(fileName: String, serializationType: i32) -> FileHandler {
    //     let mth;
    //     match serializationType {
    //         1 => mth = "JSON",
    //         2 => mth = "Bincode",
    //         3 => mth = "MessagePack",
    //         4 => mth = "BSON",
    //         5 => mth = "FlexBuffers",
    //         _ => { mth = "" }
    //     }
    //     let ifn: String = format!("{}.{}", fileName.clone(), "index");
    //     FileHandler {
    //         file_name: fileName.clone(),
    //         index_file_name: ifn.clone(),
    //         current_page_number: 1,
    //         current_offset: 0,
    //         page_size: 256 * 1024,
    //         page_buffer: BytesMut::with_capacity(2 * 256 * 1024), // page size = 256K
    //         count_object: 0,
    //         current_page_position: 0,
    //         total_of_objects: 0,
    //         outRegularFile: OpenOptions::new().write(true).create(true).open(fileName).unwrap(),
    //         outIndexFile: OpenOptions::new().write(true).create(true).open(ifn).unwrap(),
    //         page_index: vec![],
    //         page_position: vec![],
    //         object_index: vec![],
    //         object_length: vec![],
    //         object_in_each_page: Default::default(),
    //         io_time: Duration::new(0, 0),
    //         index_time: Duration::new(0, 0),
    //         network_page_size: 0,
    //         serialization_type: serializationType,
    //         method: String::from(mth),
    //
    //     }
    // }

}