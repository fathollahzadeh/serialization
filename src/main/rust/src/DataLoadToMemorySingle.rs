#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

use std::{io, env};
use std::cmp::min;
use crate::runtime::ObjectReader::ObjectReader;
use crate::tweetStructs::TweetStatus::TweetStatus;
use crate::util::Const::BATCHSIZE;

mod tweetStructs;
mod runtime;
mod util;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let inDataPath: &str = args[1].as_str();
    let nrow: u32 = args[2].parse().unwrap();

    let mut reader = ObjectReader::new1(inDataPath, "MessagePack");
    let mut size = BATCHSIZE;
    let mut i: u32 = 0;
    while i < nrow {
        let mut tweets: Vec<TweetStatus> = vec![];
        let rdSize: u32 = reader.readObjects(i, size, &mut tweets);
        i += rdSize;
        size = min(nrow - i, BATCHSIZE);
    }
    reader.flush();
    Ok(())
}