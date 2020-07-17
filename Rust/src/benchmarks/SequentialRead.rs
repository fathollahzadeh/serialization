use std::io;
use crate::filehandler::FileHandler::FileHandler;
use std::time:: Instant;
use crate::tweetStructs::TweetStatus::TweetStatus;
use crate::filehandler::LogFileHandler::LogFileHandler;

pub fn SequentialRead(args:Vec<String> ) -> io::Result<()>{

    let inFile:String = args[2].to_string();

    let serializationType:i32 = args[3].parse().unwrap();

    //Set output file path
    let from:u64 = args[4].parse().unwrap();

    // set number of tweets:
    let numberofobjects:u64=args[5].parse().unwrap();

    let  round:i32=args[6].parse().unwrap();

    let  taskset:bool= args[7].parse().unwrap();

    let log_file_name:String = format!("{}{}{}{}{}", "bin/benchmark/readobjects/result_rust_readobjects_", numberofobjects, "_", round, ".txt");
    let logfile=LogFileHandler::new(String::from(log_file_name));

    let mut file_handler = FileHandler::new(inFile, serializationType);
    file_handler.prepareToRead();

    let start = Instant::now();
    let objectList:Vec<TweetStatus>=vec![];

    file_handler.getObjectsFromFile(from,numberofobjects,objectList);
    let elapsedSeconds = start.elapsed();
    logfile.add_log(true, serializationType, true, String::from("TweetStatus"), file_handler.getio_time(), elapsedSeconds, taskset);

    Ok(())
}