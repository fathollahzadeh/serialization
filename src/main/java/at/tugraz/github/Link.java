package at.tugraz.github;

import at.tugraz.util.Base;
import at.tugraz.util.RootData;

import java.util.List;

public class Link extends Base implements RootData {
    private String href;

    @Override
    public List<RootData> generateObjects(int number) {
        return null;
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
    public int compareTo(RootData rootData) {
        return 0;
    }

    public String getHref() {
        return href;
    }

    public void setHref(String href) {
        this.href = href;
    }
}
