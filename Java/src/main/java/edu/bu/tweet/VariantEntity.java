package edu.bu.tweet;

import java.nio.ByteBuffer;
import java.util.List;
import edu.bu.util.Base;
import edu.bu.util.RootData;
import javax.json.*;
import org.apache.log4j.Logger;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;


public class VariantEntity extends Base implements RootData {

	private static final long serialVersionUID = 4970008846733532705L;
	static Logger logger = Logger.getLogger(VariantEntity.class);

    private long bitrate;
    private String content_type;
    private String url;

    public long getBitrate() {
        return bitrate;
    }

    public void setBitrate(long bitrate) {
        this.bitrate = bitrate;
    }

    public String getContent_type() {
        return content_type;
    }

    public void setContent_type(String content_type) {
        this.content_type = content_type;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
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
        byte[] content_typeBytes = (content_type != null) ? content_type.getBytes() : new byte[0];
        allocatedBufferSize += content_typeBytes.length + 4;

        byte[] urlBytes = (url != null) ? url.getBytes() : new byte[0];
        allocatedBufferSize += urlBytes.length + 4;

        allocatedBufferSize+=8;//bitrate

        // array fields
        ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
        byteBuffer.putLong(bitrate);
        byteBuffer.putInt(content_typeBytes.length);
        byteBuffer.put(content_typeBytes);
        byteBuffer.putInt(urlBytes.length);
        byteBuffer.put(urlBytes);

        return byteBuffer.array();
    }

    public RootData readByteBuffer(byte[] buffData) {
        ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
        int stringSize;

        this.bitrate=byteBuffer.getLong();
        stringSize = byteBuffer.getInt();
        this.content_type = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.url = extractString(byteBuffer, stringSize);
        return this;
    }

    public JsonObject jsonObjectBuilder() {
        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
        objectBuilder.add("bitrate",this.bitrate);

        if (this.content_type != null && !this.content_type.isEmpty()) {
            objectBuilder.add("content_type", this.content_type);
        }

        if (this.url != null && !this.url.isEmpty()) {
            objectBuilder.add("url", this.url);
        }

        JsonObject jsonObject = objectBuilder.build();
        return jsonObject;
    }

    public VariantEntity readJSONVariantEntity(JsonObject jsonObject) {

        this.bitrate=Long.parseLong(jsonObject.getJsonNumber("bitrate").toString());

        if (jsonObject.get("content_type") != null && jsonObject.get("content_type") != JsonValue.NULL) {
            this.content_type = jsonObject.getString("content_type");
        }
        if (jsonObject.get("url") != null && jsonObject.get("url") != JsonValue.NULL) {
            this.url = jsonObject.getString("url");
        }
        return  this;
    }
    public byte[] bsonSerialization() {
        BasicOutputBuffer outputBuffer = new BasicOutputBuffer();
        BsonBinaryWriter writer=new BsonBinaryWriter(outputBuffer);

        writer.writeStartDocument();

        if (this.content_type!=null)
            writer.writeString("content_type",this.content_type);

        if (this.url!=null)
            writer.writeString("url",this.url);

        writer.writeInt64("bitrate",this.bitrate);

        writer.writeEndDocument();

        return outputBuffer.toByteArray();
    }

    public RootData bsonDeSerialization(byte[] buffData) {
        ByteBuffer buf = ByteBuffer.wrap(buffData);
        BsonBinaryReader reader=new BsonBinaryReader(buf);

        reader.readStartDocument();

        String currentName=reader.readName();
        if (currentName.equals("content_type")){
            this.content_type=reader.readString();
            currentName=reader.readName();
        }

        if (currentName.equals("url")){
            this.url=reader.readString();
            reader.readName();
        }
        this.bitrate=reader.readInt64();
        reader.readEndDocument();

        return this;
    }
    public int compareTo(RootData o) {
        return 0;
    }
}

