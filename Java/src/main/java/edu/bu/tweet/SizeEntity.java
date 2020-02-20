package edu.bu.tweet;

import java.nio.ByteBuffer;
import java.util.List;
import javax.json.*;
import org.apache.log4j.Logger;
import edu.bu.util.Base;
import edu.bu.util.RootData;

public class SizeEntity extends Base implements RootData {

	private static final long serialVersionUID = -7101997427441983771L;
	static Logger logger = Logger.getLogger(SizeEntity.class);

	private int width;
    private int height;
    private String resize;

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public String getResize() {
        return resize;
    }

    public void setResize(String resize) {
        this.resize = resize;
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

        byte[] resizeBytes = (resize != null) ? resize.getBytes() : new byte[0];
        allocatedBufferSize += resizeBytes.length + 4;

        allocatedBufferSize+=4;//width
        allocatedBufferSize+=4;//height

        // array fields
        ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
        byteBuffer.putInt(resizeBytes.length);
        byteBuffer.put(resizeBytes);
        byteBuffer.putInt(width);
        byteBuffer.putInt(height);

        return byteBuffer.array();
    }

    public RootData readByteBuffer(byte[] buffData) {
        ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
        int stringSize;

        stringSize = byteBuffer.getInt();
        this.resize = extractString(byteBuffer, stringSize);

        this.width=byteBuffer.getInt();
        this.height=byteBuffer.getInt();

        return this;
    }

    public JsonObject jsonObjectBuilder() {

        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
        objectBuilder.add("width",this.width);
        objectBuilder.add("height",this.height);

        if (this.resize != null && !this.resize.isEmpty()) {
            objectBuilder.add("resize", this.resize);
        }
        JsonObject jsonObject = objectBuilder.build();
        return jsonObject;
    }

    public SizeEntity readJSONSizeEntity(JsonObject jsonObject) {
        this.width=jsonObject.getInt("width");
        this.height=jsonObject.getInt("height");

        if (jsonObject.get("resize") != null && jsonObject.get("resize") != JsonValue.NULL) {
            this.resize = jsonObject.getString("resize");
        }
        return  this;
    }

    public int compareTo(RootData o) {
        return 0;
    }
}

