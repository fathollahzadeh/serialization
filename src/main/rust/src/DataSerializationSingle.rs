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
    let inDataPath: &str = args[1].as_str();
    let method: &str = args[2].as_str();
    let nrow: u32 = args[3].parse().unwrap();

    let mut reader = ObjectReader::new1(inDataPath, "MessagePack");
    let mut writer = ObjectWriter::new2(method, nrow, PAGESIZE as usize);
    let mut size = BATCHSIZE;
    let mut i: u32 = 0;
    while i < nrow {
        let mut tweets: Vec<TweetStatus> = vec![];
        let rdSize: u32 = reader.readObjects(i, size, &mut tweets);
        for k in 0..rdSize as usize {
            writer.serializeObject(tweets[k].borrow());
        }
        i += rdSize;
        size = min(nrow - i, BATCHSIZE);
    }

    reader.flush();
    Ok(())
}