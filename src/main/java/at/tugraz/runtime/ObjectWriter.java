package at.tugraz.runtime;


import at.tugraz.tweet.TweetStatus;
import at.tugraz.util.Const;
import at.tugraz.util.KryoSinglton;
import at.tugraz.util.RootData;
import com.esotericsoftware.kryo.Kryo;
import org.apache.log4j.Logger;

import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.util.ArrayList;

public class ObjectWriter {
    static Logger logger = Logger.getLogger(ObjectWriter.class);
    protected File outStreamRegularFile;
    protected RandomAccessFile randOutStreamRegularFile;
    protected FileOutputStream outIndexFile;
    protected BufferedOutputStream bosIndexFile;
    protected long currentPageNumber;
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
        this(method, rlen, Const.PAGESIZE);
        this.outStreamRegularFile = new File(fname);
        this.outIndexFile = new FileOutputStream(fname + ".index");
        this.randOutStreamRegularFile = new RandomAccessFile(outStreamRegularFile, "rw");
        this.bosIndexFile = new BufferedOutputStream(outIndexFile);
    }

    public ObjectWriter(String method, int rlen, int pageSize) {
        this.kryo = new KryoSinglton().getKryo();
        this.currentPageNumber = 0;
        this.currentOffset = 0;
        this.method = method;
        this.pageBuffer = new byte[2 * pageSize]; // this is our page
        this.rlen = rlen;
        this.row = 0;
        this.pageIndex = new int[rlen];
        this.objectIndex = new int[rlen];
        this.objectLength = new int[rlen];
    }


    public void serializeObjects(RootData[] objects) {
        for (RootData object : objects) {
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
            logger.error("ObjectWriter(serializeObject):" + ex.getMessage());
        }
        return buffer;
    }

    public void writeObjectToFile(RootData[] objects) {
        for (RootData object : objects)
            writeObjectToFile(object);
    }
    public void writeBufferToFile(ArrayList<byte[]> buffers) {
        for (byte[] ob : buffers)
            writeObjectToFile(ob);
    }

    public void writeObjectToFile(ArrayList<RootData> objects) {
        for (RootData object : objects)
            writeObjectToFile(object);
    }

    public void writeObjectToFile(RootData object) {
        byte[] buffer = serializeObject(object);
        writeObjectToFile(buffer);
    }

    public void writeObjectToFile(byte[] buffer) {
        int objectSize;
        try {
            objectSize = buffer.length;
            //check capacity of the current page size
            //if current page is full should write to the file and then reset the page
            if ((currentOffset + objectSize) > Const.PAGESIZE) {
                //Write in file:
                randOutStreamRegularFile.seek(currentPageNumber * Const.PAGESIZE);
                randOutStreamRegularFile.write(this.pageBuffer);
                currentPageNumber++;
                currentOffset = 0;
                this.pageBuffer = new byte[2 * Const.PAGESIZE];
            }
            System.arraycopy(buffer, 0, this.pageBuffer, this.currentOffset, objectSize);
            this.pageIndex[row] = (int) currentPageNumber;
            this.objectIndex[row] = currentOffset;
            this.objectLength[row] = objectSize;
            currentOffset += objectSize;
            this.row++;
        } catch (Exception ex) {
            logger.error("writeObjectToFile:" + ex + "  " + row);
        }
    }

    public void writeObjectToNetworkPage(RootData object, DataOutputStream dos, DataInputStream dis) {
        byte[] buffer = serializeObject(object);
        int objectSize;
        try {
            objectSize = buffer.length;
            //check capacity of the current page size
            //if current page is full should write to the socket and then reset the page
            if ((currentOffset + objectSize) > Const.NETWORK_PAGESIZE) {
                byte ack = dis.readByte();
                if (ack != 1) {
                    throw new RuntimeException("writeObjectToNetworkPage " + ack);
                }
                //Write in socket:
                dos.writeInt(currentOffset);
                dos.write(this.pageBuffer, 0, currentOffset);
                currentOffset = 0;
                this.pageBuffer = new byte[2 * Const.NETWORK_PAGESIZE];
            }
            // write object size
            byte[] bytes = ByteBuffer.allocate(4).putInt(objectSize).array();
            System.arraycopy(bytes, 0, this.pageBuffer, this.currentOffset, 4);
            System.arraycopy(buffer, 0, this.pageBuffer, this.currentOffset + 4, objectSize);
            currentOffset += objectSize + 4;
        } catch (Exception ex) {
            logger.error("writeObjectToNetworkPage:" + ex);
        }
    }

    public void writeToNetworkPage(byte[] page, DataOutputStream dos, DataInputStream dis) {
        try {
            byte ack = dis.readByte();
            if (ack != 1) {
                throw new RuntimeException("writeObjectToNetworkPage  ACK " + ack);
            }
            dos.write(page, 0, page.length);
        } catch (Exception ex) {
            logger.error("writeToNetworkPage:", ex);
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

    public void flushToNetwork(DataOutputStream dos, DataInputStream dis) {
        try {
            byte ack = dis.readByte();
            if (ack != 1) {
                throw new RuntimeException("flushToNetwork " + ack);
            }
            dos.writeInt(currentOffset);
            dos.write(this.pageBuffer, 0, currentOffset);

            ack = dis.readByte();
            if (ack != 1) {
                throw new RuntimeException("flushToNetwork " + ack);
            }
            dos.writeInt(-1);
            ack = dis.readByte();
            if (ack != 1) {
                throw new RuntimeException("flushToNetwork " + ack);
            }
            dos.close();
            dis.close();

        } catch (Exception e) {
            logger.error("can't write last page to the serialization network!" + e.getMessage());
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

    public void writeNetworkPageToFile(byte[] page) {
        try {
            randOutStreamRegularFile.seek(randOutStreamRegularFile.length());
            randOutStreamRegularFile.write(page, 4, page.length -4);
        } catch (Exception ex) {
            logger.error("writeNetworkPageToFile! ", ex);
        }
    }

    public void flushNetworkPageWriter() {
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
}
