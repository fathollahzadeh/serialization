package at.tugraz.benchmarks;

import com.google.gson.Gson;
import at.tugraz.filehandler.FileHandler;
import at.tugraz.filehandler.LogFileHandler;
import at.tugraz.filehandler.ReadTweet;
import at.tugraz.tweet.TweetStatus;
import org.apache.log4j.PropertyConfigurator;
import java.io.IOException;
import java.util.Properties;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public class DataSerialization {

	public static void main(String[] args) throws IOException {

		Properties prop = new Properties();

		PropertyConfigurator.configure(prop);
		prop.setProperty("log4j.appender.WORKLOG.File", "log4j.properties");

		PropertyConfigurator.configure("log4j.properties");

		// Set input file path:
		String inputFile = args[0];

		int serializationType = Integer.parseInt(args[1]);

		//Set output file path
		String outFile = args[2];

		// set number of tweets:
		long numberOfTweets = Long.parseLong(args[3]);

		int round = Integer.parseInt(args[4]);

		boolean taskset = Boolean.parseBoolean(args[5]);

		String logFileName = "bin/benchmark/writeobjects/result_java_writeobjects_" + numberOfTweets + "_" + round + ".txt";

		FileHandler fileHandler = new FileHandler(outFile, serializationType);
		fileHandler.prepareToWrite();

		BlockingQueue<String> queue = new ArrayBlockingQueue<>(1000);
		ReadTweet readTweet = new ReadTweet(queue, inputFile);
		Thread rt = new Thread(readTweet);
		rt.start();
		//starting consumer to consume raw tweet from queue

		double elapsedSeconds = 0;

		try {
			String line;
			readTweet.setReadStatus(true);
			for(long i = 0; i < numberOfTweets; i++) {
				line = queue.take();
				Gson gson = new Gson();
				TweetStatus tweetStatus = gson.fromJson(line, TweetStatus.class);
				long tmpTime = System.nanoTime();
				fileHandler.appendObjectToFile(tweetStatus);
				elapsedSeconds += (System.nanoTime() - tmpTime);
			}
			readTweet.setReadStatus(false);
			queue.take();
		}
		catch(Exception e) {
			e.printStackTrace();
		}
		fileHandler.appendObjectToFileFlush();

		// Time Calculation
		elapsedSeconds /= 1000000000.0;

		LogFileHandler logFileHandler = new LogFileHandler(logFileName);
		logFileHandler
			.addLog(false, serializationType, true, "TweetStatus", fileHandler.getIoTime(), elapsedSeconds, taskset);

	}
}