package edu.bu.tweet;

import edu.rice.dmodel.Base;
import edu.rice.dmodel.RootData;
import org.apache.log4j.Logger;
import javax.json.*;
import java.nio.ByteBuffer;
import java.util.List;

public class MatchingRulesEntity extends Base implements RootData {

    static Logger logger = Logger.getLogger(AdditionalMediaInfoEntity.class);

    private String tag;
    private long id;
    private String id_str;

    public String getTag() {
        return tag;
    }

    public void setTag(String tag) {
        this.tag = tag;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getId_str() {
        return id_str;
    }

    public void setId_str(String id_str) {
        this.id_str = id_str;
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

        byte[] tagBytes = (tag != null) ? tag.getBytes() : new byte[0];
        allocatedBufferSize += tagBytes.length + 4;

        byte[] id_strBytes = (id_str != null) ? id_str.getBytes() : new byte[0];
        allocatedBufferSize += id_strBytes.length + 4;

        allocatedBufferSize += 8;// id

        // array fields
        ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
        byteBuffer.putInt(tagBytes.length);
        byteBuffer.put(tagBytes);
        byteBuffer.putInt(id_strBytes.length);
        byteBuffer.put(id_strBytes);
        byteBuffer.putLong(id);

        return byteBuffer.array();
    }

    public RootData readByteBuffer(byte[] buffData) {
        ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
        int stringSize;

        stringSize = byteBuffer.getInt();
        this.tag = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.id_str = extractString(byteBuffer, stringSize);
        this.id = byteBuffer.getLong();
        return this;
    }

    public int compareTo(RootData o) {
        return 0;
    }

    public JsonObject jsonObjectBuilder() {

        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
        if (this.tag != null && !this.tag.isEmpty()) {
            objectBuilder.add("tag", this.tag);
        }

        objectBuilder.add("id", this.id);

        if (this.id_str != null && !this.id_str.isEmpty()) {
            objectBuilder.add("id_str", this.id_str);
        }
        JsonObject jsonObject = objectBuilder.build();
        return jsonObject;
    }

    public MatchingRulesEntity readJSONMatchingRulesEntity(JsonObject jsonObject) {
        if (jsonObject.get("tag") != null && jsonObject.get("tag") != JsonValue.NULL) {
            this.tag = jsonObject.getString("tag");
        }
        this.id = Long.parseLong(jsonObject.getJsonNumber("id").toString());

        if (jsonObject.get("id_str") != null && jsonObject.get("id_str") != JsonValue.NULL) {
            this.id_str = jsonObject.getString("id_str");
        }

        return this;
    }
}
