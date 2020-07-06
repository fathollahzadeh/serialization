use std::fs::File;
use std::io::{BufReader, BufRead};
use std::io;
use serde::{Serialize, Deserialize};
use crate::tweetStructs::TweetStatus::TweetStatus;

mod tweetStructs;

fn main()  -> io::Result<()>{
    let f = File::open("/home/saeed/Documents/Projects/1-Research/GitHub/serialization/data/tweets_jsonline_1M.txt")?;
    let f = BufReader::new(f);

    for line in f.lines() {
        //println!("{}", line.unwrap());

        let deserialized:  TweetStatus = serde_json::from_str(&line.unwrap()).unwrap();
       // println!("-------------------------------------------------------------");
        //println!("{:?}", deserialized);
    }

    Ok(())
}



