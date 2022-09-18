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
    //let mut queue = PriorityQueue::new();
    let mut reader = ObjectReader::new1(inDataPath, method);
    let fileCount = (reader.getRlen() as f32 / chunkSize as f32).ceil() as u32;
    let mut pageObjectCounter: Vec<u32> = vec![0; fileCount as usize];
    let mut readFileObject: Vec<u32> = vec![0; fileCount as usize];
    let mut pageCounter: Vec<u32> = vec![0; fileCount as usize];

    let mut i = 0;
    while i < fileCount && i * chunkSize < reader.getRlen() {
        let mut list: Vec<TweetStatus> = vec![];
        reader.readObjects(i * chunkSize, chunkSize, &mut list);
        list.sort_by(|cu, ot| cu.getOrder().cmp(&ot.getOrder()));

        let mut writer = ObjectWriter::new1(format!("{}/{}Rust-sorted-{}.bin", outDataPath, method, i).as_str(), method, list.len() as u32);
        for tweet in list {
            writer.writeObjectToFile(tweet);
        }
        writer.flush();
        i += 1;
    }

    let mut readerArray: Vec<ObjectReader> = vec![];
    for i in 0..fileCount {
        let sortedFileName = format!("{}/{}Rust-sorted-{}.bin", outDataPath, method, i);
        let reader = ObjectReader::new1(sortedFileName.as_str(), method);
        readerArray.push(reader);
    }

    // reading objects from the first pages and adding them to a priority queue
    for i in 0..fileCount {
        let n = readerArray[i as usize].getObjectInEachPage()[&1];
        let mut rd: Vec<TweetStatus> = vec![];
        readerArray[i as usize].readObjects(0, n, &mut rd);
        pageObjectCounter[i as usize] = n;
        readFileObject[i as usize] = n;
        for tweet in rd {
            let order = tweet.getOrder();
            let objectFileIndex = ObjectFileIndex::new(tweet, i);
            queue.push(objectFileIndex, Reverse(order));
        }
    }
    println!("Single-Thread External Sort: First page reading is done! ");
    let mut writer = ObjectWriter::new1(format!("{}/{}Rust-sorted.bin", outDataPath, method).as_str(), method, reader.getRlen());

    while !queue.is_empty() {
        let tmpObjectFileIndex: ObjectFileIndex = queue.pop().unwrap().0;
        let fileNumber = tmpObjectFileIndex.getFileIndex() as usize;
        // reduce the number of objects read from that file.
        pageObjectCounter[fileNumber] = pageObjectCounter[fileNumber] - 1;

        //If needed load more objects from files.
        //if zero load the next page from file and add objects.
        if pageObjectCounter[fileNumber] == 0 && pageCounter[fileNumber] < readerArray[fileNumber].getObjectInEachPage().len() as u32 - 1 {
            // add page counter
            pageCounter[fileNumber] = pageCounter[fileNumber] + 1;
            pageObjectCounter[fileNumber] = readerArray[fileNumber].getObjectInEachPage()[&pageCounter[fileNumber]];

            let mut rd: Vec<TweetStatus> = vec![];
            let rdLen = readerArray[fileNumber].readObjects(readFileObject[fileNumber], pageObjectCounter[fileNumber], &mut rd);
            readFileObject[fileNumber] += rdLen;

            for tweet in rd {
                let order = tweet.getOrder();
                let objectFileIndex = ObjectFileIndex::new(tweet, fileNumber as u32);
                queue.push(objectFileIndex, Reverse(order));
            }
        }
        writer.writeObjectToFile(tmpObjectFileIndex.getObject());
    }
    writer.flush();
    reader.flush();

    println!("Single-Thread External Sort is Done! ");
    Ok(())
}