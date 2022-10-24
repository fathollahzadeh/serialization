#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

use std::{io, env};
use std::borrow::Borrow;
use std::cmp::min;
use crate::runtime::ObjectReader::ObjectReader;
use crate::runtime::ObjectWriter::ObjectWriter;
use crate::tweetStructs::TweetStatus::TweetStatus;
use crate::util::Const::{BATCHSIZE, PAGESIZE};

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

    crossbeam::scope(|scope| {
        for i in 0..NUM_THREADS as u32 {
            let beginPos = i * blklen;
            let endPos = min((i + 1) * blklen, nrow);
            let inDataPath = inDataPath.clone();
            let method = method.clone();
            scope.spawn(move |_| {
                let mut reader = ObjectReader::new1(inDataPath.as_str(), "MessagePack");
                let mut writer = ObjectWriter::new2(method.as_str(), endPos - beginPos + 1, PAGESIZE as usize);

                let mut size = BATCHSIZE;
                let mut j: u32 = beginPos;
                while j < endPos {
                    let mut tweets: Vec<TweetStatus> = vec![];
                    let rdSize: u32 = reader.readObjects(j, size, &mut tweets);
                    writer.serializeObject2(tweets);
                    // for k in 0..rdSize as usize {
                    //     writer.serializeObject(tweets[k].borrow());
                    // }
                    j += rdSize;
                    size = min(endPos - j, BATCHSIZE);
                }
                reader.flush();
            });
        }
    }).expect("Finished!");

    Ok(())
}