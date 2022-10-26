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
    let outDataPath: &str = args[2].as_str();
    let nrow: u32 = args[3].parse().unwrap();

    let mut writer = ObjectWriter::new1(outDataPath, "MessagePack", nrow);
    let f = File::open(&inDataPath)?;
    let f = BufReader::new(f);
    let mut id = 0;
    for line in f.lines() {
         let mut tweetStatus: TweetStatus = serde_json::from_str(&line.unwrap()).unwrap();
         tweetStatus.set_id(tweetStatus.getId() + id);
          writer.writeObjectToFile(&tweetStatus);
    }
    writer.flush();
    Ok(())
}
