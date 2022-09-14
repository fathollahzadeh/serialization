#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

use std::{io, env};
use std::cmp::min;
use std::fs::File;
use std::io::{BufRead, BufReader};
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
    let seqRand: &str = args[3].as_str();
    let nrow: u32 = args[4].parse().unwrap();

    let mut reader = ObjectReader::new1(inDataPath, method);
    if seqRand.to_lowercase().eq("sequential") {
        reader.readIO(0, nrow);
    }
    else {
        let randomDataPath: &str = args[5].as_str();
        let infile = File::open(randomDataPath)?;
        let f = BufReader::new(infile);
        for line in f.lines() {
            reader.readObjectIO(line.unwrap().parse().unwrap());
        }
    }
    reader.flush();
    Ok(())
}