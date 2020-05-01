package edu.bu.benchmarks;

import edu.bu.filehandler.FileHandler;
import edu.bu.filehandler.LogFileHandler;
import edu.bu.util.RootData;
import org.apache.log4j.PropertyConfigurator;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;
import java.util.stream.Stream;

public class RandomRead {

    public static void main(String[] args) throws IOException {

        Properties prop = new Properties();

        PropertyConfigurator.configure(prop);
        prop.setProperty("log4j.appender.WORKLOG.File", "log4j.properties");

        PropertyConfigurator.configure("log4j.properties");

        //Set serialized file path

        String inFile = args[0];

        int serializationType = Integer.parseInt(args[1]);

        long cunt_to_read = Integer.parseInt(args[2]);

        int round=Integer.parseInt(args[3]);

        boolean taskset=Boolean.parseBoolean(args[5]);

        List<Long>  objectIndexes=new ArrayList<>();
        // read random data from file
        try (Stream<String> stream = Files.lines(Paths.get(args[4]))) {
            stream.forEach(
                    e -> {
                        objectIndexes.add(Long.parseLong(e));
                    }
            );
        }

        String logFileName="bin/benchmark/readobjects/result_java_readobjects_" + cunt_to_read + "_" + round + ".txt";

        FileHandler fileHandler = new FileHandler(inFile, serializationType);
        fileHandler.prepareToRead();

        // Start Calculation time:
        long tmpTime = System.nanoTime();

        List<RootData>  objectList=new ArrayList<>();
        for (long j = 0; j < cunt_to_read; ++j) {
           objectList.add(fileHandler.getObjectsFromFile(objectIndexes.get((int) j), 1).get(0));
        }

        // Time Calculation
        double elapsedSeconds= (System.nanoTime() - tmpTime) / 1000000000.0;

        LogFileHandler logFileHandler=new LogFileHandler(logFileName);
        logFileHandler.addLog(true,serializationType,false,"TweetStatus",fileHandler.getIoTime(),elapsedSeconds,taskset);

    }
}
