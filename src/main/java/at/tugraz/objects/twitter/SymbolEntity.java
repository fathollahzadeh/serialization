package at.tugraz.objects.twitter;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import javax.json.*;

import com.google.flatbuffers.FlatBufferBuilder;
import at.tugraz.tweet.flatbuffers.SymbolEntityFBS;
import at.tugraz.tweet.flatbuffers.URLEntityFBS;
import at.tugraz.util.Base;
import at.tugraz.util.RootData;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;

public class SymbolEntity extends Base implements RootData {

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
		for(int i = 0; i < numberOfIndices; i++) {
			this.indices.add(byteBuffer.getInt());
		}
		return this;
	}

	public JsonObject jsonObjectBuilder() {

		JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
		JsonArrayBuilder jsonIndicesArray = Json.createArrayBuilder();
		for(Integer integer : indices) {
			jsonIndicesArray.add(integer);
		}
		objectBuilder.add("indices", jsonIndicesArray);

		if(this.text != null && !this.text.isEmpty()) {
			objectBuilder.add("text", this.text);
		}
		JsonObject jsonObject = objectBuilder.build();
		return jsonObject;
	}

	public SymbolEntity readJSONSymbolEntity(JsonObject jsonObject) {
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
			reader.readName();
		}

		int indices_size = reader.readInt32();
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

		SymbolEntityFBS.startSymbolEntityFBS(builder);
		SymbolEntityFBS.addIndices(builder, indicesBuilder);
		SymbolEntityFBS.addText(builder, textBuilder);
		int orc = SymbolEntityFBS.endSymbolEntityFBS(builder);
		return orc;
	}

	public SymbolEntity flatBuffersDeserialization(SymbolEntityFBS symbolEntityFBS) {

		for(int i = 0; i < symbolEntityFBS.indicesLength(); i++) {
			this.indices.add(symbolEntityFBS.indices(i));
		}
		this.text = symbolEntityFBS.text();

		return this;
	}
}

