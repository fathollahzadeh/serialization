package edu.bu.tweet;

import edu.bu.util.Base;
import edu.bu.util.RootData;
import org.apache.log4j.Logger;
import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonValue;
import java.nio.ByteBuffer;
import java.util.List;

public class OptionEntity extends Base implements RootData {

    static Logger logger = Logger.getLogger(OptionEntity.class);

    private int position;
    private String text;

    public int getPosition() {
        return position;
    }

    public void setPosition(int position) {
        this.position = position;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
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

        byte[] textBytes = (text != null) ? text.getBytes() : new byte[0];
        allocatedBufferSize += textBytes.length + 4;

        allocatedBufferSize+=4;//position

        // array fields
        ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
        byteBuffer.putInt(textBytes.length);
        byteBuffer.put(textBytes);
        byteBuffer.putInt(position);

        return byteBuffer.array();
    }

    public RootData readByteBuffer(byte[] buffData) {
        ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
        int stringSize;

        stringSize = byteBuffer.getInt();
        this.text = extractString(byteBuffer, stringSize);
        this.position=byteBuffer.getInt();

        return this;
    }

    public JsonObject jsonObjectBuilder() {
        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
        objectBuilder.add("position",this.position);
        if (this.text != null && !this.text.isEmpty()) {
            objectBuilder.add("text", this.text);
        }
        JsonObject jsonObject = objectBuilder.build();
        return jsonObject;
    }

    public OptionEntity readJSONOptionEntity(JsonObject jsonObject) {

        this.position=jsonObject.getInt("position");
        if (jsonObject.get("text") != null && jsonObject.get("text") != JsonValue.NULL) {
            this.text = jsonObject.getString("text");
        }
        return this;
    }

    public int compareTo(RootData o) {
        return 0;
    }
}
