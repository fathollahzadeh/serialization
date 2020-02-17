package edu.bu.tweet;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import javax.json.*;
import org.apache.log4j.Logger;
import edu.rice.dmodel.Base;
import edu.rice.dmodel.RootData;


public class SymbolEntity extends Base implements RootData {

    private static final long serialVersionUID = -1393301876954386760L;
    static Logger logger = Logger.getLogger(SymbolEntity.class);

    private List<Integer> indices;
    private String text;

    public SymbolEntity() {
        this.indices = new ArrayList<>();
    }

    public List<Integer> getIndices() {
        return indices;
    }

    public void setIndices(List<Integer> indices) {
        this.indices = indices;
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

        allocatedBufferSize += 4 * (indices.size() + 1); //indices * sizeof integer

        // array fields
        ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
        byteBuffer.putInt(textBytes.length);
        byteBuffer.put(textBytes);

        byteBuffer.putInt(indices.size());
        for (int i = 0; i < indices.size(); i++) {
            byteBuffer.putInt(indices.get(i));
        }
        return byteBuffer.array();
    }

    public RootData readByteBuffer(byte[] buffData) {
        ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
        int stringSize;

        stringSize = byteBuffer.getInt();
        this.text = extractString(byteBuffer, stringSize);

        int numberOfIndices = byteBuffer.getInt();
        for (int i = 0; i < numberOfIndices; i++) {
            this.indices.add(byteBuffer.getInt());
        }
        return this;
    }
    public JsonObject jsonObjectBuilder() {

        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
        JsonArrayBuilder jsonIndicesArray = Json.createArrayBuilder();
        for (Integer integer : indices) {
            jsonIndicesArray.add(integer);
        }
        objectBuilder.add("indices", jsonIndicesArray);

        if (this.text != null && !this.text.isEmpty()) {
            objectBuilder.add("text", this.text);
        }
        JsonObject jsonObject = objectBuilder.build();
        return jsonObject;
    }

    public SymbolEntity readJSONSymbolEntity(JsonObject jsonObject) {
        if (jsonObject.getJsonArray("indices") != null) {
            JsonArray indicesArray = jsonObject.getJsonArray("indices");
            for (int i = 0; i < indicesArray.size(); i++) {
                this.indices.add(indicesArray.getInt(i));
            }
        }

        if (jsonObject.get("text") != null && jsonObject.get("text") != JsonValue.NULL) {
            this.text = jsonObject.getString("text");
        }
        return  this;
    }

    public int compareTo(RootData o) {
        return 0;
    }
}

