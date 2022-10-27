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

mod tweetStructs;
mod runtime;
mod util;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let inDataPath: String = args[1].to_string();
    let method: String = args[2].to_string();
    let nrow: u32 = args[3].parse().unwrap();

    let mut reader = ObjectReader::new1(inDataPath.as_str(), "MessagePack");
    let mut binaryObject =vec![];
    reader.readIO2(0, reader.getRlen(), &mut binaryObject);

    let NUM_THREADS: usize = num_cpus::get();
    let fv = nrow as f32 / NUM_THREADS as f32;
    let blklen = fv.ceil() as u32;

    crossbeam::scope(|scope| {
        for tweetsChunk in binaryObject.chunks_mut(blklen as usize) {
            let method = method.clone();
            scope.spawn(move |_| {
                let mut writer = ObjectWriter::new2(method.as_str(), tweetsChunk.len() as u32, PAGESIZE as usize);
                for (i, e) in tweetsChunk.iter_mut().enumerate() {
                    let tweet:TweetStatus = rmp_serde::from_slice(&*e).unwrap();
                    writer.serializeObject(&tweet);
                }
            });
        }
    }).expect("Finished!");
    reader.flush();
    Ok(())
}

