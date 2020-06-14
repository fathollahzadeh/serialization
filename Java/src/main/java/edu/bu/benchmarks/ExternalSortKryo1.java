package edu.bu.benchmarks;

import edu.bu.filehandler.FileHandler;
import edu.bu.filehandler.LogFileHandler;
import edu.bu.tweet.TweetStatus;
import edu.bu.util.ObjectFileIndex;
import edu.bu.util.RootData;
import org.apache.log4j.PropertyConfigurator;

import java.util.*;

public class ExternalSortKryo1 {

    private String fileName;
    private int numberOfFiles;
    private int serializationType;
    private long numberOfObjectsInEachFiles;
    private  String logFileName;
    private boolean taskset;

    // define variables for calculate bench time:
    private double ioTime = 0;

    public static void main(String[] args) {

        Properties prop = new Properties();

        PropertyConfigurator.configure(prop);
        prop.setProperty("log4j.appender.WORKLOG.File", "log4j.properties");

        PropertyConfigurator.configure("log4j.properties");

        ExternalSortKryo1 externalSort=new ExternalSortKryo1();
        externalSort.fileName=args[0];
        externalSort.numberOfFiles=Integer.parseInt(args[1]);
        externalSort.serializationType=Integer.parseInt(args[2]);
        int round= Integer.parseInt(args[3]);
        externalSort.taskset=Boolean.parseBoolean(args[4]);
        externalSort.logFileName="bin/benchmark/externalsort/result_java_externalsort_"+round+".txt";

        externalSort.runTheExternalSort();
    }

    private void runTheExternalSort(){

        // Get a Runtime object
        Runtime runTime = Runtime.getRuntime();

        System.out.println("Start Reading part of the file into RAM" );

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
       for (int i = 0; i < numberOfFiles; i++) {

            System.out.println("Reading for file number "+ i);

            startIndexInEachFile = i * numberOfObjectsInEachFiles;

            // define a vector to store read objects from each file:
            List<RootData> m_list_read_from_file;

            // read objects from file:
            m_list_read_from_file=fileHandler.getObjectsFromFile(startIndexInEachFile, numberOfObjectsInEachFiles);

            // Sort the data
            long tmpTime = System.nanoTime();

            //Sort:
            Collections.sort(m_list_read_from_file);

            // Sort Time Calculation
            sortTime += System.nanoTime()-tmpTime;

            // write the sorted list back to files.
            String tmpStoreFileName = "bin/tmp/sorted-" + i + "-" + serializationType;
            writeToFiles(m_list_read_from_file, tmpStoreFileName);
            m_list_read_from_file.clear();
           // activate the garbage collector
           runTime.gc();
            
        }
        this.ioTime+=fileHandler.getIoTime();
        System.out.println("First stage done! ");

        // end of time calculation
        long endTime = System.nanoTime();
        double elapsedSeconds = (endTime - startTime)/1000000000.0;

        // add times to the log file
        LogFileHandler logFileHandler=new LogFileHandler(logFileName);
        logFileHandler.addLog(true,serializationType,true,"TweetStatus",this.ioTime,elapsedSeconds,taskset);
    }

    private  void writeToFiles(List<RootData> list, String filename) {

        // Define file handler for each serialization type:
        FileHandler fileHandler = new FileHandler(filename, this.serializationType);
        fileHandler.prepareToWrite();
        for (int i = 0; i < list.size(); ++i) {
            //Serialize the TweetStatus object and then write to file:
            RootData rd=list.get(i);
            fileHandler.appendObjectToFile((TweetStatus)rd );
            //rd=null;
        }
        fileHandler.appendObjectToFileFlush();
        this.ioTime+=fileHandler.getIoTime();
    }
}
