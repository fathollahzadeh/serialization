package at.tugraz.tweet;

import at.tugraz.tweet.flatbuffers.EntitiesFBS;
import at.tugraz.tweet.flatbuffers.ExtendedEntitiesFBS;
import at.tugraz.util.Base;
import at.tugraz.util.RootData;
import com.esotericsoftware.kryo.util.Null;
import com.google.flatbuffers.FlatBufferBuilder;
import org.bson.BsonBinary;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;

import javax.json.*;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.List;

public class ExtendedTweet extends Base implements RootData {

	private String full_text;
	private List<Integer> display_text_range;
	private  Entities entities;
	private ExtendedEntities extendedEntities;

	public String getFull_text() {
		return full_text;
	}

	public void setFull_text(String full_text) {
		this.full_text = full_text;
	}

	public List<Integer> getDisplay_text_range() {
		return display_text_range;
	}

	public void setDisplay_text_range(List<Integer> display_text_range) {
		this.display_text_range = display_text_range;
	}

	public Entities getEntities() {
		return entities;
	}

	public void setEntities(Entities entities) {
		this.entities = entities;
	}

	public ExtendedEntities getExtendedEntities() {
		return extendedEntities;
	}

	public void setExtendedEntities(ExtendedEntities extendedEntities) {
		this.extendedEntities = extendedEntities;
	}

	public ExtendedTweet() {
		this.display_text_range = new ArrayList<>();
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

		byte[] fullTextBytes = (full_text != null) ? full_text.getBytes() : new byte[0];
		allocatedBufferSize += fullTextBytes.length + 4;

		allocatedBufferSize += 4 * display_text_range.size() + 4;

		byte[] entitiesBytes = entities.writeByteBuffer();
		allocatedBufferSize += entitiesBytes.length + 4;

		byte[] extendedEntitiesBytes = extendedEntities.writeByteBuffer();
		allocatedBufferSize += extendedEntitiesBytes.length + 4;

		// array fields
		ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
		byteBuffer.putInt(fullTextBytes.length);
		byteBuffer.put(fullTextBytes);
		byteBuffer.putInt(display_text_range.size());
		for (int i:display_text_range)
			byteBuffer.putInt(i);
		byteBuffer.putInt(entitiesBytes.length);
		byteBuffer.put(entitiesBytes);
		byteBuffer.putInt(extendedEntitiesBytes.length);
		byteBuffer.put(extendedEntitiesBytes);

		return byteBuffer.array();
	}

	public RootData readByteBuffer(byte[] buffData) {
		ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);

		int stringSize;

		stringSize = byteBuffer.getInt();
		this.full_text = extractString(byteBuffer, stringSize);

		int numberSize = byteBuffer.getInt();
		this.display_text_range = new ArrayList<>();
		for(int i = 0; i < numberSize; i++) {
			this.display_text_range.add(byteBuffer.getInt());
		}

		byte[] entitiesBytes = new byte[byteBuffer.getInt()];
		byteBuffer.get(entitiesBytes, 0, entitiesBytes.length);
		this.entities = new Entities();
		this.entities.readByteBuffer(entitiesBytes);

		byte[] extendedEntitiesBytes = new byte[byteBuffer.getInt()];
		byteBuffer.get(extendedEntitiesBytes, 0, extendedEntitiesBytes.length);
		this.extendedEntities = new ExtendedEntities();
		this.extendedEntities.readByteBuffer(extendedEntitiesBytes);
		return this;
	}

	public int compareTo(RootData o) {
		return 0;
	}

	public JsonObject jsonObjectBuilder() {
		JsonObjectBuilder objectBuilder = Json.createObjectBuilder();

		if(this.full_text != null && !this.full_text.isEmpty())
			objectBuilder.add("full_text", this.full_text);

		JsonArrayBuilder jsonDisplayTextRangeArray = Json.createArrayBuilder();
		for(Integer integer : display_text_range) {
			jsonDisplayTextRangeArray.add(integer);
		}
		objectBuilder.add("display_text_range", jsonDisplayTextRangeArray);

		if(this.entities != null)
			objectBuilder.add("entities", this.entities.jsonObjectBuilder());

		if(this.extendedEntities != null)
			objectBuilder.add("extended_entities", this.extendedEntities.jsonObjectBuilder());

		JsonObject jsonObject = objectBuilder.build();
		return jsonObject;
	}

	public ExtendedTweet readJSONExtendedTweet(JsonObject jsonObject) {

		if(jsonObject.get("full_text") != null && jsonObject.get("full_text") != JsonValue.NULL) {
			this.full_text = jsonObject.getString("full_text");
		}

		if(jsonObject.getJsonArray("display_text_range") != null) {
			JsonArray displayTextRangeArray = jsonObject.getJsonArray("display_text_range");
			for(int i = 0; i < displayTextRangeArray.size(); i++) {
				this.display_text_range.add(displayTextRangeArray.getInt(i));
			}
		}

		if(jsonObject.getJsonObject("entities") != null && jsonObject.getJsonObject("entities") != JsonValue.NULL) {
			JsonObject entityJsonObject = jsonObject.getJsonObject("entities");
			this.entities = new Entities().readJSONEntities(entityJsonObject);
		}

		if(jsonObject.getJsonObject("extended_entities") != null && jsonObject.getJsonObject("extended_entities") != JsonValue.NULL) {
			JsonObject extendedEntityJsonObject = jsonObject.getJsonObject("extended_entities");
			this.extendedEntities = new ExtendedEntities().readJSONExtendedEntities(extendedEntityJsonObject);
		}
		return this;
	}

	public byte[] bsonSerialization() {
		BasicOutputBuffer outputBuffer = new BasicOutputBuffer();
		BsonBinaryWriter writer = new BsonBinaryWriter(outputBuffer);

		writer.writeStartDocument();

		if(this.full_text != null) {
			writer.writeString("full_text", this.full_text);
		}

		writer.writeInt32("display_text_range_size", this.display_text_range.size());
		writer.writeName("display_text_range");
		writer.writeStartArray();
		for(Integer i : this.display_text_range) {
			writer.writeInt32(i);
		}

		if (entities != null) {
			writer.writeName("entities");
			writer.writeBinaryData(new BsonBinary(this.entities.bsonSerialization()));
		}

		if (extendedEntities != null) {
			writer.writeName("extended_entities");
			writer.writeBinaryData(new BsonBinary(this.extendedEntities.bsonSerialization()));
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
		if(currentName.equals("full_text")) {
			this.full_text = reader.readString();
		}

		int display_text_range_size = reader.readInt32("display_text_range_size");
		reader.readName("display_text_range");
		reader.readStartArray();
		for(int i = 0; i < display_text_range_size; i++) {
			this.display_text_range.add(reader.readInt32());
		}

		if(currentName.equals("entities")) {
			this.entities = new Entities();
			this.entities.bsonDeSerialization(reader.readBinaryData().getData());
			reader.readName();
		}

		if(currentName.equals("extended_entities")) {
			this.extendedEntities = new ExtendedEntities();
			this.extendedEntities.bsonDeSerialization(reader.readBinaryData().getData());
			reader.readName();
		}

		reader.readEndArray();
		reader.readEndDocument();
		return this;
	}

	public int flatBuffersWriter(FlatBufferBuilder builder) {
		int[] mediaList = new int[this.media.size()];
		int i = 0;
		for(MediaEntity mediaEntity : this.media) {
			mediaList[i] = mediaEntity.flatBuffersWriter(builder);
			i++;
		}
		int mediaBuilder = EntitiesFBS.createMediaVector(builder, mediaList);

		ExtendedEntitiesFBS.startExtendedEntitiesFBS(builder);
		EntitiesFBS.addMedia(builder, mediaBuilder);
		int orc = ExtendedEntitiesFBS.endExtendedEntitiesFBS(builder);
		return orc;
	}

	public ExtendedTweet flatBuffersDeserialization(ExtendedEntitiesFBS extendedEntitiesFBS) {

		for(int i = 0; i < extendedEntitiesFBS.mediaLength(); i++) {
			MediaEntity mediaEntity = new MediaEntity();
			mediaEntity.flatBuffersDeserialization(extendedEntitiesFBS.media(i));
			this.media.add(mediaEntity);
		}
		return this;
	}
}
