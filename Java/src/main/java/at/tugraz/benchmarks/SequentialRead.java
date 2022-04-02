package at.tugraz.benchmarks;

import at.tugraz.filehandler.FileHandler;
import at.tugraz.filehandler.LogFileHandler;
import org.apache.log4j.PropertyConfigurator;
import java.io.IOException;
import java.util.Properties;

public class SequentialRead {

	public static void main(String[] args) throws IOException {
		Properties prop = new Properties();

		PropertyConfigurator.configure(prop);
		prop.setProperty("log4j.appender.WORKLOG.File", "log4j.properties");

		PropertyConfigurator.configure("log4j.properties");

		//Set serialized file path
		String inFile = args[0];

		int serializationType = Integer.parseInt(args[1]);

		int from = Integer.parseInt(args[2]);

		int numberofobjects = Integer.parseInt(args[3]);

		int round = Integer.parseInt(args[4]);

		boolean taskset = Boolean.parseBoolean(args[5]);

		String logFileName = "bin/benchmark/readobjects/result_java_readobjects_" + numberofobjects + "_" + round + ".txt";

		FileHandler fileHandler = new FileHandler(inFile, serializationType);
		fileHandler.prepareToRead();

		// Start Calculation time:
		long tmpTime = System.nanoTime();

		fileHandler.getObjectsFromFile(from, numberofobjects);

		// Time Calculation
		double elapsedSeconds = (System.nanoTime() - tmpTime) / 1000000000.0;

		LogFileHandler logFileHandler = new LogFileHandler(logFileName);
		logFileHandler
			.addLog(true, serializationType, true, "TweetStatus", fileHandler.getIoTime(), elapsedSeconds, taskset);
	}

}
