#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

use std::{io, env};
use std::cmp::min;
use crate::runtime::ObjectReader::ObjectReader;
use crate::runtime::ObjectWriter::ObjectWriter;
use crate::tweetStructs::TweetStatus::TweetStatus;
use crate::util::Const::{BATCHSIZE, PAGESIZE};
use std::time::{Duration, Instant};
use std::path::Path;
use std::fs;
use std::fs::metadata;

mod tweetStructs;
mod runtime;
mod util;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let inDataPath: String = args[1].to_string();
    let outDataPath: String = args[2].to_string();
    let nrow: u32 = args[3].parse().unwrap();
    let method: String = args[4].to_string();

    let start = 0;
    let end = outDataPath.find(".").unwrap() as i32;
    let outDataPath: String = outDataPath.chars().skip(start).take(end as usize).collect();

    let exist = Path::new(outDataPath.clone().as_str()).exists();

    if (exist && !metadata(outDataPath.clone()).unwrap().is_dir()) || !exist {
        fs::create_dir(outDataPath.clone());
    }

    let outDataPath = format!("{}/{}", outDataPath.clone(), method.clone());
    let exist = Path::new(outDataPath.clone().as_str()).exists();
    if (exist && !metadata(outDataPath.clone()).unwrap().is_dir()) || !exist {
        fs::create_dir(outDataPath.clone());
    }

    let mut reader = ObjectReader::new1(inDataPath.as_str(), "MessagePack");
    let mut binaryObject =vec![];
    reader.readIO2(0, reader.getRlen(), &mut binaryObject);

    let NUM_THREADS: usize = num_cpus::get();
    let fv = nrow as f32 / NUM_THREADS as f32;
    let blklen = fv.ceil() as u32;

    crossbeam::scope(|scope| {
        let mut index = 0;
        for tweetsChunk in binaryObject.chunks_mut(blklen as usize) {
            let method = method.clone();
            let inDataPath = inDataPath.clone();
            let outDataPath = outDataPath.clone();
            let i = index.clone();
            scope.spawn(move |_| {
                let mut writer = ObjectWriter::new1(format!("{}/{}", outDataPath, i.clone()).as_str(), method.as_str(), tweetsChunk.len() as u32);
                for (i, e) in tweetsChunk.iter_mut().enumerate() {
                    let tweet:TweetStatus = rmp_serde::from_slice(&*e).unwrap();
                    writer.writeObjectToFile(&tweet);
                }
                writer.flush();
            });
            index +=1;
        }

    }).expect("Finished!");
    reader.flush();
    Ok(())
}