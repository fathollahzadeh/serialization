package edu.bu.benchmarks;

import com.google.gson.Gson;
import edu.bu.filehandler.FileHandler;
import edu.bu.tweet.TweetStatus;
import org.apache.log4j.PropertyConfigurator;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Properties;
import java.util.stream.Stream;

public class SequentialRead {

    public static void main(String[] args) throws IOException {
        Properties prop = new Properties();

        PropertyConfigurator.configure(prop);
        prop.setProperty("log4j.appender.WORKLOG.File", "log4j.properties");

        PropertyConfigurator.configure("log4j.properties");

        // Before any experiments create a hot gc
        // Create a hot garbage collector
//        Garbage.activateGarbageCollector();
//
//        System.out.println("Activating Java garbage collector!");
//        System.gc();
//        System.out.println("Java garbage collector is made hot!");


        //Set serialized file path
        String inFile = args[0];

        int serializationType = Integer.parseInt(args[1]);

        int from = Integer.parseInt(args[2]);

        int numberofobjects = Integer.parseInt(args[3]);

        int round=Integer.parseInt(args[4]);

        FileHandler fileHandler = new FileHandler(inFile, serializationType);
        fileHandler.prepareToRead();

        fileHandler.getObjectsFromFile(from,numberofobjects);

    }

}
