package edu.bu.tweet;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

import edu.bu.util.Base;
import edu.bu.util.RootData;

import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonValue;

import org.apache.log4j.Logger;
import org.bson.BsonBinary;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;


public class MediaEntity extends Base implements RootData {

    private static final long serialVersionUID = 6676093799500575284L;
    static Logger logger = Logger.getLogger(MediaEntity.class);

    private String display_url;
    private String expanded_url;
    private long id;
    private List<Integer> indices;
    private String media_url;
    private String media_url_https;
    private MediaSizesEntity sizes;
    private String type;
    private long source_status_id;
    private String source_status_id_str;
    private String url;
    private VideoEntity video_info;
    private AdditionalMediaInfoEntity additional_media_info;

    public MediaEntity() {
        this.indices = new ArrayList<>();
    }

    public String getDisplay_url() {
        return display_url;
    }

    public void setDisplay_url(String display_url) {
        this.display_url = display_url;
    }

    public String getExpanded_url() {
        return expanded_url;
    }

    public void setExpanded_url(String expanded_url) {
        this.expanded_url = expanded_url;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public List<Integer> getIndices() {
        return indices;
    }

    public void setIndices(List<Integer> indices) {
        this.indices = indices;
    }

    public String getMedia_url() {
        return media_url;
    }

    public void setMedia_url(String media_url) {
        this.media_url = media_url;
    }

    public String getMedia_url_https() {
        return media_url_https;
    }

    public void setMedia_url_https(String media_url_https) {
        this.media_url_https = media_url_https;
    }

    public MediaSizesEntity getSizes() {
        return sizes;
    }

    public void setSizes(MediaSizesEntity sizes) {
        this.sizes = sizes;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public long getSource_status_id() {
        return source_status_id;
    }

    public void setSource_status_id(long source_status_id) {
        this.source_status_id = source_status_id;
    }

    public String getSource_status_id_str() {
        return source_status_id_str;
    }

    public void setSource_status_id_str(String source_status_id_str) {
        this.source_status_id_str = source_status_id_str;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public VideoEntity getVideo_info() {
        return video_info;
    }

    public void setVideo_info(VideoEntity video_info) {
        this.video_info = video_info;
    }

    public AdditionalMediaInfoEntity getAdditional_media_info() {
        return additional_media_info;
    }

    public void setAdditional_media_info(AdditionalMediaInfoEntity additional_media_info) {
        this.additional_media_info = additional_media_info;
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

        byte[] display_urlBytes = (display_url != null) ? display_url.getBytes() : new byte[0];
        allocatedBufferSize += display_urlBytes.length + 4;

        byte[] expanded_urlBytes = (expanded_url != null) ? expanded_url.getBytes() : new byte[0];
        allocatedBufferSize += expanded_urlBytes.length + 4;

        byte[] media_urlBytes = (media_url != null) ? media_url.getBytes() : new byte[0];
        allocatedBufferSize += media_urlBytes.length + 4;

        byte[] media_url_httpsBytes = (media_url_https != null) ? media_url_https.getBytes() : new byte[0];
        allocatedBufferSize += media_url_httpsBytes.length + 4;

        byte[] sizesBytes = (sizes != null) ? sizes.writeByteBuffer() : new byte[0];
        allocatedBufferSize += sizesBytes.length + 4;

        byte[] typeBytes = (type != null) ? type.getBytes() : new byte[0];
        allocatedBufferSize += typeBytes.length + 4;

        byte[] source_status_id_strBytes = (source_status_id_str != null) ? source_status_id_str.getBytes() : new byte[0];
        allocatedBufferSize += source_status_id_strBytes.length + 4;

        byte[] urlBytes = (url != null) ? url.getBytes() : new byte[0];
        allocatedBufferSize += urlBytes.length + 4;

        byte[] video_infoBytes = (video_info != null) ? video_info.writeByteBuffer() : new byte[0];
        allocatedBufferSize += video_infoBytes.length + 4;

        byte[] additional_media_infoBytes = (additional_media_info != null) ? additional_media_info.writeByteBuffer() : new byte[0];
        allocatedBufferSize += additional_media_infoBytes.length + 4;

        allocatedBufferSize += 8; //id
        allocatedBufferSize += 4 * (indices.size() + 1);//indices
        allocatedBufferSize += 8;//source_status_id

        // array fields
        ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
        byteBuffer.putInt(display_urlBytes.length);
        byteBuffer.put(display_urlBytes);
        byteBuffer.putInt(expanded_urlBytes.length);
        byteBuffer.put(expanded_urlBytes);
        byteBuffer.putLong(id);
        byteBuffer.putInt(indices.size());
        for (int i = 0; i < indices.size(); i++) {
            byteBuffer.putInt(indices.get(i));
        }
        byteBuffer.putInt(media_urlBytes.length);
        byteBuffer.put(media_urlBytes);
        byteBuffer.putInt(media_url_httpsBytes.length);
        byteBuffer.put(media_url_httpsBytes);
        byteBuffer.putInt(sizesBytes.length);
        byteBuffer.put(sizesBytes);
        byteBuffer.putInt(typeBytes.length);
        byteBuffer.put(typeBytes);
        byteBuffer.putLong(source_status_id);
        byteBuffer.putInt(source_status_id_strBytes.length);
        byteBuffer.put(source_status_id_strBytes);
        byteBuffer.putInt(urlBytes.length);
        byteBuffer.put(urlBytes);
        byteBuffer.putInt(video_infoBytes.length);
        byteBuffer.put(video_infoBytes);
        byteBuffer.putInt(additional_media_infoBytes.length);
        byteBuffer.put(additional_media_infoBytes);
        return byteBuffer.array();
    }

    public RootData readByteBuffer(byte[] buffData) {
        ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
        int stringSize;

        stringSize = byteBuffer.getInt();
        this.display_url = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.expanded_url = extractString(byteBuffer, stringSize);
        this.id = byteBuffer.getLong();

        int numberOfIndices = byteBuffer.getInt();
        this.indices = new ArrayList<>();
        for (int i = 0; i < numberOfIndices; i++) {
            this.indices.add(byteBuffer.getInt());
        }

        stringSize = byteBuffer.getInt();
        this.media_url = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.media_url_https = extractString(byteBuffer, stringSize);

        byte[] sizesBytes = new byte[byteBuffer.getInt()];
        if (sizesBytes.length > 0) {
            byteBuffer.get(sizesBytes, 0, sizesBytes.length);
            this.sizes = new MediaSizesEntity();
            this.sizes.readByteBuffer(sizesBytes);
        } else
            this.sizes = null;

        stringSize = byteBuffer.getInt();
        this.type = extractString(byteBuffer, stringSize);
        this.source_status_id = byteBuffer.getLong();
        stringSize = byteBuffer.getInt();
        this.source_status_id_str = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.url = extractString(byteBuffer, stringSize);

        byte[] video_infoBytes = new byte[byteBuffer.getInt()];
        if (video_infoBytes.length > 0) {
            byteBuffer.get(video_infoBytes, 0, video_infoBytes.length);
            this.video_info = new VideoEntity();
            this.video_info.readByteBuffer(video_infoBytes);
        } else
            this.video_info = null;

        byte[] additional_media_infoBytes = new byte[byteBuffer.getInt()];
        if (additional_media_infoBytes.length > 0) {
            byteBuffer.get(additional_media_infoBytes, 0, additional_media_infoBytes.length);
            this.additional_media_info = new AdditionalMediaInfoEntity();
            this.additional_media_info.readByteBuffer(additional_media_infoBytes);
        } else
            this.additional_media_info = null;

        return this;
    }

    public JsonObject jsonObjectBuilder() {

        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
        if (this.display_url != null && !this.display_url.isEmpty()) {
            objectBuilder.add("display_url", this.display_url);
        }

        if (this.expanded_url != null && !this.expanded_url.isEmpty()) {
            objectBuilder.add("expanded_url", this.expanded_url);
        }
        objectBuilder.add("id", this.id);

        JsonArrayBuilder jsonIndicesArray = Json.createArrayBuilder();
        for (Integer integer : indices) {
            jsonIndicesArray.add(integer);
        }

        objectBuilder.add("indices", jsonIndicesArray);
        if (this.media_url != null && !this.media_url.isEmpty()) {
            objectBuilder.add("media_url", this.media_url);
        }

        if (this.media_url_https != null && !this.media_url_https.isEmpty()) {
            objectBuilder.add("media_url_https", this.media_url_https);
        }

        if (this.sizes != null) {
            objectBuilder.add("sizes", this.sizes.jsonObjectBuilder());
        }

        if (this.type != null && !this.type.isEmpty()) {
            objectBuilder.add("type", this.type);
        }
        objectBuilder.add("source_status_id", this.source_status_id);

        if (this.source_status_id_str != null && !this.source_status_id_str.isEmpty()) {
            objectBuilder.add("source_status_id_str", this.source_status_id_str);
        }

        if (this.url != null && !this.url.isEmpty()) {
            objectBuilder.add("url", this.url);
        }

        if (this.video_info != null) {
            objectBuilder.add("video_info", this.video_info.jsonObjectBuilder());
        }

        if (this.additional_media_info != null) {
            objectBuilder.add("additional_media_info", this.additional_media_info.jsonObjectBuilder());
        }

        JsonObject jsonObject = objectBuilder.build();
        return jsonObject;
    }

    public MediaEntity readJSONMediaEntity(JsonObject jsonObject) {

        if (jsonObject.get("display_url") != null && jsonObject.get("display_url") != JsonValue.NULL) {
            this.display_url = jsonObject.getString("display_url");
        }
        if (jsonObject.get("expanded_url") != null && jsonObject.get("expanded_url") != JsonValue.NULL) {
            this.expanded_url = jsonObject.getString("expanded_url");
        }
        this.id = Long.parseLong(jsonObject.getJsonNumber("id").toString());

        if (jsonObject.getJsonArray("indices") != null) {
            JsonArray indicesArray = jsonObject.getJsonArray("indices");
            for (int i = 0; i < indicesArray.size(); i++) {
                this.indices.add(indicesArray.getInt(i));
            }
        }

        if (jsonObject.get("media_url") != null && jsonObject.get("media_url") != JsonValue.NULL) {
            this.media_url = jsonObject.getString("media_url");
        }
        if (jsonObject.get("media_url_https") != null && jsonObject.get("media_url_https") != JsonValue.NULL) {
            this.media_url_https = jsonObject.getString("media_url_https");
        }
        if (jsonObject.getJsonObject("sizes") != null && jsonObject.getJsonObject("sizes") != JsonValue.NULL) {
            JsonObject sizesJsonObject = jsonObject.getJsonObject("sizes");
            this.sizes = new MediaSizesEntity().readJSONMediaSizesEntity(sizesJsonObject);
        }
        if (jsonObject.get("type") != null && jsonObject.get("type") != JsonValue.NULL) {
            this.type = jsonObject.getString("type");
        }
        this.source_status_id = Long.parseLong(jsonObject.getJsonNumber("source_status_id").toString());

        if (jsonObject.get("source_status_id_str") != null && jsonObject.get("source_status_id_str") != JsonValue.NULL) {
            this.source_status_id_str = jsonObject.getString("source_status_id_str");
        }
        if (jsonObject.get("url") != null && jsonObject.get("url") != JsonValue.NULL) {
            this.url = jsonObject.getString("url");
        }
        if (jsonObject.getJsonObject("video_info") != null && jsonObject.getJsonObject("video_info") != JsonValue.NULL) {
            JsonObject video_infoJsonObject = jsonObject.getJsonObject("video_info");
            this.video_info = new VideoEntity().readJSONVideoEntity(video_infoJsonObject);
        }

        if (jsonObject.getJsonObject("additional_media_info") != null && jsonObject.getJsonObject("additional_media_info") != JsonValue.NULL) {
            JsonObject additional_media_infoJsonObject = jsonObject.getJsonObject("additional_media_info");
            this.additional_media_info = new AdditionalMediaInfoEntity().readJSONAdditionalMediaInfoEntity(additional_media_infoJsonObject);
        }

        return this;
    }

    public byte[] bsonSerialization() {
        BasicOutputBuffer outputBuffer = new BasicOutputBuffer();
        BsonBinaryWriter writer = new BsonBinaryWriter(outputBuffer);

        writer.writeStartDocument();
        if (this.display_url != null) {
            writer.writeString("display_url",this.display_url);
        }

        if (this.expanded_url != null) {
            writer.writeString("expanded_url",this.expanded_url);
        }
        writer.writeInt64("id", this.id);

        writer.writeInt32("indices_size", this.indices.size());
        writer.writeName("indices");
        writer.writeStartArray();
        for (Integer i : this.indices) {
            writer.writeInt32(i);
        }
        writer.writeEndArray();

        if (this.media_url != null) {
            writer.writeString("media_url",this.media_url);
        }

        if (this.media_url_https != null) {
            writer.writeString("media_url_https",this.media_url_https);
        }

        if (this.sizes != null)
            writer.writeBinaryData("sizes", new BsonBinary(this.sizes.bsonSerialization()));

        if (this.type != null) {
            writer.writeString("type",this.type);
        }

        if (this.source_status_id_str != null) {
            writer.writeString("source_status_id_str",this.source_status_id_str);
        }

        if (this.url != null) {
            writer.writeString("url",this.url);
        }

        if (this.video_info != null)
            writer.writeBinaryData("video_info", new BsonBinary(this.video_info.bsonSerialization()));

        if (this.additional_media_info != null)
            writer.writeBinaryData("additional_media_info", new BsonBinary(this.additional_media_info.bsonSerialization()));

        writer.writeInt64("source_status_id", this.source_status_id);
        writer.writeEndDocument();

        return outputBuffer.toByteArray();
    }

    public RootData bsonDeSerialization(byte[] buffData) {
        ByteBuffer buf = ByteBuffer.wrap(buffData);
        BsonBinaryReader reader = new BsonBinaryReader(buf);

        reader.readStartDocument();

        String currentName = reader.readName();
        if (currentName.equals("display_url")) {
            this.display_url = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("expanded_url")) {
            this.expanded_url = reader.readString();
            reader.readName();
        }
        this.id = reader.readInt64();

        int indices_size = reader.readInt32("indices_size");
        reader.readName("indices");
        reader.readStartArray();
        for (int i = 0; i < indices_size; i++) {
            this.indices.add(reader.readInt32());
        }
        reader.readEndArray();

        currentName = reader.readName();
        if (currentName.equals("media_url")) {
            this.media_url = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("media_url_https")) {
            this.media_url_https = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("sizes")) {
            this.sizes = new MediaSizesEntity();
            this.sizes.bsonDeSerialization(reader.readBinaryData().getData());
            currentName = reader.readName();
        }

        if (currentName.equals("type")) {
            this.type = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("source_status_id_str")) {
            this.source_status_id_str = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("url")) {
            this.url = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("video_info")) {
            this.video_info = new VideoEntity();
            this.video_info.bsonDeSerialization(reader.readBinaryData().getData());
            currentName = reader.readName();
        }

        if (currentName.equals("additional_media_info")) {
            this.additional_media_info = new AdditionalMediaInfoEntity();
            this.additional_media_info.bsonDeSerialization(reader.readBinaryData().getData());
            reader.readName();
        }
        this.source_status_id = reader.readInt64();

        reader.readEndDocument();

        return this;
    }

    public int compareTo(RootData o) {
        return 0;
    }
}