package edu.bu.filehandler;

import com.esotericsoftware.kryo.Kryo;
import com.google.gson.Gson;
import edu.bu.tweet.TweetStatus;
import edu.bu.util.*;
import org.apache.log4j.Logger;

import java.io.*;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class FileHandler {

    static Logger logger = Logger.getLogger(FileHandler.class);
    private String fileName;
    private long currentPageNumber;
    private long currentOffset;
    byte[] pageBuffer;
    private ByteBuffer bbPageBuffer;

    //total number of objects in serialized file:
    private long totalOfObjects;

    //Output Stream: For Writing:
    RandomAccessFile randOutStreamRegularFile;

    //Output Stream: For Index Writing:
     BufferedOutputStream bosIndexFile;

    //Input Stream: For Reading:
    FileChannel inStreamRegularFile;

    //Page index:
    List<Long> pageIndex;

    //Object index:
    List<Long> objectIndex;

    //Object Length:
    List<Long> objectLength;

    //Object in each page:
    Map<Long, Long> objectInEachPage;

    //benchmark times:
    private double ioTime;
    private double indexTime;

    //Network Experiments:
    private long networkPageSize;

    private SerializationType method = null;

    public FileHandler(String fileName, int serializationType) {
        this.fileName = fileName;
        this.currentOffset = 0;
        this.pageIndex=new ArrayList<>();
        this.objectIndex=new ArrayList<>();
        this.objectLength=new ArrayList<>();

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
            case 7:
                method = SerializationType.FLATBUFFERS;
                break;
        }
    }

    //Write data index to the an index file:
    private void writeIndexToFile(List<Long> indexList) {

        ByteBuffer byteBufferLengths = ByteBuffer.allocate(8  + (indexList.size() * 8));

        try {
            byte[] data = null;
            // first write total number of Objects into file.
            byteBufferLengths.putLong(indexList.size()); // 8 bytes

            // then the whole list array.
            for (Long l:indexList){
                byteBufferLengths.putLong(l);
            }
             // write the list to disk.
            data = byteBufferLengths.array();
            bosIndexFile.write(data); // write the data

        }
        catch (Exception e){
            logger.error("write index to file error! ",e);
        }
    }

    private void readIndexesFromFile() {

        this.pageIndex=new ArrayList<>();
        this.objectIndex=new ArrayList<>();
        this.objectLength=new ArrayList<>();

        try {
            Path path = Paths.get(this.fileName + ".index");
            FileChannel fileChannel = FileChannel.open(path);

            //Read PageIndex List from file:
            ByteBuffer byteBufferSizeOf = ByteBuffer.allocateDirect(8);
            fileChannel.read(byteBufferSizeOf);
            byteBufferSizeOf.flip();

            long totalPageNumbers = byteBufferSizeOf.getLong(); // 8 bytes

            ByteBuffer byteBuffer = ByteBuffer.allocateDirect((int) (totalPageNumbers * 8)); // our page index data
            fileChannel.read(byteBuffer);
            byteBuffer.flip();

            for (long i=0;i<totalPageNumbers;i++){
                long value=byteBuffer.getLong();
                pageIndex.add(value);
            }

            //Read ObjectIndex List from file:
            byteBufferSizeOf = ByteBuffer.allocateDirect(8);
            fileChannel.read(byteBufferSizeOf);
            byteBufferSizeOf.flip();

            long totalObjectNumbers = byteBufferSizeOf.getLong(); // 8 bytes

            byteBuffer = ByteBuffer.allocateDirect((int) (totalObjectNumbers * 8)); // our object index data
            fileChannel.read(byteBuffer);
            byteBuffer.flip();

            for (long i=0;i<totalObjectNumbers;i++){
                long value=byteBuffer.getLong();
                objectIndex.add(value);
            }

            //Read ObjectLength List from file:
            byteBufferSizeOf = ByteBuffer.allocateDirect(8);
            fileChannel.read(byteBufferSizeOf);
            byteBufferSizeOf.flip();

            long totalLengthNumbers = byteBufferSizeOf.getLong(); // 8 bytes

            byteBuffer = ByteBuffer.allocateDirect((int) (totalLengthNumbers * 8)); // our object index data
            fileChannel.read(byteBuffer);
            byteBuffer.flip();

            for (long i=0;i<totalLengthNumbers;i++){
                long value=byteBuffer.getLong();
                objectLength.add(value);
            }

            fileChannel.close();

        } catch (IOException e) {
            logger.error("readIndex  ", e);
        }

    }

    private void readPageFromFile(Long id) {
        //If page is already in RAM: Use from RAM:
        if (currentPageNumber == id) {
            return;
        }
        //Page not in RAM: Disk IO:
        else {
            try {

                this.bbPageBuffer.clear();
                long newPosition = id * Const.PAGESIZE;
                long tmpTime = System.nanoTime();

                // Disk I/O
                inStreamRegularFile.position(newPosition);
                inStreamRegularFile.read(bbPageBuffer); // read object data from disk

                // Time Calculation
                ioTime += (System.nanoTime() - tmpTime);
                currentPageNumber = id;
            }
            catch (Exception ex){
                logger.error("read new page error!",ex);
            }

        }
    }

    public ArrayList<RootData> getObjectsFromFile(long i, long n){

        ArrayList<RootData> readListOfObject = new ArrayList<RootData>();

        long listSize = Math.min((i + n), this.totalOfObjects);

        //Iterate over all objects that you aspire to read.
        for (long j = i; j < listSize; j++) {

            readPageFromFile(this.pageIndex.get((int) j));

            long lenght_each_object=this.objectLength.get((int) j);

            byte[] buffData_each_obecjt = new byte[(int) lenght_each_object];

            // Copy part of the byte buffer to another byte array
            int relativePosition = Math.toIntExact(this.objectIndex.get((int) j));
            this.bbPageBuffer.position(relativePosition);
            this.bbPageBuffer.get(buffData_each_obecjt, 0, (int) lenght_each_object);
            // NOW read each object
            readListOfObject.add(readObjectWithSerialization(new TweetStatus(),buffData_each_obecjt,this.method,KryoSinglton.getInstance().getKryo()));
        }
        return readListOfObject;
    }


    public void prepareToWrite() {

        try {
            // open a random access file for writing objects to it.
            File outStreamRegularFile = new File(this.fileName);
            FileOutputStream outIndexFile =new FileOutputStream(this.fileName + ".index");

            randOutStreamRegularFile = new RandomAccessFile(outStreamRegularFile, "rw");
            bosIndexFile = new BufferedOutputStream(outIndexFile);

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
        try {
            this.objectInEachPage=new HashMap<>();

            Path path = Paths.get(this.fileName);

            //Opening serialized file and keeping it open
            this.inStreamRegularFile = FileChannel.open(path);

            this.bbPageBuffer= ByteBuffer.allocateDirect(Const.PAGESIZE);

            //reset io time:
            this.ioTime = 0;
            this.indexTime = 0;

            //Read the page and object map data from file
            readIndexesFromFile();

            this.currentPageNumber = -1;

            this.totalOfObjects = this.objectIndex.size();

            //calculate object in each page:
            for (int i = 0; i < pageIndex.size(); ++i) {
                if (objectInEachPage.get(pageIndex.get(i))==null)
                    objectInEachPage.put(pageIndex.get(i),0L);
                objectInEachPage.put(pageIndex.get(i),objectInEachPage.get(pageIndex.get(i))+1);
            }
        }
        catch (Exception ex){
            logger.error("prepareToRead! ",ex);
        }

    }

    public void appendObjectToFile(TweetStatus object){
        byte[] buffer=null;
        int objectSize ;
        try {
            switch (method) {
                case JAVADEFAULT:
                    buffer = object.javaDefaultSerialization();
                    break;
                case JSON:
                    buffer = object.jsonSerialization_withGZIP();
                    break;
                case BSON:
                    buffer = object.bsonSerialization();
                    break;
                case PROTOCOL:
                    buffer = object.protocolBufferWrite();
                    break;
                case KRYO:
                    buffer =object.kryoSerialization(KryoSinglton.getInstance().getKryo());
                    break;
                case BYTEBUFFER:
                    buffer = object.writeByteBuffer();
                    break;
                case FLATBUFFERS:
                    buffer = object.flatBuffersSerialization();
                    break;

            }
            objectSize = buffer.length;

            //check capacity of the current page size
            //if current page is full should be write to the file and then reset the page
            if ((currentOffset + objectSize) > Const.PAGESIZE) {

                //Write in file:
                long tmpTime = System.nanoTime();
                randOutStreamRegularFile.seek(currentPageNumber*Const.PAGESIZE);
                randOutStreamRegularFile.write(this.pageBuffer);
                this.ioTime += (System.nanoTime() - tmpTime);
                currentPageNumber++;
                currentOffset = 0;
                this.pageBuffer=new byte[2*Const.PAGESIZE];
            }
            System.arraycopy(buffer, 0, this.pageBuffer, (int) this.currentOffset, objectSize);
            this.pageIndex.add(currentPageNumber);
            this.objectIndex.add(currentOffset);
            this.objectLength.add((long) objectSize);
            currentOffset += objectSize;
        }
        catch (Exception ex){
            logger.error(ex);
        }
    }
    /*
     * This method reads the objects based on their serialization and prints them out
     */
    public RootData readObjectWithSerialization(TweetStatus myData, byte[] buffData, SerializationType method, Kryo kryo) {
        RootData myDeserlizedObject = null;

        switch (method) {
            case JAVADEFAULT:
                myDeserlizedObject = myData.javaDefaultDeserialization(buffData);
                break;
            case JSON:
                myDeserlizedObject = myData.jsonDeserialization_withGZIP(buffData);
                break;
            case BSON:
                myDeserlizedObject = myData.bsonDeSerialization(buffData);
                break;
            case PROTOCOL:
                myDeserlizedObject = myData.protocolBufferRead(buffData);
                break;
            case KRYO:
                myDeserlizedObject = myData.kryoDeserialization(buffData, myData.getClass(), kryo);
                break;
            case BYTEBUFFER:
                myDeserlizedObject = myData.readByteBuffer(buffData);
                break;
            case FLATBUFFERS:
                myDeserlizedObject = myData.flatBuffersDeserialization(buffData);
                break;
//            case GSON:
//                myDeserlizedObject = myData.gsonDeSerialization(buffData);
//                break;
        }

        return myDeserlizedObject;
    }

    public  void appendObjectToFileFlush(){

        //Write last page in file:
        try {
            long tmpTime = System.nanoTime();
            randOutStreamRegularFile.seek(currentPageNumber * Const.PAGESIZE);
            randOutStreamRegularFile.write(this.pageBuffer);
            this.ioTime += (System.nanoTime() - tmpTime);
        }
        catch (Exception e){
            logger.error("can't write last page to the serialization file!");
        }
        this.writeIndexToFile(this.pageIndex);
        this.writeIndexToFile(this.objectIndex);
        this.writeIndexToFile(this.objectLength);
        try {
            // flush BufferedOutputStream
            bosIndexFile.flush();
        }
        catch (Exception e){
            logger.error("can't close bosIndexFile file! ",e);
        }
       
        try {
            this.randOutStreamRegularFile.close();
        } catch (IOException e) {
            logger.error("can't close randOutStreamRegularFile file! ",e);
        }
    }

    public double getIoTime() {
        return ioTime / 1000000000.0;
    }

    public long getTotalOfObjects() {
        return totalOfObjects;
    }

    public Map<Long, Long> getObjectInEachPage() {
        return objectInEachPage;
    }
}
