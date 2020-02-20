package edu.bu.tweet;

import java.nio.ByteBuffer;
import java.util.List;
import edu.bu.util.Base;
import edu.bu.util.RootData;
import javax.json.*;
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

        int allocatedBufferSize = 0;

        byte[] thumbBytes = (thumb != null) ? thumb.writeByteBuffer() : new byte[0];
        allocatedBufferSize += thumbBytes.length + 4;

        byte[] largeBytes = (large != null) ? large.writeByteBuffer() : new byte[0];
        allocatedBufferSize += largeBytes.length + 4;

        byte[] mediumBytes = (medium != null) ? medium.writeByteBuffer() : new byte[0];
        allocatedBufferSize += mediumBytes.length + 4;

        byte[] smallBytes = (small != null) ? small.writeByteBuffer() : new byte[0];
        allocatedBufferSize += smallBytes.length + 4;

        // array fields
        ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
        byteBuffer.putInt(thumbBytes.length);
        byteBuffer.put(thumbBytes);
        byteBuffer.putInt(largeBytes.length);
        byteBuffer.put(largeBytes);
        byteBuffer.putInt(mediumBytes.length);
        byteBuffer.put(mediumBytes);
        byteBuffer.putInt(smallBytes.length);
        byteBuffer.put(smallBytes);

        return byteBuffer.array();
    }

    public RootData readByteBuffer(byte[] buffData) {
        ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);

        byte[] thumbBytes = new byte[byteBuffer.getInt()];
        if (thumbBytes.length > 0) {
            byteBuffer.get(thumbBytes, 0, thumbBytes.length);
            this.thumb = new SizeEntity();
            this.thumb.readByteBuffer(thumbBytes);
        } else
            this.thumb = null;

        byte[] largeBytes = new byte[byteBuffer.getInt()];
        if (largeBytes.length > 0) {
            byteBuffer.get(largeBytes, 0, largeBytes.length);
            this.large = new SizeEntity();
            this.large.readByteBuffer(largeBytes);
        } else
            this.large = null;

        byte[] mediumBytes = new byte[byteBuffer.getInt()];
        if (mediumBytes.length > 0) {
            byteBuffer.get(mediumBytes, 0, mediumBytes.length);
            this.medium = new SizeEntity();
            this.medium.readByteBuffer(mediumBytes);
        } else
            this.medium = null;

        byte[] smallBytes = new byte[byteBuffer.getInt()];
        if (smallBytes.length > 0) {
            byteBuffer.get(smallBytes, 0, smallBytes.length);
            this.small = new SizeEntity();
            this.small.readByteBuffer(smallBytes);
        } else
            this.small = null;

        return this;
    }

    public JsonObject jsonObjectBuilder() {

        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();

        if (this.thumb != null) {
            objectBuilder.add("thumb", this.thumb.jsonObjectBuilder());
        }
        if (this.large != null) {
            objectBuilder.add("large", this.large.jsonObjectBuilder());
        }
        if (this.medium != null) {
            objectBuilder.add("medium", this.medium.jsonObjectBuilder());
        }
        if (this.small != null) {
            objectBuilder.add("small", this.small.jsonObjectBuilder());
        }
        JsonObject jsonObject = objectBuilder.build();
        return jsonObject;
    }

    public MediaSizesEntity readJSONMediaSizesEntity(JsonObject jsonObject) {

        if (jsonObject.getJsonObject("thumb") != null && jsonObject.getJsonObject("thumb") != JsonValue.NULL) {
            JsonObject thumbJsonObject = jsonObject.getJsonObject("thumb");
            this.thumb=new SizeEntity().readJSONSizeEntity(thumbJsonObject);
        }
        if (jsonObject.getJsonObject("large") != null && jsonObject.getJsonObject("large") != JsonValue.NULL) {
            JsonObject largeJsonObject = jsonObject.getJsonObject("large");
            this.large=new SizeEntity().readJSONSizeEntity(largeJsonObject);
        }
        if (jsonObject.getJsonObject("medium") != null && jsonObject.getJsonObject("medium") != JsonValue.NULL) {
            JsonObject mediumJsonObject = jsonObject.getJsonObject("medium");
            this.medium=new SizeEntity().readJSONSizeEntity(mediumJsonObject);
        }
        if (jsonObject.getJsonObject("small") != null && jsonObject.getJsonObject("small") != JsonValue.NULL) {
            JsonObject smallJsonObject = jsonObject.getJsonObject("small");
            this.small=new SizeEntity().readJSONSizeEntity(smallJsonObject);
        }
        return this;
    }

    public int compareTo(RootData o) {
        return 0;
    }
}

