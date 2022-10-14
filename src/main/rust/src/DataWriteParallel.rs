#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

use std::{io, env};
use std::cmp::min;
use std::io::{BufRead, BufReader};
use std::fs::metadata;
use std::path::Path;
use std::fs;
use crate::runtime::ObjectReader::ObjectReader;
use crate::runtime::ObjectWriter::ObjectWriter;
use crate::tweetStructs::TweetStatus::TweetStatus;
use crate::util::Const::BATCHSIZE;

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

    let NUM_THREADS: usize = 1; //num_cpus::get();
    let fv = nrow as f32 / NUM_THREADS as f32;
    let blklen = fv.ceil() as u32;

    crossbeam::scope(|scope| {
        for i in 0..NUM_THREADS as u32 {
            let beginPos = i * blklen;
            let endPos = min((i + 1) * blklen, nrow);
            let inDataPath = inDataPath.clone();
            let method = method.clone();
            let outDataPath = outDataPath.clone();
            scope.spawn(move |_| {
                let mut reader = ObjectReader::new1(inDataPath.as_str(), "MessagePack");
                let mut writer = ObjectWriter::new1(format!("{}/{}", outDataPath, i.clone()).as_str(), method.as_str(), endPos - beginPos + 1);

                let mut size = BATCHSIZE;
                let mut j: u32 = beginPos;
                while j < endPos {
                    let mut tweets: Vec<TweetStatus> = vec![];
                    let rdSize: u32 = reader.readObjects(j, size, &mut tweets);
                    for tweet in tweets {
                        writer.writeObjectToFile(tweet);
                    }
                    j += rdSize;
                    size = min(endPos - j, BATCHSIZE);
                }
                writer.flush();
                reader.flush();
            });
        }
    });
    Ok(())
}