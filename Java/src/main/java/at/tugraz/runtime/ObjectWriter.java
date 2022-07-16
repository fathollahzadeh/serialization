package at.tugraz.runtime;


import at.tugraz.tweet.TweetStatus;
import at.tugraz.util.Const;
import at.tugraz.util.KryoSinglton;
import at.tugraz.util.RootData;
import com.esotericsoftware.kryo.Kryo;
import com.google.gson.Gson;
import org.apache.log4j.Logger;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;


public class ObjectWriter {
    static Logger logger = Logger.getLogger(ObjectWriter.class);
    protected File outStreamRegularFile;
    protected RandomAccessFile randOutStreamRegularFile;
    protected FileOutputStream outIndexFile;
    protected BufferedOutputStream bosIndexFile;
    protected int currentPageNumber;
    protected int currentOffset;
    protected int row;
    protected String method;
    protected byte[] pageBuffer;
    int rlen;
    int[] pageIndex;
    int[] objectIndex;
    int[] objectLength;
    protected Kryo kryo;

    public ObjectWriter(String fname, String method, int rlen) throws FileNotFoundException {
        this(method, rlen);
        this.outStreamRegularFile = new File(fname);
        this.outIndexFile = new FileOutputStream(fname + ".index");
        this.randOutStreamRegularFile = new RandomAccessFile(outStreamRegularFile, "rw");
        this.bosIndexFile = new BufferedOutputStream(outIndexFile);
    }

    public ObjectWriter(String method, int rlen){
        this.kryo = new KryoSinglton().getKryo();
        this.currentPageNumber = 0;
        this.currentOffset = 0;
        this.method = method;
        this.pageBuffer = new byte[2 * Const.PAGESIZE]; // this is our page
        this.rlen = rlen;
        this.row = 0;
        this.pageIndex = new int[rlen];
        this.objectIndex = new int[rlen];
        this.objectLength = new int[rlen];
    }


    public void serializeObjects(RootData[] objects) {
        for (RootData object : objects){
            this.serializeObject(object);
        }
    }

    public byte[] serializeObject(RootData object) {
        byte[] buffer = null;
        try {
            switch (method) {
                case "Default":
                    buffer = object.javaDefaultSerialization();
                    break;
                case "Json+Gzip":
                    buffer = object.jsonSerialization_withGZIP();
                    break;
                case "Bson":
                    buffer = object.bsonSerialization();
                    break;
                case "ProtoBuf":
                    buffer = object.protocolBufferWrite();
                    break;
                case "Kryo":
                    buffer = object.kryoSerialization(kryo);
                    break;
                case "ByteBuffer":
                    buffer = object.writeByteBuffer();
                    break;
                case "FlatBuffers":
                    buffer = ((TweetStatus) object).flatBuffersSerialization();
                    break;
                case "Json":
                    buffer = object.jsonSerialization();
                    break;
                case "Gson":
                    buffer = object.gsonSerialization();
                    break;

            }
        } catch (Exception ex) {
            ex.printStackTrace();
            logger.error("ObjectWriter(serializeObject):"+ex.getMessage());
        }
        return buffer;
    }

    public void writeObjectToFile(RootData[] objects) {
        for (RootData object : objects)
            writeObjectToFile(object);
    }

    public void writeObjectToFile(RootData object) {
        byte[] buffer = serializeObject(object);
        int objectSize;
        try {
            objectSize = buffer.length;
            //check capacity of the current page size
            //if current page is full should write to the file and then reset the page
            if ((currentOffset + objectSize) > Const.PAGESIZE) {
                //Write in file:
                randOutStreamRegularFile.seek((long) currentPageNumber * Const.PAGESIZE);
                randOutStreamRegularFile.write(this.pageBuffer);
                currentPageNumber++;
                currentOffset = 0;
                this.pageBuffer = new byte[2 * Const.PAGESIZE];
            }
            System.arraycopy(buffer, 0, this.pageBuffer, this.currentOffset, objectSize);
            this.pageIndex[row] = currentPageNumber;
            this.objectIndex[row] = currentOffset;
            this.objectLength[row] = objectSize;
            currentOffset += objectSize;
            this.row++;
        } catch (Exception ex) {
            logger.error("writeObjectToFile:"+ex+"  "+row);
        }
    }

    public void flush() {
        //Write last page in file:
        try {
            randOutStreamRegularFile.seek((long) currentPageNumber * Const.PAGESIZE);
            randOutStreamRegularFile.write(this.pageBuffer);
        } catch (Exception e) {
            logger.error("can't write last page to the serialization file!");
        }

        this.writeIndexToFile(this.pageIndex);
        this.writeIndexToFile(this.objectIndex);
        this.writeIndexToFile(this.objectLength);
        try {
            // flush BufferedOutputStream
            bosIndexFile.flush();
        } catch (Exception e) {
            logger.error("can't close bosIndexFile file! ", e);
        }

        try {
            this.randOutStreamRegularFile.close();
        } catch (IOException e) {
            logger.error("can't close randOutStreamRegularFile file! ", e);
        }
    }

    //Write data index to an index file:
    private void writeIndexToFile(int[] indexList) {
        ByteBuffer bb = ByteBuffer.allocate(4 + (rlen * 4));
        try {
            byte[] data;
            // first write total number of Objects into file.
            bb.putInt(rlen); // 4 bytes

            // then the whole list array.
            for (Integer i : indexList) {
                bb.putInt(i);
            }
            // write the list to disk.
            data = bb.array();
            this.bosIndexFile.write(data); // write the data
        } catch (Exception e) {
            logger.error("write index to file error! ", e);
        }
    }
}
