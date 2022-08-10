package at.tugraz.runtime;

import at.tugraz.tweet.TweetStatus;
import at.tugraz.util.Const;
import at.tugraz.util.KryoSinglton;
import at.tugraz.util.RootData;
import com.esotericsoftware.kryo.Kryo;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;

public class ObjectReader {
    static Logger logger = Logger.getLogger(ObjectReader.class);
    protected long currentPageNumber;
    protected int currentOffset;
    protected int row;
    protected int rlen;
    protected String method;
    protected byte[] pageBuffer;
    protected int[] pageIndex;
    protected int[] objectIndex;
    protected int[] objectLength;
    protected HashMap<Integer, Integer> objectInEachPage;
    protected FileChannel inStreamRegularFile;
    protected ByteBuffer bbPageBuffer;
    protected Kryo kryo;

    public ObjectReader(String fname, String method) {
        this(method);

        //Allocates write page buffer:
        this.pageBuffer = new byte[2 * Const.PAGESIZE];

        try {
            this.objectInEachPage = new HashMap<>();
            Path path = Paths.get(fname);

            //Opening serialized file and keeping it open
            this.inStreamRegularFile = FileChannel.open(path);
            this.bbPageBuffer = ByteBuffer.allocateDirect(Const.PAGESIZE);

            //Read the page and object map data from file
            readIndexesFromFile(fname);

            this.currentPageNumber = -1;
            //calculate object in each page:
            for (int index : pageIndex) {
                if (objectInEachPage.containsKey(index)) objectInEachPage.put(index, objectInEachPage.get(index) + 1);
                else objectInEachPage.put(index, 0);
            }
        } catch (Exception ex) {
            logger.error("prepareToRead! ", ex);
        }
    }

    public ObjectReader(String method) {
        this.method = method;
        this.currentOffset = 0;
        this.row = 0;
        this.kryo = new KryoSinglton().getKryo();
    }

    private void readIndexesFromFile(String fname) {

        try {
            Path path = Paths.get(fname + ".index");
            FileChannel fileChannel = FileChannel.open(path);

            //Read PageIndex List from file:
            ByteBuffer byteBufferSizeOf = ByteBuffer.allocateDirect(4);
            fileChannel.read(byteBufferSizeOf);
            byteBufferSizeOf.flip();

            int totalPageNumbers = byteBufferSizeOf.getInt(); // 4 bytes
            this.rlen = totalPageNumbers;
            this.pageIndex = new int[rlen];
            this.objectIndex = new int[rlen];
            this.objectLength = new int[rlen];


            ByteBuffer byteBuffer = ByteBuffer.allocateDirect(totalPageNumbers * 4); // our page index data
            fileChannel.read(byteBuffer);
            byteBuffer.flip();

            for (int i = 0; i < totalPageNumbers; i++) {
                int value = byteBuffer.getInt();
                pageIndex[i] = value;
            }

            //Read ObjectIndex List from file:
            byteBufferSizeOf = ByteBuffer.allocateDirect(4);
            fileChannel.read(byteBufferSizeOf);
            byteBufferSizeOf.flip();

            int totalObjectNumbers = byteBufferSizeOf.getInt(); // 4 bytes

            byteBuffer = ByteBuffer.allocateDirect(totalObjectNumbers * 4); // our object index data
            fileChannel.read(byteBuffer);
            byteBuffer.flip();

            for (int i = 0; i < totalObjectNumbers; i++) {
                int value = byteBuffer.getInt();
                objectIndex[i] = value;
            }

            //Read ObjectLength List from file:
            byteBufferSizeOf = ByteBuffer.allocateDirect(4);
            fileChannel.read(byteBufferSizeOf);
            byteBufferSizeOf.flip();

            int totalLengthNumbers = byteBufferSizeOf.getInt(); // 4 bytes

            byteBuffer = ByteBuffer.allocateDirect(totalLengthNumbers * 4); // our object index data
            fileChannel.read(byteBuffer);
            byteBuffer.flip();

            for (int i = 0; i < totalLengthNumbers; i++) {
                int value = byteBuffer.getInt();
                objectLength[i] = value;
            }
            fileChannel.close();
        } catch (IOException e) {
            logger.error("readIndex  ", e);
        }
    }

    public RootData[] readObjects(long i, int n) {

        long listSize = Math.min((i + n), this.rlen);
        RootData[] readListOfObject = new RootData[(int) (listSize - i)];

        //Iterate over all objects that you aspire to read.
        int index = 0;
        for (int j = (int) i; j < listSize; j++) {
            readPage(this.pageIndex[j]);
            byte[] buffer = new byte[this.objectLength[j]];

            // Copy part of the byte buffer to another byte array
            int relativePosition = Math.toIntExact(this.objectIndex[j]);
            this.bbPageBuffer.position(relativePosition);
            this.bbPageBuffer.get(buffer, 0, this.objectLength[j]);
            // NOW read each object
            readListOfObject[index++] = readObjectWithSerialization(new TweetStatus(), buffer);
        }
        return readListOfObject;
    }

    public long readObjects(long i, int n, RootData[] rd) {

        long listSize = Math.min((i + n), this.rlen);
        //Iterate over all objects that you aspire to read.
        for (int j = (int) i; j < listSize; j++) {
            readPage(this.pageIndex[j]);
            byte[] buffer = new byte[this.objectLength[j]];

            // Copy part of the byte buffer to another byte array
            int relativePosition = Math.toIntExact(this.objectIndex[j]);
            this.bbPageBuffer.position(relativePosition);
            this.bbPageBuffer.get(buffer, 0, this.objectLength[j]);
            // NOW read each object
            rd[j] = readObjectWithSerialization(new TweetStatus(), buffer);
        }
        return listSize;
    }

    public long readObjects(long i, int n, ArrayList<RootData> rd) {

        long listSize = Math.min((i + n), this.rlen);
        //Iterate over all objects that you aspire to read.
        for (int j = (int) i; j < listSize; j++) {
            readPage(this.pageIndex[j]);
            byte[] buffer = new byte[this.objectLength[j]];

            // Copy part of the byte buffer to another byte array
            int relativePosition = Math.toIntExact(this.objectIndex[j]);
            this.bbPageBuffer.position(relativePosition);
            this.bbPageBuffer.get(buffer, 0, this.objectLength[j]);
            // NOW read each object
            rd.add(readObjectWithSerialization(new TweetStatus(), buffer));
        }
        return listSize;
    }

    public void readIO(long i, int n) {

        long listSize = Math.min((i + n), this.rlen);
        //Iterate over all objects that you aspire to read.
        for (int j = (int) i; j < listSize; j++) {
            readPage(this.pageIndex[j]);
            byte[] buffer = new byte[this.objectLength[j]];
            // Copy part of the byte buffer to another byte array
            int relativePosition = Math.toIntExact(this.objectIndex[j]);
            this.bbPageBuffer.position(relativePosition);
            this.bbPageBuffer.get(buffer, 0, this.objectLength[j]);
        }
    }

    protected void readPage(long id) {
        if (currentPageNumber != id) {
            try {
                this.bbPageBuffer.clear();
                long newPosition = id * Const.PAGESIZE;
                inStreamRegularFile.position(newPosition);
                inStreamRegularFile.read(bbPageBuffer); // read object data from disk
                currentPageNumber = id;
            } catch (Exception ex) {
                logger.error("read new page error!", ex);
            }
        }
    }

    /*
     * This method reads the objects based on their serialization and prints them out
     */
    public RootData readObjectWithSerialization(TweetStatus myData, byte[] buffData) {
        RootData myDeserlizedObject = null;
        switch (method) {
            case "Default":
                myDeserlizedObject = myData.javaDefaultDeserialization(buffData);
                break;
            case "Json+Gzip":
                myDeserlizedObject = myData.jsonDeserialization_withGZIP(buffData);
                break;
            case "Bson":
                myDeserlizedObject = myData.bsonDeSerialization(buffData);
                break;
            case "ProtoBuf":
                myDeserlizedObject = myData.protocolBufferRead(buffData);
                break;
            case "Kryo":
                myDeserlizedObject = myData.kryoDeserialization(buffData, myData.getClass(), kryo);
                break;
            case "ByteBuffer":
                myDeserlizedObject = myData.readByteBuffer(buffData);
                break;
            case "FlatBuffers":
                myDeserlizedObject = myData.flatBuffersDeserialization(buffData);
                break;
            case "Json":
                myDeserlizedObject = myData.jsonDeserialization(buffData);
                break;
            case "Gson":
                myDeserlizedObject = myData.gsonDeSerialization(buffData);
                break;
        }
        return myDeserlizedObject;
    }

    public int getRlen() {
        return rlen;
    }

    public HashMap<Integer, Integer> getObjectInEachPage() {
        return objectInEachPage;
    }
}
