#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

use std::{io, env};
use crate::runtime::ObjectReader::ObjectReader;
use crate::runtime::ObjectWriter::ObjectWriter;
use crate::tweetStructs::TweetStatus::TweetStatus;
use priority_queue::PriorityQueue;
use std::cmp::Reverse;
use crate::util::ObjectFileIndex::ObjectFileIndex;
use crate::util::Network::Network;

mod tweetStructs;
mod runtime;
mod util;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let inDataPath: &str = args[1].as_str();
    let outDataPath: &str = args[2].as_str();
    let method: &str = args[3].as_str();
    let config: String= args[4].to_string();
    let plan: &str = args[5].as_str();

    let network = Network::new(config);


    Ok(())
}