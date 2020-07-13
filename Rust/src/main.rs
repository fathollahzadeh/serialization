use std::fs::File;
use std::io::{BufReader, BufRead};
use std::{io, env};
use serde::{Serialize, Deserialize};
use crate::tweetStructs::TweetStatus::TweetStatus;
use crate::filehandler::LogFileHandler::LogFileHandler;
use crate::benchmarks::DataSerialization::DataSerialization;
use bytes::{BytesMut, BufMut};
use bytes::Bytes;
use bytebuffer::*;

mod tweetStructs;
mod filehandler;
mod benchmarks;


fn main() -> io::Result<()>{

    let args: Vec<String> = env::args().collect();
    let bench_type=&args[1];

    if bench_type=="write" {
        DataSerialization(args);
    }
    Ok(())
}






// use std::io;
// use positioned_io_preview::{RandomAccessFile, ReadAt};
//
// fn main()  -> io::Result<()>{
// // open a file (note: binding does not need to be mut)
//     let raf = RandomAccessFile::open("tests/pi.txt")?;
//
// // read up to 512 bytes
//     let mut buf = [0; 512];
//     let bytes_read = raf.read_at(2048, &mut buf)?;
//
//     Ok(())
// }