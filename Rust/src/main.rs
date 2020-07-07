use std::fs::File;
use std::io::{BufReader, BufRead};
use std::io;
use serde::{Serialize, Deserialize};
use crate::tweetStructs::TweetStatus::TweetStatus;
use crate::filehandler::LogFileHandler::LogFileHandler;
use crate::benchmarks::DataSerialization::DataSerialization;

mod tweetStructs;
mod filehandler;
mod benchmarks;

fn main()  -> io::Result<()>{
    let f = File::open("/home/saeed/Documents/Projects/1-Research/GitHub/serialization/data/tweets_jsonline_1M.txt")?;
    let f = BufReader::new(f);

    let logfile=LogFileHandler::new(String::from("/home/saeed/rustlog.txt"));
    logfile.add_log(true, 1, true, String::from("TweetStatus"), 100.1, 100.1, true);

    DataSerialization("input file name".parse().unwrap(), 1, "out file name".parse().unwrap(), 100, 1, true);

    // for line in f.lines() {
    //     //println!("{}", line.unwrap());
    //
    //     let deserialized:  TweetStatus = serde_json::from_str(&line.unwrap()).unwrap();
    //     println!("-------------------------------------------------------------");
    //     println!("{:?}", deserialized);
    // }

    Ok(())
}





