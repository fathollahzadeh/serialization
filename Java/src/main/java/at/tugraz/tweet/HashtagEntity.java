package at.tugraz.tweet;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import javax.json.*;
import com.google.flatbuffers.FlatBufferBuilder;
import at.tugraz.tweet.flatbuffers.HashtagEntityFBS;
import at.tugraz.tweet.flatbuffers.URLEntityFBS;
import at.tugraz.util.Base;
import at.tugraz.util.RootData;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;

public class HashtagEntity extends Base implements RootData {

	private List<Integer> indices;
	private String text;

	public HashtagEntity() {
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

		allocatedBufferSize += 4 * indices.size() + 4;

		// array fields
		ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);

		byteBuffer.putInt(textBytes.length);
		byteBuffer.put(textBytes);
		byteBuffer.putInt(indices.size());
		for(int i = 0; i < indices.size(); i++) {
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
		this.indices = new ArrayList<>();
		for(int i = 0; i < numberOfIndices; i++) {
			this.indices.add(byteBuffer.getInt());
		}

		return this;
	}

	public JsonObject jsonObjectBuilder() {

		JsonObjectBuilder hashtagEntityObjectBuilder = Json.createObjectBuilder();

		JsonArrayBuilder jsonIndicesArray = Json.createArrayBuilder();
		for(Integer integer : indices) {
			jsonIndicesArray.add(integer);
		}
		hashtagEntityObjectBuilder.add("indices", jsonIndicesArray);

		if(this.text != null && !this.text.isEmpty())
			hashtagEntityObjectBuilder.add("text", this.text);

		JsonObject hashtagEntityJsonObject = hashtagEntityObjectBuilder.build();

		return hashtagEntityJsonObject;
	}

	public HashtagEntity readJSONHashtagEntity(JsonObject jsonObject) {

		if(jsonObject.getJsonArray("indices") != null) {
			JsonArray indicesArray = jsonObject.getJsonArray("indices");
			for(int i = 0; i < indicesArray.size(); i++) {
				this.indices.add(indicesArray.getInt(i));
			}
		}

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

		writer.writeInt32("indices_size", this.indices.size());
		writer.writeName("indices");
		writer.writeStartArray();
		for(Integer i : this.indices) {
			writer.writeInt32(i);
		}
		writer.writeEndArray();

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

		int indices_size = reader.readInt32("indices_size");
		reader.readName("indices");
		reader.readStartArray();
		for(int i = 0; i < indices_size; i++) {
			this.indices.add(reader.readInt32());
		}
		reader.readEndArray();

		reader.readEndDocument();
		return this;
	}

	public int compareTo(RootData o) {
		return 0;
	}

	public int flatBuffersWriter(FlatBufferBuilder builder) {

		int textBuilder = this.text != null ? builder.createString(this.text) : 0;
		int[] indicesList = new int[this.indices.size()];
		for(int i = 0; i < this.indices.size(); i++) {
			indicesList[i] = this.indices.get(i);
		}
		int indicesBuilder = URLEntityFBS.createIndicesVector(builder, indicesList);

		HashtagEntityFBS.startHashtagEntityFBS(builder);
		HashtagEntityFBS.addText(builder, textBuilder);
		HashtagEntityFBS.addIndices(builder, indicesBuilder);
		int orc = HashtagEntityFBS.endHashtagEntityFBS(builder);
		return orc;
	}

	public HashtagEntity flatBuffersDeserialization(HashtagEntityFBS hashtagEntityFBS) {

		for(int i = 0; i < hashtagEntityFBS.indicesLength(); i++) {
			this.indices.add(hashtagEntityFBS.indices(i));
		}
		this.text = hashtagEntityFBS.text();
		return this;
	}
}

