#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

use std::{io, env};
use crate::runtime::ObjectReader::ObjectReader;
use crate::runtime::ObjectWriter::ObjectWriter;
use crate::tweetStructs::TweetStatus::TweetStatus;
use priority_queue::PriorityQueue;
use std::cmp::Reverse;
use crate::util::ObjectFileIndex::ObjectFileIndex;

mod tweetStructs;
mod runtime;
mod util;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let inDataPath: &str = args[1].as_str();
    let outDataPath: &str = args[2].as_str();
    let method: &str = args[3].as_str();
    let chunkSize: u32 = args[4].parse().unwrap();

    let mut queue: PriorityQueue<ObjectFileIndex, Reverse<usize>> = PriorityQueue::new();
    let mut reader = ObjectReader::new1(inDataPath, method);
    let fileCount = (reader.getRlen() as f32 / chunkSize as f32).ceil() as u32;
    let mut pageObjectCounter: Vec<u32> = vec![0; fileCount as usize];
    let mut readFileObject: Vec<u32> = vec![0; fileCount as usize];
    let mut pageCounter: Vec<u32> = vec![0; fileCount as usize];

    let mut i = 0;
    while i < fileCount && i * chunkSize < reader.getRlen() {
        let listSize = reader.getMaxLen(i*chunkSize, chunkSize);
        let mut readLen = listSize - i*chunkSize;
        let sortedFileName = format!("{}/{}Rust-sorted-{}.bin", outDataPath, method, i);
        let mut writer = ObjectWriter::new1(sortedFileName.as_str(), method, readLen as u32);
        for j in i * chunkSize..listSize {
           writer.writeObjectBufferToFile(reader.readObjectIO(j as usize));
        }
        writer.flush();
        i += 1;
    }

    let mut writer = ObjectWriter::new1(format!("{}/{}Rust-sorted.bin", outDataPath, method).as_str(), method, reader.getRlen());
    for i in 0..fileCount {
        let sortedFileName = format!("{}/{}Rust-sorted-{}.bin", outDataPath, method, i);
        let mut tmpReader = ObjectReader::new1(sortedFileName.as_str(), method);
        let n = tmpReader.getRlen();
         for j in 0..n{
            writer.writeObjectBufferToFile(tmpReader.readObjectIO(j as usize));
         }
        tmpReader.flush();
    }

    writer.flush();
    reader.flush();

    println!("Single-Thread External Sort is Done! ");
    Ok(())
}