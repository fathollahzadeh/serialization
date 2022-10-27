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

    let NUM_THREADS: usize = num_cpus::get();
    let fv = nrow as f32 / NUM_THREADS as f32;
    let blklen = fv.ceil() as u32;

    let start = Instant::now();
    crossbeam::scope(|scope| {
        for i in 0..NUM_THREADS as u32 {
            let beginPos = i * blklen;
            let endPos = min((i + 1) * blklen, nrow);
            let inDataPath = inDataPath.clone();
            let method = method.clone();
            scope.spawn(move |_| {
                let start_t = Instant::now();
                let mut reader = ObjectReader::new1(inDataPath.as_str(), "MessagePack");
                let mut writer = ObjectWriter::new2(method.as_str(), endPos - beginPos + 1, PAGESIZE as usize);

                let mut size = BATCHSIZE;
                let mut j: u32 = beginPos;
                let mut sum = 0;
                while j < endPos {
                    let mut tweets: Vec<TweetStatus> = vec![];
                    let rdSize: u32 = reader.readObjects(j, size, &mut tweets);
                    for tweet in tweets {
                        writer.serializeObject(&tweet);
                        sum +=1;
                    }
                    j += rdSize;
                    size = min(endPos - j, BATCHSIZE);
                }
                let duration_t = start_t.elapsed();
                println!("{},{},{:?}", i, sum, duration_t);
            });
        }
    }).expect("Finished!");

    let duration = start.elapsed();
    println!("Time elapsed in expensive_function() is: {:?}", duration);

    Ok(())
}