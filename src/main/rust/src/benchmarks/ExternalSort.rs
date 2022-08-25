use std::io;
use crate::filehandler::FileHandler::FileHandler;
use std::time::{Duration, Instant};
use crate::tweetStructs::TweetStatus::TweetStatus;
use crate::filehandler::LogFileHandler::LogFileHandler;
use std::convert::TryInto;
use crate::util::ObjectFileIndex::ObjectFileIndex;
use priority_queue::PriorityQueue;
use std::hash::BuildHasherDefault;
use std::cmp::Reverse;

pub fn ExternalSort(args: Vec<String>) -> io::Result<()> {
	let fileName: String = args[2].to_string();
	let numberOfFiles: usize = args[3].parse().unwrap();
	let serializationType: i32 = args[4].parse().unwrap();
	let round: i32 = args[5].parse().unwrap();
	let taskset: bool = args[6].parse().unwrap();

	let log_file_name: String = format!("{}{}{}", "bin/benchmark/externalsort/result_rust_externalsort_", round, ".txt");
	let logfile = LogFileHandler::new(String::from(log_file_name));

	////////////////////////////////////////////////
	println!("Start Reading part of the file into RAM");

	let mut file_handler = FileHandler::new(fileName, serializationType);
	file_handler.prepareToRead();

	//get number of objects in file:
	let totalObjectsCount = file_handler.getTotalOfObjects();

	// start of time calculation
	let start = Instant::now();
	let mut io_time: Duration = Duration::new(0, 0);

	//define start position of objects in each file:
	let mut startIndexInEachFile = 0;
	let numberOfObjectsInEachFiles = totalObjectsCount / numberOfFiles as u64;

	for i in 0..numberOfFiles as u64 {
		println!("Reading for file number {}", i);
		startIndexInEachFile = i * numberOfObjectsInEachFiles;
		// define a vector to store read objects from each file:
		let mut m_list_read_from_file: Vec<TweetStatus> = vec![];

		// read objects from file:
		file_handler.getObjectsFromFile(startIndexInEachFile, numberOfObjectsInEachFiles, &mut m_list_read_from_file);

		//Sort:
		m_list_read_from_file.sort_by(|cu, ot| cu.getOrder().cmp(&ot.getOrder()));

		// write the sorted list back to files.
		let tmpStoreFileName: String = format!("{}{}{}{}", "bin/tmp/sorted-", i, "-", serializationType);
		io_time += writeToFiles(m_list_read_from_file, tmpStoreFileName, serializationType);
	}
	io_time += file_handler.getio_time();
	println!("First stage done! ");

	// ///////////////////////////////////////////////////
	//
	// External Sort - Second stage                     //
	//
	// //////////////////////////////////////////////////
	println!("Second Stage ... ");

	// open all of data files and keep them open to read partially.
	let mut fileArray: Vec<FileHandler> = vec![];
	for i in 0..numberOfFiles {
		let sortedFileName: String = format!("{}{}{}{}", "bin/tmp/sorted-", i, "-", serializationType);
		let mut file_handler = FileHandler::new(sortedFileName, serializationType);
		file_handler.prepareToRead();
		fileArray.push(file_handler);
	}
	let mut pageCounter: Vec<u64> = vec![0; numberOfFiles];

	// set all positions to the beginning of files - zero.
	for i in 0..numberOfFiles {
		pageCounter[i] = 0;
	}
	let mut pageObjectCounter: Vec<u64> = vec![0; numberOfFiles];
	let mut readFileObject: Vec<u64> = vec![0; numberOfFiles];

	// type PqType = PriorityQueue<ObjectFileIndex, usize>;
	let mut queue: PriorityQueue<ObjectFileIndex, Reverse<usize>> = PriorityQueue::new();

	// reading objects from the first pages and adding them to a priority queue
	for i in 0..numberOfFiles {
		//get number of objects in the first page

		let n = fileArray.get(i).unwrap().getObjectInEachPage()[&1];
		pageObjectCounter[i] = n;
		readFileObject[i] = n;
		let mut m_list_read_from_file: Vec<TweetStatus> = vec![];
		fileArray[i].getObjectsFromFile(0, n, &mut m_list_read_from_file);

		for j in 0..m_list_read_from_file.len() {
			let objectFileIndex: ObjectFileIndex = ObjectFileIndex::new(m_list_read_from_file[j].clone(), i);
			queue.push(objectFileIndex, Reverse(m_list_read_from_file[j].getOrder()));
		}
	}// End of loop over files

	println!("First page reading is done! ");

	let mut dataToWrite: Vec<TweetStatus> = vec![];

	// reading next pages
	// ###################################################################
	// open final output file.
	let finalFileName: String = format!("{}{}", "bin/tmp/finalSortedFile-", serializationType);
	let mut objectFileOutput = FileHandler::new(finalFileName, serializationType);
	objectFileOutput.prepareToWrite();

	while !queue.is_empty() {
		let tmpObjectFileIndex: ObjectFileIndex = queue.pop().unwrap().0;
		let fileNumber: usize = tmpObjectFileIndex.getFileIndex();

		// reduce the number of objects read from that file.
		pageObjectCounter[fileNumber] = pageObjectCounter[fileNumber] - 1;

		// If needed load more objects from files.
		// if zero load the next page from file and add objects.

		if pageObjectCounter[fileNumber] == 0 && pageCounter[fileNumber] < fileArray[fileNumber].getObjectInEachPage().len() as u64 - 1 {
			// add page counter
			pageCounter[fileNumber] = pageCounter[fileNumber] + 1;
			pageObjectCounter[fileNumber] = fileArray[fileNumber].getObjectInEachPage()[&pageCounter[fileNumber]];

			let mut m_list_read_from_file: Vec<TweetStatus> = vec![];

			fileArray[fileNumber].getObjectsFromFile(readFileObject[fileNumber], pageObjectCounter[fileNumber], &mut m_list_read_from_file);

			readFileObject[fileNumber] = readFileObject[fileNumber] + m_list_read_from_file.len() as u64;

			for j in 0..m_list_read_from_file.len() {
				let objectFileIndex: ObjectFileIndex = ObjectFileIndex::new(m_list_read_from_file[j].clone(), fileNumber);
				queue.push(objectFileIndex, Reverse(m_list_read_from_file[j].getOrder()));
			}
		}

		dataToWrite.push(tmpObjectFileIndex.getObject());

		// Write only of we collected more than 10000 objects
		if dataToWrite.len() > 10000 {
			for t in &dataToWrite {
				//Serialize the TweetStatus object and then write to file:
				objectFileOutput.appendObjectToFile(t.to_owned());
			}
			dataToWrite.clear();
		}
	}

	for t in &dataToWrite {
		//Serialize the TweetStatus object and then write to file:
		objectFileOutput.appendObjectToFile(t.to_owned());
	}
	dataToWrite.clear();

	objectFileOutput.appendObjectToFileFlush();

	io_time += objectFileOutput.getio_time();
	println!("Done!");

	// Close object files.
	for k in 0..numberOfFiles {
		io_time += fileArray[k].getio_time();
	}
	let elapsedSeconds = start.elapsed();
	logfile.add_log(true, serializationType, true, String::from("TweetStatus"), file_handler.getio_time(), elapsedSeconds, taskset);

	Ok(())
}

pub fn writeToFiles(list: Vec<TweetStatus>, filename: String, serializationType: i32) -> Duration {

	// Define file handler for each serialization type:
	let mut file_handler = FileHandler::new(filename, serializationType);
	file_handler.prepareToWrite();

	for t in list {
		//Serialize the TweetStatus object and then write to file:
		file_handler.appendObjectToFile(t);
	}

	file_handler.appendObjectToFileFlush();
	let a = file_handler.getio_time();
	return a;
}

