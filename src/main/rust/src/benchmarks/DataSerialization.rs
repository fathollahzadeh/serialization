use std::fs::File;
use std::io::{BufReader, BufRead};
use std::io;
use crate::filehandler::FileHandler::FileHandler;
use std::time::{Duration, Instant};
use crate::tweetStructs::TweetStatus::TweetStatus;
use crate::filehandler::LogFileHandler::LogFileHandler;


pub fn DataSerialization(args: Vec<String>) -> io::Result<()> {
	let mut inputFile: String = args[2].to_string();

	let serializationType: i32 = args[3].parse().unwrap();

	//Set output file path
	let mut outFile: String = args[4].to_string();

	// set number of tweets:
	let numberOfTweets: i64 = args[5].parse().unwrap();

	let round: i32 = args[6].parse().unwrap();

	let taskset: bool = args[7].parse().unwrap();

	let log_file_name: String = format!("{}{}{}{}{}", "bin/benchmark/writeobjects/result_rust_writeobjects_", numberOfTweets, "_", round, ".txt");
	let logfile = LogFileHandler::new(String::from(log_file_name));

	let mut file_handler = FileHandler::new(outFile, serializationType);
	file_handler.prepareToWrite();

	let mut elapsedSeconds: Duration = Duration::new(0, 0);

	let mut eof: bool = false;
	let mut nor = 0;
	while !eof {
		let f = File::open(&inputFile)?;
		let f = BufReader::new(f);
		for line in f.lines() {
			let tweetStatus: TweetStatus = serde_json::from_str(&line.unwrap()).unwrap();
			let start = Instant::now();
			file_handler.appendObjectToFile(tweetStatus);
			let duration = start.elapsed();
			elapsedSeconds += duration;

			nor += 1;
			if nor >= numberOfTweets {
				eof = true;
				break;
			}
		}
	}
	// Finalize and close all open files:
	file_handler.appendObjectToFileFlush();

	logfile.add_log(false, serializationType, true, String::from("TweetStatus"), file_handler.getio_time(), elapsedSeconds, taskset);

	Ok(())
}
