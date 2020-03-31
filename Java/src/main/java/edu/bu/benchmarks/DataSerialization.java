package edu.bu.benchmarks;

import com.google.gson.Gson;
import edu.bu.filehandler.FileHandler;
import edu.bu.filehandler.ReadTweet;
import edu.bu.tweet.TweetStatus;
import org.apache.log4j.PropertyConfigurator;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Properties;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.stream.Stream;

public class DataSerialization {

    public static void main(String[] args) throws IOException {

        Properties prop = new Properties();

        PropertyConfigurator.configure(prop);
        prop.setProperty("log4j.appender.WORKLOG.File", "log4j.properties");

        PropertyConfigurator.configure("log4j.properties");

        // Before any experiments create a hot gc
        // Create a hot garbage collector
         //Garbage.activateGarbageCollector();
//
//        System.out.println("Activating Java garbage collector!");
      //  System.gc();
//        System.out.println("Java garbage collector is made hot!");

        // Set input file path:
        String inputFile = args[0];

        int serializationType = Integer.parseInt(args[1]);

        //Set output file path
        String outFile = args[2];

        // set number of tweets:
        long numberOfTweets=Long.parseLong(args[3]);

        FileHandler fileHandler = new FileHandler(outFile, serializationType);
        fileHandler.prepareToWrite();

        BlockingQueue<String> queue = new ArrayBlockingQueue<>(1000);
        ReadTweet readTweet = new ReadTweet(queue,inputFile);
       Thread rt=  new Thread(readTweet);
       rt.start();
        //starting consumer to consume raw tweet from queue
        try{
            String line;
            readTweet.setReadStatus(true);
            for (long i=0;i<numberOfTweets;i++){
                line = queue.take();
                Gson gson = new Gson();
                TweetStatus tweetStatus = gson.fromJson(line, TweetStatus.class);
                fileHandler.appendObjectToFile(tweetStatus);
            }
            readTweet.setReadStatus(false);
            queue.take();
        }catch(Exception e) {
            e.printStackTrace();
        }
        fileHandler.appendObjectToFileFlush();

    }
}
