#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

use std::{io, env};
use std::cmp::min;
use crate::runtime::ObjectReader::ObjectReader;
use crate::runtime::ObjectWriter::ObjectWriter;
use crate::tweetStructs::TweetStatus::TweetStatus;
use crate::util::Const::BATCHSIZE;

mod tweetStructs;
mod runtime;
mod util;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let inDataPath: &str = args[1].as_str();
    let outDataPath: &str = args[2].as_str();
    let nrow: u32 = args[3].parse().unwrap();
    let method: &str = args[4].as_str();

    let mut reader = ObjectReader::new1(inDataPath, "MessagePack");
    let mut writer = ObjectWriter::new1(outDataPath, method, nrow);
    let mut size = BATCHSIZE;
    let mut i: u32 = 0;
    while i < nrow {
        let mut tweets: Vec<TweetStatus> = vec![];
        let rdSize: u32 = reader.readObjects(i, size, &mut tweets);
        for tweet in tweets {
            writer.writeObjectToFile(tweet);
        }
        i += rdSize;
        size = min(nrow - i, BATCHSIZE);
    }
    writer.flush();
    reader.flush();
    Ok(())
}