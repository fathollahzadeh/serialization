package at.tugraz.github;

import at.tugraz.tweet.TweetStatus;
import at.tugraz.util.RootData;
import com.esotericsoftware.kryo.Kryo;

import java.util.List;

public class RequestedReviewer extends User implements RootData {
    @Override
    public List<RootData> generateObjects(int number) {
        return null;
    }

    @Override
    public byte[] javaDefaultSerialization() {
        return new byte[0];
    }

    @Override
    public RootData javaDefaultDeserialization(byte[] buf) {
        return null;
    }

    @Override
    public byte[] jsonSerialization() {
        return new byte[0];
    }

    @Override
    public RootData jsonDeserialization(byte[] buf) {
        return null;
    }

    @Override
    public byte[] jsonSerialization_withGZIP() {
        return new byte[0];
    }

    @Override
    public RootData jsonDeserialization_withGZIP(byte[] buf) {
        return null;
    }

    @Override
    public byte[] protocolBufferWrite() {
        return new byte[0];
    }

    @Override
    public RootData protocolBufferRead(byte[] buf) {
        return null;
    }

    @Override
    public byte[] kryoSerialization(Kryo kryo) {
        return new byte[0];
    }

    @Override
    public RootData kryoDeserialization(byte[] buf, Class<?> myclass, Kryo kryo) {
        return null;
    }

    @Override
    public byte[] writeByteBuffer() {
        return new byte[0];
    }

    @Override
    public RootData readByteBuffer(byte[] buffData) {
        return null;
    }

    @Override
    public byte[] bsonSerialization() {
        return new byte[0];
    }

    @Override
    public RootData bsonDeSerialization(byte[] buffData) {
        return null;
    }

    @Override
    public byte[] gsonSerialization() {
        return new byte[0];
    }

    @Override
    public TweetStatus gsonDeSerialization(byte[] buff) {
        return null;
    }

    @Override
    public int compareTo(RootData rootData) {
        return 0;
    }


}
