package at.tugraz.tweet;

import java.nio.ByteBuffer;
import java.util.List;
import javax.json.*;

import com.google.flatbuffers.FlatBufferBuilder;
import at.tugraz.tweet.flatbuffers.SizeEntityFBS;
import at.tugraz.util.Base;
import at.tugraz.util.RootData;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;

public class SizeEntity extends Base implements RootData {

	private int w;
	private int h;
	private String resize;

	public int getW() {
		return w;
	}

	public void setW(int w) {
		this.w = w;
	}

	public int getH() {
		return h;
	}

	public void setH(int h) {
		this.h = h;
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

		allocatedBufferSize += 4;//width
		allocatedBufferSize += 4;//height

		// array fields
		ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
		byteBuffer.putInt(resizeBytes.length);
		byteBuffer.put(resizeBytes);
		byteBuffer.putInt(w);
		byteBuffer.putInt(h);

		return byteBuffer.array();
	}

	public RootData readByteBuffer(byte[] buffData) {
		ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
		int stringSize;

		stringSize = byteBuffer.getInt();
		this.resize = extractString(byteBuffer, stringSize);

		this.w = byteBuffer.getInt();
		this.h = byteBuffer.getInt();

		return this;
	}

	public JsonObject jsonObjectBuilder() {

		JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
		objectBuilder.add("width", this.w);
		objectBuilder.add("height", this.h);

		if(this.resize != null && !this.resize.isEmpty()) {
			objectBuilder.add("resize", this.resize);
		}
		JsonObject jsonObject = objectBuilder.build();
		return jsonObject;
	}

	public SizeEntity readJSONSizeEntity(JsonObject jsonObject) {
		this.w = jsonObject.getInt("width");
		this.h = jsonObject.getInt("height");

		if(jsonObject.get("resize") != null && jsonObject.get("resize") != JsonValue.NULL) {
			this.resize = jsonObject.getString("resize");
		}
		return this;
	}

	public byte[] bsonSerialization() {
		BasicOutputBuffer outputBuffer = new BasicOutputBuffer();
		BsonBinaryWriter writer = new BsonBinaryWriter(outputBuffer);

		writer.writeStartDocument();
		if(this.resize != null)
			writer.writeString("resize", this.resize);

		writer.writeInt32("width", this.w);
		writer.writeInt32("height", this.h);

		writer.writeEndDocument();

		return outputBuffer.toByteArray();
	}

	public RootData bsonDeSerialization(byte[] buffData) {
		ByteBuffer buf = ByteBuffer.wrap(buffData);
		BsonBinaryReader reader = new BsonBinaryReader(buf);

		reader.readStartDocument();

		String currentName = reader.readName();
		if(currentName.equals("resize")) {
			this.resize = reader.readString();
			reader.readName();
		}

		this.w = reader.readInt32();
		this.h = reader.readInt32("height");
		reader.readEndDocument();

		return this;
	}

	public int compareTo(RootData o) {
		return 0;
	}

	public int flatBuffersWriter(FlatBufferBuilder builder) {

		int resizeBuilder = this.resize != null ? builder.createString(this.resize) : 0;

		SizeEntityFBS.startSizeEntityFBS(builder);
		SizeEntityFBS.addWidth(builder, this.w);
		SizeEntityFBS.addHeight(builder, this.h);
		SizeEntityFBS.addResize(builder, resizeBuilder);
		int orc = SizeEntityFBS.endSizeEntityFBS(builder);
		return orc;
	}

	public SizeEntity flatBuffersDeserialization(SizeEntityFBS sizeEntityFBS) {

		this.w = sizeEntityFBS.width();
		this.h = sizeEntityFBS.height();
		this.resize = sizeEntityFBS.resize();
		return this;
	}
}

