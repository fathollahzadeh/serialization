#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

use std::{io, env};
use std::fs::File;
use std::io::{BufRead, BufReader};
use crate::runtime::ObjectWriter::ObjectWriter;
use crate::tweetStructs::TweetStatus::TweetStatus;

mod tweetStructs;
mod runtime;
mod util;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let inDataPath: &str = args[1].as_str();
    let method: &str = args[2].as_str();
    let nrow: u64 = args[3].parse().unwrap();

    let mut writer = ObjectWriter::new2(method, nrow, );
    let f = File::open(&inDataPath)?;
    let f = BufReader::new(f);
    for line in f.lines() {
        let tweetStatus: TweetStatus = serde_json::from_str(&line.unwrap()).unwrap();
        writer.writeObjectToFile(tweetStatus);
    }
    writer.flush();
    Ok(())
}