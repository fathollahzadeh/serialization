package edu.bu.tweet;

import edu.rice.dmodel.Base;
import edu.rice.dmodel.RootData;
import org.apache.log4j.Logger;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonValue;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.List;

public class AdditionalMediaInfoEntity extends Base implements RootData {

    static Logger logger = Logger.getLogger(AdditionalMediaInfoEntity.class);

    private String title;
    private String description;
    private boolean embeddable;
    private boolean monetizable;

    public AdditionalMediaInfoEntity() {
        this.embeddable=false;
        this.monetizable=false;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public boolean isEmbeddable() {
        return embeddable;
    }

    public void setEmbeddable(boolean embeddable) {
        this.embeddable = embeddable;
    }

    public boolean isMonetizable() {
        return monetizable;
    }

    public void setMonetizable(boolean monetizable) {
        this.monetizable = monetizable;
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

        byte[] titleBytes =(title!=null)? title.getBytes(Charset.forName("UTF-8")):new byte[0];
        allocatedBufferSize += titleBytes.length + 4;

        byte[] descriptionBytes =(description!=null)? description.getBytes(Charset.forName("UTF-8")):new byte[0];
        allocatedBufferSize += descriptionBytes.length + 4;

        allocatedBufferSize+=1;//embeddable
        allocatedBufferSize+=1;//monetizable

        // array fields
        ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);

        byteBuffer.putInt(titleBytes.length);
        byteBuffer.put(titleBytes);
        byteBuffer.putInt(descriptionBytes.length);
        byteBuffer.put(descriptionBytes);
        byteBuffer.put(convertToByte(embeddable));
        byteBuffer.put(convertToByte(monetizable));

        return byteBuffer.array();
    }

    public RootData readByteBuffer(byte[] buffData) {

        ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
        int stringSize;

        stringSize = byteBuffer.getInt();
        this.title = extractString(byteBuffer, stringSize);

        stringSize = byteBuffer.getInt();
        this.description = extractString(byteBuffer, stringSize);

        this.embeddable=convertToBoolean(byteBuffer.get());
        this.monetizable=convertToBoolean(byteBuffer.get());

        return this;

    }

    public JsonObject jsonObjectBuilder() {

        JsonObjectBuilder additionalMediaInfoEntityObjectBuilder = Json.createObjectBuilder();
        if (this.title != null && !this.title.isEmpty()) {
            additionalMediaInfoEntityObjectBuilder.add("title", this.title);
        }
        if (this.description != null && !this.description.isEmpty()) {
            additionalMediaInfoEntityObjectBuilder.add("description", this.description);
        }
        additionalMediaInfoEntityObjectBuilder.add("embeddable",this.embeddable);
        additionalMediaInfoEntityObjectBuilder.add("monetizable",this.monetizable);

        JsonObject additionalMediaInfoEntityJsonObject = additionalMediaInfoEntityObjectBuilder.build();

        return additionalMediaInfoEntityJsonObject;
    }

    public AdditionalMediaInfoEntity readJSONAdditionalMediaInfoEntity(JsonObject jsonObject) {

        if (jsonObject.get("title") != null && jsonObject.get("title") != JsonValue.NULL) {
            this.title=jsonObject.getString("title");
        }

        if (jsonObject.get("description") != null && jsonObject.get("description") != JsonValue.NULL) {
            this.description=jsonObject.getString("description");
        }
        this.embeddable=jsonObject.getBoolean("embeddable");
        this.monetizable=jsonObject.getBoolean("monetizable");
        return this;
    }

    public int compareTo(RootData o) {
        return 0;
    }
}
