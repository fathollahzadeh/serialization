package at.tugraz.tweet;

import com.google.flatbuffers.FlatBufferBuilder;
import at.tugraz.tweet.flatbuffers.MatchingRulesEntityFBS;
import at.tugraz.util.Base;
import at.tugraz.util.RootData;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;
import javax.json.*;
import java.nio.ByteBuffer;
import java.util.List;

public class MatchingRulesEntity extends Base implements RootData {
	private String tag;
	private long id;
	private String id_str;

	public String getTag() {
		return tag;
	}

	public void setTag(String tag) {
		this.tag = tag;
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

		byte[] tagBytes = (tag != null) ? tag.getBytes() : new byte[0];
		allocatedBufferSize += tagBytes.length + 4;

		byte[] id_strBytes = (id_str != null) ? id_str.getBytes() : new byte[0];
		allocatedBufferSize += id_strBytes.length + 4;

		allocatedBufferSize += 8;// id

		// array fields
		ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
		byteBuffer.putInt(tagBytes.length);
		byteBuffer.put(tagBytes);
		byteBuffer.putInt(id_strBytes.length);
		byteBuffer.put(id_strBytes);
		byteBuffer.putLong(id);

		return byteBuffer.array();
	}

	public RootData readByteBuffer(byte[] buffData) {
		ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
		int stringSize;

		stringSize = byteBuffer.getInt();
		this.tag = extractString(byteBuffer, stringSize);
		stringSize = byteBuffer.getInt();
		this.id_str = extractString(byteBuffer, stringSize);
		this.id = byteBuffer.getLong();
		return this;
	}

	public int compareTo(RootData o) {
		return 0;
	}

	public JsonObject jsonObjectBuilder() {

		JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
		if(this.tag != null && !this.tag.isEmpty()) {
			objectBuilder.add("tag", this.tag);
		}

		objectBuilder.add("id", this.id);

		if(this.id_str != null && !this.id_str.isEmpty()) {
			objectBuilder.add("id_str", this.id_str);
		}
		JsonObject jsonObject = objectBuilder.build();
		return jsonObject;
	}

	public MatchingRulesEntity readJSONMatchingRulesEntity(JsonObject jsonObject) {
		if(jsonObject.get("tag") != null && jsonObject.get("tag") != JsonValue.NULL) {
			this.tag = jsonObject.getString("tag");
		}
		this.id = Long.parseLong(jsonObject.getJsonNumber("id").toString());

		if(jsonObject.get("id_str") != null && jsonObject.get("id_str") != JsonValue.NULL) {
			this.id_str = jsonObject.getString("id_str");
		}

		return this;
	}

	public byte[] bsonSerialization() {
		BasicOutputBuffer outputBuffer = new BasicOutputBuffer();
		BsonBinaryWriter writer = new BsonBinaryWriter(outputBuffer);

		writer.writeStartDocument();

		if(this.tag != null) {
			writer.writeString("tag", this.tag);
		}

		if(this.id_str != null) {
			writer.writeString("id_str", this.id_str);
		}

		writer.writeInt64("id", this.id);
		writer.writeEndDocument();

		return outputBuffer.toByteArray();

	}

	public RootData bsonDeSerialization(byte[] buffData) {
		ByteBuffer buf = ByteBuffer.wrap(buffData);
		BsonBinaryReader reader = new BsonBinaryReader(buf);

		reader.readStartDocument();
		String currentName = reader.readName();
		if(currentName.equals("tag")) {
			this.tag = reader.readString();
			currentName = reader.readName();
		}

		if(currentName.equals("id_str")) {
			this.id_str = reader.readString();
			reader.readName();
		}

		this.id = reader.readInt64();

		reader.readEndDocument();

		return this;
	}

	public int flatBuffersWriter(FlatBufferBuilder builder) {

		int tagBuilder = this.tag != null ? builder.createString(this.tag) : 0;
		int id_strBuilder = this.id_str != null ? builder.createString(this.id_str) : 0;

		MatchingRulesEntityFBS.startMatchingRulesEntityFBS(builder);
		MatchingRulesEntityFBS.addTag(builder, tagBuilder);
		MatchingRulesEntityFBS.addId(builder, this.id);
		MatchingRulesEntityFBS.addIdStr(builder, id_strBuilder);
		int orc = MatchingRulesEntityFBS.endMatchingRulesEntityFBS(builder);
		return orc;
	}

	public MatchingRulesEntity flatBuffersDeserialization(MatchingRulesEntityFBS matchingRulesEntityFBS) {

		this.tag = matchingRulesEntityFBS.tag();
		this.id = matchingRulesEntityFBS.id();
		this.id_str = matchingRulesEntityFBS.idStr();
		return this;
	}
}
