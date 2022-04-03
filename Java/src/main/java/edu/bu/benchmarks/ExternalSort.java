package edu.bu.benchmarks;

import edu.bu.filehandler.FileHandler;
import edu.bu.filehandler.LogFileHandler;
import edu.bu.tweet.TweetStatus;
import edu.bu.util.RootData;
import edu.bu.util.ObjectFileIndex;
import org.apache.log4j.PropertyConfigurator;
import java.util.List;
import java.util.Properties;
import java.util.Collections;
import java.util.ArrayList;
import java.util.PriorityQueue;

public class ExternalSort {

	private String fileName;
	private int numberOfFiles;
	private int serializationType;
	private long numberOfObjectsInEachFiles;
	private String logFileName;
	private boolean taskset;

	// define variables for calculate bench time:
	private double ioTime = 0;

	public static void main(String[] args) {

		Properties prop = new Properties();

		PropertyConfigurator.configure(prop);
		prop.setProperty("log4j.appender.WORKLOG.File", "log4j.properties");

		PropertyConfigurator.configure("log4j.properties");

		ExternalSort externalSort = new ExternalSort();
		externalSort.fileName = args[0];
		externalSort.numberOfFiles = Integer.parseInt(args[1]);
		externalSort.serializationType = Integer.parseInt(args[2]);
		int round = Integer.parseInt(args[3]);
		externalSort.taskset = Boolean.parseBoolean(args[4]);
		externalSort.logFileName = "bin/benchmark/externalsort/result_java_externalsort_" + round + ".txt";

		externalSort.runTheExternalSort();
	}

	private void runTheExternalSort() {

		// Get a Runtime object
		Runtime runTime = Runtime.getRuntime();

		System.out.println("Start Reading part of the file into RAM");

		FileHandler fileHandler = new FileHandler(fileName, serializationType);
		fileHandler.prepareToRead();

		//get number of objects in file:
		long totalObjectsCount = fileHandler.getTotalOfObjects();

		long sortTime = 0;

		// start of time calculation
		long startTime = System.nanoTime();

		//define start position of objects in each file:
		long startIndexInEachFile = 0;
		numberOfObjectsInEachFiles = totalObjectsCount / numberOfFiles;
		for(int i = 0; i < numberOfFiles; i++) {

			System.out.println("Reading for file number " + i);

			startIndexInEachFile = i * numberOfObjectsInEachFiles;

			// define a vector to store read objects from each file:
			List<RootData> m_list_read_from_file;

			// read objects from file:
			m_list_read_from_file = fileHandler.getObjectsFromFile(startIndexInEachFile, numberOfObjectsInEachFiles);

			// Sort the data
			long tmpTime = System.nanoTime();

			//Sort:
			Collections.sort(m_list_read_from_file);

			// Sort Time Calculation
			sortTime += System.nanoTime() - tmpTime;

			// write the sorted list back to files.
			String tmpStoreFileName = "bin/tmp/sorted-" + i + "-" + serializationType;
			writeToFiles(m_list_read_from_file, tmpStoreFileName);
			m_list_read_from_file.clear();
			// activate the garbage collector
			runTime.gc();

		}
		this.ioTime += fileHandler.getIoTime();
		System.out.println("First stage done! ");
		// ///////////////////////////////////////////////////
		//
		// External Sort - Second stage //
		//
		// //////////////////////////////////////////////////
		System.out.println("Second Stage ... ");

		// open all of data files and keep them open to read partially.
		List<FileHandler> fileArray = new ArrayList<>();
		for(int i = 0; i < numberOfFiles; ++i) {
			String sortedFileName = "bin/tmp/sorted-" + i + "-" + serializationType;
			FileHandler tmpFileHandler = new FileHandler(sortedFileName, serializationType);
			tmpFileHandler.prepareToRead();
			fileArray.add(tmpFileHandler);
		}

		int[] pageCounter = new int[numberOfFiles];
		// set all positions to the beginning of files - zero.
		for(int i = 0; i < numberOfFiles; i++) {
			pageCounter[i] = 0;
		}

		long[] pageObjectCounter = new long[numberOfFiles];

		long[] readFileObject = new long[numberOfFiles];

		PriorityQueue<ObjectFileIndex> queue = new PriorityQueue<ObjectFileIndex>();

		// reading objects from the first pages and adding them to a priority queue
		for(int i = 0; i < numberOfFiles; i++) {

			//get number of objects in the first page
			long n = fileArray.get(i).getObjectInEachPage().get(0L);

			pageObjectCounter[i] = n;

			readFileObject[i] = n;

			List<RootData> m_list_read_from_file;
			m_list_read_from_file = fileArray.get(i).getObjectsFromFile(0, n);

			for(int j = 0; j < m_list_read_from_file.size(); ++j) {
				ObjectFileIndex objectFileIndex = new ObjectFileIndex(i, m_list_read_from_file.get(j));
				queue.add(objectFileIndex);
			}

		}// End of loop over files

		System.out.println("First page reading is done! ");

		// activate the garbage collector
		runTime.gc();

		List<RootData> dataToWrite = new ArrayList<>();

		// reading next pages
		// open final output file.
		FileHandler objectFileOutput = new FileHandler("bin/tmp/finalSortedFile-" + serializationType,
			serializationType);
		objectFileOutput.prepareToWrite();

		while(!queue.isEmpty()) {

			ObjectFileIndex tmpObjectFileIndex = queue.remove();
			int fileNumber = tmpObjectFileIndex.getFileIndex();

			// reduce the number of objects read from that file.
			pageObjectCounter[fileNumber] = pageObjectCounter[fileNumber] - 1;

			// If needed load more objects from files.
			// if zero load the next page from file and add objects.
			if(pageObjectCounter[fileNumber] == 0 && pageCounter[fileNumber] < fileArray.get(fileNumber)
				.getObjectInEachPage().size() - 1) {

				// add page counter
				pageCounter[fileNumber] = pageCounter[fileNumber] + 1;
				pageObjectCounter[fileNumber] = fileArray.get(fileNumber).getObjectInEachPage()
					.get((long) pageCounter[fileNumber]);

				List<RootData> m_list_read_from_file;

				m_list_read_from_file = fileArray.get(fileNumber)
					.getObjectsFromFile(readFileObject[fileNumber], pageObjectCounter[fileNumber]);

				readFileObject[fileNumber] += m_list_read_from_file.size();

				for(int j = 0; j < m_list_read_from_file.size(); ++j) {
					ObjectFileIndex objectFileIndex = new ObjectFileIndex(fileNumber, m_list_read_from_file.get(j));
					queue.add(objectFileIndex);
				}
			}
			dataToWrite.add(tmpObjectFileIndex.getValue());

			// Write only of we collected more than 10000 objects
			if(dataToWrite.size() > 10000) {

				for(int i = 0; i < dataToWrite.size(); ++i) {
					//Serialize the TweetStatus object and then write to file:
					objectFileOutput.appendObjectToFile((TweetStatus) dataToWrite.get(i));
				}
				dataToWrite.clear();
				// activate the garbage collector
				runTime.gc();
			}
		}

		for(int i = 0; i < dataToWrite.size(); ++i) {
			//Serialize the TweetStatus object and then write to file:
			objectFileOutput.appendObjectToFile((TweetStatus) dataToWrite.get(i));

		}
		dataToWrite.clear();

		objectFileOutput.appendObjectToFileFlush();

		this.ioTime += objectFileOutput.getIoTime();

		System.out.println("Done!");

		// Close object files.
		for(int k = 0; k < numberOfFiles; ++k) {
			this.ioTime += fileArray.get(k).getIoTime();
		}
		// end of time calculation
		long endTime = System.nanoTime();
		double elapsedSeconds = (endTime - startTime) / 1000000000.0;

		// add times to the log file
		LogFileHandler logFileHandler = new LogFileHandler(logFileName);
		logFileHandler.addLog(true, serializationType, true, "TweetStatus", this.ioTime, elapsedSeconds, taskset);
	}

	private void writeToFiles(List<RootData> list, String filename) {

		// Define file handler for each serialization type:
		FileHandler fileHandler = new FileHandler(filename, this.serializationType);
		fileHandler.prepareToWrite();
		for(int i = 0; i < list.size(); ++i) {
			//Serialize the TweetStatus object and then write to file:
			RootData rd = list.get(i);
			fileHandler.appendObjectToFile((TweetStatus) rd);
		}
		fileHandler.appendObjectToFileFlush();
		this.ioTime += fileHandler.getIoTime();
	}
}
