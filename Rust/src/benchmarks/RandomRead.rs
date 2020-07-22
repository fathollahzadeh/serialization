use std::io;
use crate::filehandler::FileHandler::FileHandler;
use std::time:: Instant;
use crate::tweetStructs::TweetStatus::TweetStatus;
use crate::filehandler::LogFileHandler::LogFileHandler;
use std::fs::File;
use std::io::{BufReader, BufRead};
use bytes::{BytesMut, Buf};

pub fn RandomRead(args:Vec<String> ) -> io::Result<()>{

    let inFile:String = args[2].to_string();

    let serializationType:i32 = args[3].parse().unwrap();

    //Set output file path
    let random_list_path:String = args[4].to_string();

    // set number of tweets:
    let cunt_to_read:u64=args[5].parse().unwrap();

    let  round:i32=args[6].parse().unwrap();

    let  taskset:bool= args[7].parse().unwrap();

    let mut objectIndexes:Vec<u64>=vec![];

    // read random data from file
    let f = File::open(&random_list_path)?;
    let f = BufReader::new(f);
    for line in f.lines() {
        objectIndexes.push(line.unwrap().parse().unwrap());
    }


    let log_file_name:String = format!("{}{}{}{}{}", "bin/benchmark/readobjects/result_rust_readobjects_", cunt_to_read, "_", round, ".txt");
    let logfile=LogFileHandler::new(String::from(log_file_name));

    let mut file_handler = FileHandler::new(inFile, serializationType);
    file_handler.prepareToRead();

    let start = Instant::now();
    let mut objectList:Vec<TweetStatus>=vec![];

    for u in objectIndexes {
        file_handler.getObjectsFromFile(u,1, &mut objectList);
    }
    let elapsedSeconds = start.elapsed();
    logfile.add_log(true, serializationType, false, String::from("TweetStatus"), file_handler.getio_time(), elapsedSeconds, taskset);

    Ok(())
}