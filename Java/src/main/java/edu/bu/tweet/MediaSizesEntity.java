package edu.bu.tweet;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import edu.rice.dmodel.Base;
import edu.rice.dmodel.RootData;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonReader;
import javax.json.JsonWriter;
import javax.json.JsonWriterFactory;
import javax.json.stream.JsonGenerator;

import org.apache.log4j.Logger;


public class MediaSizesEntity extends Base implements RootData {

    private static final long serialVersionUID = -7101997427441983771L;
    static Logger logger = Logger.getLogger(MediaSizesEntity.class);

    private SizeEntity thumb;
    private SizeEntity large;
    private SizeEntity medium;
    private SizeEntity small;

    public SizeEntity getThumb() {
        return thumb;
    }

    public void setThumb(SizeEntity thumb) {
        this.thumb = thumb;
    }

    public SizeEntity getLarge() {
        return large;
    }

    public void setLarge(SizeEntity large) {
        this.large = large;
    }

    public SizeEntity getMedium() {
        return medium;
    }

    public void setMedium(SizeEntity medium) {
        this.medium = medium;
    }

    public SizeEntity getSmall() {
        return small;
    }

    public void setSmall(SizeEntity small) {
        this.small = small;
    }

    public List<RootData> generateObjects(int number) {
        return null;
    }

    public RootData javaDefaultDeserialization(byte[] buf) {
        return null;
    }

    public byte[] jsonSerialization() {
        return new byte[0];
    }

    public RootData jsonDeserialization(byte[] buf) {
        return null;
    }

    public byte[] jsonSerialization_withGZIP() {
        return new byte[0];
    }

    public RootData jsonDeserialization_withGZIP(byte[] buf) {
        return null;
    }

    public byte[] protocolBufferWrite() {
        return new byte[0];
    }

    public RootData protocolBufferRead(byte[] buf) {
        return null;
    }

    public byte[] writeByteBuffer() {
        return new byte[0];
    }

    public RootData readByteBuffer(byte[] buffData) {
        return null;
    }

    public int compareTo(RootData o) {
        return 0;
    }
}

