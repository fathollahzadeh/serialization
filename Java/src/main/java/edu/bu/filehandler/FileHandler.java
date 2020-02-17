package edu.bu.filehandler;

import edu.bu.tweet.TweetStatus;
import edu.bu.util.Const;
import edu.bu.util.SerializationType;
import edu.rice.pdb.serialization.KryoSinglton;
import org.apache.log4j.Logger;

import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class FileHandler {

    static Logger logger = Logger.getLogger(FileHandler.class);
    private String fileName;
    private long currentPageNumber;
    private long currentOffset;
    private int countObject;
    byte[] pageBuffer;

    //total number of objects in serialized file:
    private long totalOfObjects;

    //Output Stream: For Writing:
    RandomAccessFile randOutStreamRegularFile;

    //Output Stream: For Index Writing:
     RandomAccessFile randOutIndexFile;

    //Input Stream: For Reading:
    File inStreamRegularFile;

    //Page index:
    List<Long> pageIndex;

    //Object index:
    List<Long> objectIndex;

    //Object in each page:
    Map<Long, Long> objectInEachPage;

    //benchmark times:
    private double ioTime;
    private double indexTime;

    //Network Experiments:
    private long networkPageSize;

    private int serializationType;
    private SerializationType method = null;

    public FileHandler(String fileName, int serializationType) {
        this.fileName = fileName;
        this.serializationType = serializationType;
        this.currentOffset = 0;
        this.pageIndex=new ArrayList<>();
        this.objectIndex=new ArrayList<>();

        //Allocates write page buffer:
        this.pageBuffer = new byte[2*Const.PAGESIZE]; // this is our page

        // Write them to file with different serialization methods.
        switch (serializationType) {
            case 1:
                method = SerializationType.JAVADEFAULT;
                break;
            case 2:
                method = SerializationType.JSON;
                break;

            case 3:
                method = SerializationType.BSON;
                break;
            case 4:
                method = SerializationType.PROTOCOL;
                break;

            case 5:
                method = SerializationType.KRYO;
                break;

            case 6:
                method = SerializationType.BYTEBUFFER;
                break;

        }
    }

    //Write data index to the an index file:
    private void writeIndexToFile(List<Long> indexMap) {

    }

    private void readIndexesFromFile() {

    }

    private byte[] readPageFromFile(Long id) {
        return null;
    }


    public void prepareToWrite() {

        try {
            // open a random access file for writing objects to it.
            File outStreamRegularFile = new File(this.fileName);
            File outIndexFile = new File(this.fileName + ".index");

            randOutStreamRegularFile = new RandomAccessFile(outStreamRegularFile, "rw");
            randOutIndexFile = new RandomAccessFile(outIndexFile, "rw");

            this.currentPageNumber = 0;
            //reset io time:
            this.ioTime = 0;
            this.indexTime = 0;
        }
        catch (Exception ex){
            logger.error(ex);
        }
    }

    public void prepareToRead() {

    }

    public void appendObjectToFile(TweetStatus object){
        byte[] buffer=null;
        int objectSize = 0;
        try {
            switch (method) {
                case JAVADEFAULT:
                    buffer = object.javaDefaultSerialization();
                    break;
                case JSON:
                    buffer = object.jsonSerialization();
                    break;
                case BSON:
                    buffer = object.bsonSerialization();
                    break;
                case PROTOCOL:
                    buffer = object.protocolBufferWrite();
                    break;
                case KRYO:
                    buffer = object.kryoSerialization(KryoSinglton.getInstance().getKryo());
                    break;
                case BYTEBUFFER:
                    buffer = object.writeByteBuffer();
                    break;
            }
            objectSize = buffer.length;

            //check capacity of the current page size
            //if current page is full should be write to the file and then reset the page
            if ((currentOffset + objectSize) > Const.PAGESIZE) {

                //Write in file:
                long tmpTime = System.nanoTime();
                randOutStreamRegularFile.write(this.pageBuffer);
                this.ioTime += (System.nanoTime() - tmpTime);
                currentPageNumber++;
                currentOffset = 0;
                this.pageBuffer=new byte[2*Const.PAGESIZE];
            }
            System.arraycopy(buffer, 0, this.pageBuffer, (int) this.currentOffset, buffer.length);
            this.pageIndex.add(currentPageNumber);
            this.objectIndex.add(currentOffset);
            currentOffset += objectSize;
            countObject++;
        }
        catch (Exception ex){
            logger.error(ex);
        }
    }

    public  void appendObjectToFileFlush(){
       
        try {
            this.randOutStreamRegularFile.close();
        } catch (IOException e) {
            logger.error("can't close randOutStreamRegularFile file! ",e);
        }
    }
}
