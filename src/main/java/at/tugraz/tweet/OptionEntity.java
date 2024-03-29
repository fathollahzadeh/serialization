package at.tugraz.tweet;

import at.tugraz.tweet.flatbuffers.OptionEntityFBS;
import at.tugraz.util.Base;
import at.tugraz.util.RootData;
import com.google.flatbuffers.FlatBufferBuilder;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonValue;
import java.nio.ByteBuffer;
import java.util.List;

public class OptionEntity extends Base implements RootData {

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

		allocatedBufferSize += 4;//position

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
		this.position = byteBuffer.getInt();

		return this;
	}

	public JsonObject jsonObjectBuilder() {
		JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
		objectBuilder.add("position", this.position);
		if(this.text != null && !this.text.isEmpty()) {
			objectBuilder.add("text", this.text);
		}
		JsonObject jsonObject = objectBuilder.build();
		return jsonObject;
	}

	public OptionEntity readJSONOptionEntity(JsonObject jsonObject) {

		this.position = jsonObject.getInt("position");
		if(jsonObject.get("text") != null && jsonObject.get("text") != JsonValue.NULL) {
			this.text = jsonObject.getString("text");
		}
		return this;
	}

	public byte[] bsonSerialization() {
		BasicOutputBuffer outputBuffer = new BasicOutputBuffer();
		BsonBinaryWriter writer = new BsonBinaryWriter(outputBuffer);

		writer.writeStartDocument();
		if(this.text != null) {
			writer.writeString("text", this.text);
		}
		writer.writeInt32("position", this.position);
		writer.writeEndDocument();

		return outputBuffer.toByteArray();

	}

	public RootData bsonDeSerialization(byte[] buffData) {
		ByteBuffer buf = ByteBuffer.wrap(buffData);
		BsonBinaryReader reader = new BsonBinaryReader(buf);

		reader.readStartDocument();

		String currentName = reader.readName();
		if(currentName.equals("text")) {
			this.text = reader.readString();
		}
		this.position = reader.readInt32();

		reader.readEndDocument();

		return this;
	}

	public int compareTo(RootData o) {
		return 0;
	}

	public int flatBuffersWriter(FlatBufferBuilder builder) {

		int textBuilder = this.text != null ? builder.createString(this.text) : 0;

		OptionEntityFBS.startOptionEntityFBS(builder);
		OptionEntityFBS.addPosition(builder, this.position);
		OptionEntityFBS.addText(builder, textBuilder);

		int orc = OptionEntityFBS.endOptionEntityFBS(builder);
		return orc;
	}

	public OptionEntity flatBuffersDeserialization(OptionEntityFBS optionEntityFBS) {

		this.position = optionEntityFBS.position();
		this.text = optionEntityFBS.text();
		return this;
	}
}
