package edu.bu.tweet;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import javax.json.*;
import org.apache.log4j.Logger;
import edu.rice.dmodel.Base;
import edu.rice.dmodel.RootData;


public class UserMentionEntity extends Base implements RootData {

	private static final long serialVersionUID = -6946185052925660706L;
	static Logger logger = Logger.getLogger(UserMentionEntity.class);

    private long id;
    private String id_str;
    private List<Integer> indices;
    private String name;
    private String screen_name;

    public UserMentionEntity() {
        this.indices=new ArrayList<>();
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

    public List<Integer> getIndices() {
        return indices;
    }

    public void setIndices(List<Integer> indices) {
        this.indices = indices;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getScreen_name() {
        return screen_name;
    }

    public void setScreen_name(String screen_name) {
        this.screen_name = screen_name;
    }

    @Override
    public List<RootData> generateObjects(int number) {
        return null;
    }

    @Override
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
        byte[] id_strBytes = (id_str != null) ? id_str.getBytes() : new byte[0];
        allocatedBufferSize += id_strBytes.length + 4;

        allocatedBufferSize += 4 * (indices.size() + 1); //indices * sizeof integer

        byte[] nameBytes = (name != null) ? name.getBytes() : new byte[0];
        allocatedBufferSize += nameBytes.length + 4;

        byte[] screen_nameBytes = (screen_name != null) ? screen_name.getBytes() : new byte[0];
        allocatedBufferSize += screen_nameBytes.length + 4;

        allocatedBufferSize+=8;// id

        // array fields
        ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
        byteBuffer.putLong(id);
        byteBuffer.putInt(id_strBytes.length);
        byteBuffer.put(id_strBytes);

        byteBuffer.putInt(indices.size());
        for (int i=0;i<indices.size();i++){
            byteBuffer.putInt(indices.get(i));
        }

        byteBuffer.putInt(nameBytes.length);
        byteBuffer.put(nameBytes);
        byteBuffer.putInt(screen_nameBytes.length);
        byteBuffer.put(screen_nameBytes);
        return byteBuffer.array();
    }

    public RootData readByteBuffer(byte[] buffData) {

        ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
        int stringSize;

        this.id=byteBuffer.getLong();

        stringSize = byteBuffer.getInt();
        this.id_str = extractString(byteBuffer, stringSize);

        int numberOfIndices = byteBuffer.getInt();
        for (int i = 0; i < numberOfIndices; i++) {
            this.indices.add(byteBuffer.getInt());
        }
        stringSize = byteBuffer.getInt();
        this.name = extractString(byteBuffer, stringSize);

        stringSize = byteBuffer.getInt();
        this.screen_name = extractString(byteBuffer, stringSize);

        return this;
    }
    public JsonObject jsonObjectBuilder() {

        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
        objectBuilder.add("id",this.id);

        if (this.id_str != null && !this.id_str.isEmpty()) {
            objectBuilder.add("id_str", this.id_str);
        }

        JsonArrayBuilder jsonIndicesArray = Json.createArrayBuilder();
        for (Integer integer : indices) {
            jsonIndicesArray.add(integer);
        }
        objectBuilder.add("indices", jsonIndicesArray);

        if (this.name != null && !this.name.isEmpty()) {
            objectBuilder.add("name", this.name);
        }
        if (this.screen_name != null && !this.screen_name.isEmpty()) {
            objectBuilder.add("screen_name", this.screen_name);
        }
        JsonObject jsonObject = objectBuilder.build();
        return jsonObject;
    }

    public UserMentionEntity readJSONUserMentionEntity(JsonObject jsonObject) {

        this.id=Long.parseLong(jsonObject.getJsonNumber("id").toString());

        if (jsonObject.get("id_str") != null && jsonObject.get("id_str") != JsonValue.NULL) {
            this.id_str = jsonObject.getString("id_str");
        }

        if (jsonObject.getJsonArray("indices") != null) {
            JsonArray indicesArray = jsonObject.getJsonArray("indices");
            for (int i = 0; i < indicesArray.size(); i++) {
                this.indices.add(indicesArray.getInt(i));
            }
        }
        if (jsonObject.get("name") != null && jsonObject.get("name") != JsonValue.NULL) {
            this.name = jsonObject.getString("name");
        }
        if (jsonObject.get("screen_name") != null && jsonObject.get("screen_name") != JsonValue.NULL) {
            this.screen_name = jsonObject.getString("screen_name");
        }
        return  this;
    }

    public int compareTo(RootData o) {
        return 0;
    }
}