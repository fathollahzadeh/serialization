// #![allow(non_snake_case)]
// #![allow(dead_code)]
// #![allow(unused_variables)]
//
// use std::{io, env};
// use std::cmp::min;
// use crate::runtime::ObjectReader::ObjectReader;
// use crate::tweetStructs::TweetStatus::TweetStatus;
// use crate::util::Const::{BATCHSIZE, PAGESIZE};
//
// mod tweetStructs;
// mod runtime;
// mod util;
//
// fn main() -> io::Result<()> {
//     let args: Vec<String> = env::args().collect();
//     let inDataPath: String = args[1].to_string();
//     let nrow: u32 = args[2].parse().unwrap();
//
//     let NUM_THREADS: usize = num_cpus::get();
//     let fv = nrow as f32 / NUM_THREADS as f32;
//     let blklen = fv.ceil() as u32;
//
//     crossbeam::scope(|scope| {
//         for i in 0..NUM_THREADS as u32 {
//             let beginPos = i * blklen;
//             let endPos = min((i + 1) * blklen, nrow);
//             let inDataPath = inDataPath.clone();
//             scope.spawn(move |_| {
//                 let mut reader = ObjectReader::new1(inDataPath.as_str(), "MessagePack");
//                 let mut size = BATCHSIZE;
//                 let mut j: u32 = beginPos;
//                 let mut sum = 0;
//                 while j < endPos {
//                     let mut tweets: Vec<TweetStatus> = vec![];
//                     let rdSize: u32 = reader.readObjects(j, size, &mut tweets);
//                     j += rdSize;
//                     size = min(endPos - j, BATCHSIZE);
//                     sum += rdSize;
//                 }
//                 reader.flush();
//
//                 println!("ID={}  sum={}", i, sum);
//             });
//         }
//     }).expect("Finished!");
//
//     Ok(())
// }


#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

use std::{io, env};
use std::cmp::min;
use crate::runtime::ObjectReader::ObjectReader;
use crate::tweetStructs::TweetStatus::TweetStatus;
use crate::util::Const::{BATCHSIZE, PAGESIZE};

mod tweetStructs;
mod runtime;
mod util;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let inDataPath: String = args[1].to_string();
    let nrow: u32 = args[2].parse().unwrap();

    let NUM_THREADS: usize = num_cpus::get();
    let fv = nrow as f32 / NUM_THREADS as f32;
    let blklen = fv.ceil() as u32;

    crossbeam::scope(|scope| {
        for i in 0..NUM_THREADS as u32 {
            let beginPos = i * blklen;
            let endPos = min((i + 1) * blklen, nrow);
            let inDataPath = inDataPath.clone();
            scope.spawn(move |_| {
                let mut reader = ObjectReader::new1(inDataPath.as_str(), "MessagePack");
                let mut size= endPos - beginPos +1;
                let mut tweets: Vec<TweetStatus> = vec![];
                let rdSize: u32 = reader.readObjects(beginPos, size, &mut tweets);

                reader.flush();

                println!("ID={}  sum={}", i, rdSize);
            });
        }
    }).expect("Finished!");

    Ok(())
}