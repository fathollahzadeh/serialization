package edu.bu.tweet;

import com.google.flatbuffers.FlatBufferBuilder;
import com.google.gson.Gson;
import edu.bu.tweet.flatbuffers.PollEntityFBS;
import edu.bu.util.Base;
import edu.bu.util.RootData;
import org.bson.BsonBinary;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;

import javax.json.*;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

public class PollEntity extends Base implements RootData {

	private List<OptionEntity> options;
	private String end_datetime;
	private String duration_minutes;

	public PollEntity() {
		this.options = new ArrayList<>();
	}

	public List<OptionEntity> getOptions() {
		return options;
	}

	public void setOptions(List<OptionEntity> options) {
		this.options = options;
	}

	public String getEnd_datetime() {
		return end_datetime;
	}

	public void setEnd_datetime(String end_datetime) {
		this.end_datetime = end_datetime;
	}

	public String getDuration_minutes() {
		return duration_minutes;
	}

	public void setDuration_minutes(String duration_minutes) {
		this.duration_minutes = duration_minutes;
	}

	@Override public List<RootData> generateObjects(int number) {
		return null;
	}

	@Override public RootData javaDefaultDeserialization(byte[] buf) {
		return null;
	}

	@Override public byte[] jsonSerialization() {
		return new byte[0];
	}

	@Override public RootData jsonDeserialization(byte[] buf) {
		return null;
	}

	@Override public byte[] jsonSerialization_withGZIP() {
		return new byte[0];
	}

	@Override public RootData jsonDeserialization_withGZIP(byte[] buf) {
		return null;
	}

	@Override public byte[] protocolBufferWrite() {
		return new byte[0];
	}

	@Override public RootData protocolBufferRead(byte[] buf) {
		return null;
	}

	@Override public byte[] writeByteBuffer() {

		int allocatedBufferSize = 0;

		List<byte[]> optionsBytes = new ArrayList<>();
		for(OptionEntity optionEntity : options) {
			byte[] optionBytes = optionEntity.writeByteBuffer();
			optionsBytes.add(optionBytes);
			allocatedBufferSize += 4;
		}
		allocatedBufferSize += 4;

		byte[] end_datetimeBytes = (end_datetime != null) ? end_datetime.getBytes() : new byte[0];
		allocatedBufferSize += end_datetimeBytes.length + 4;

		byte[] duration_minutesBytes = (duration_minutes != null) ? duration_minutes.getBytes() : new byte[0];
		allocatedBufferSize += duration_minutesBytes.length + 4;

		// array fields
		ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
		byteBuffer.putInt(optionsBytes.size());
		for(byte[] b : optionsBytes) {
			byteBuffer.putInt(b.length);
			byteBuffer.put(b);
		}
		byteBuffer.putInt(end_datetimeBytes.length);
		byteBuffer.put(end_datetimeBytes);
		byteBuffer.putInt(duration_minutesBytes.length);
		byteBuffer.put(duration_minutesBytes);

		return byteBuffer.array();
	}

	@Override public RootData readByteBuffer(byte[] buffData) {

		ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
		int stringSize;

		int numberOfOptions = byteBuffer.getInt();
		this.options = new ArrayList<>();

		for(int i = 0; i < numberOfOptions; i++) {
			byte[] optionBytes = new byte[byteBuffer.getInt()];
			byteBuffer.get(optionBytes, 0, optionBytes.length);
			OptionEntity optionEntity = new OptionEntity();
			optionEntity.readByteBuffer(optionBytes);
			this.options.add(optionEntity);

			Gson gson = new Gson();
			System.out.println(gson.toJson(options));
		}
		stringSize = byteBuffer.getInt();
		this.end_datetime = extractString(byteBuffer, stringSize);

		stringSize = byteBuffer.getInt();
		this.duration_minutes = extractString(byteBuffer, stringSize);

		return this;
	}

	public JsonObject jsonObjectBuilder() {

		JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
		if(this.options.size() > 0) {
			JsonArrayBuilder jsonOptionsArray = Json.createArrayBuilder();
			for(OptionEntity optionEntity : options) {
				jsonOptionsArray.add(optionEntity.jsonObjectBuilder());
			}
			objectBuilder.add("options", jsonOptionsArray);
		}

		if(this.end_datetime != null && !this.end_datetime.isEmpty()) {
			objectBuilder.add("end_datetime", this.end_datetime);
		}
		if(this.duration_minutes != null && !this.duration_minutes.isEmpty()) {
			objectBuilder.add("duration_minutes", this.duration_minutes);
		}

		JsonObject jsonObject = objectBuilder.build();
		return jsonObject;
	}

	public PollEntity readJSONPollEntity(JsonObject jsonObject) {

		if(jsonObject.getJsonArray("options") != null) {
			JsonArray jsonOptionsArray = jsonObject.getJsonArray("options");
			for(int i = 0; i < jsonOptionsArray.size(); i++) {
				JsonObject optionJsonObject = jsonOptionsArray.getJsonObject(i);
				this.options.add(new OptionEntity().readJSONOptionEntity(optionJsonObject));
			}
		}

		if(jsonObject.get("end_datetime") != null && jsonObject.get("end_datetime") != JsonValue.NULL) {
			this.end_datetime = jsonObject.getString("end_datetime");
		}

		if(jsonObject.get("duration_minutes") != null && jsonObject.get("duration_minutes") != JsonValue.NULL) {
			this.duration_minutes = jsonObject.getString("duration_minutes");
		}
		return this;
	}

	public byte[] bsonSerialization() {
		BasicOutputBuffer outputBuffer = new BasicOutputBuffer();
		BsonBinaryWriter writer = new BsonBinaryWriter(outputBuffer);

		writer.writeStartDocument();
		if(this.end_datetime != null)
			writer.writeString("end_datetime", this.end_datetime);

		if(this.duration_minutes != null)
			writer.writeString("duration_minutes", this.duration_minutes);

		writer.writeInt32("options_size", this.options.size());
		writer.writeName("options");
		writer.writeStartArray();
		for(OptionEntity optionEntity : this.options) {
			writer.writeBinaryData(new BsonBinary(optionEntity.bsonSerialization()));
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
		if(currentName.equals("end_datetime")) {
			this.end_datetime = reader.readString();
			currentName = reader.readName();
		}
		if(currentName.equals("duration_minutes")) {
			this.duration_minutes = reader.readString();
			reader.readName();
		}

		int list_size = reader.readInt32();
		reader.readName("options");
		reader.readStartArray();
		for(int i = 0; i < list_size; i++) {
			OptionEntity optionEntity = new OptionEntity();
			optionEntity.bsonDeSerialization(reader.readBinaryData().getData());
			this.options.add(optionEntity);
		}
		reader.readEndArray();

		reader.readEndDocument();
		return this;
	}

	@Override public int compareTo(RootData o) {
		return 0;
	}

	public int flatBuffersWriter(FlatBufferBuilder builder) {

		int end_datetimeBuilder = this.end_datetime != null ? builder.createString(this.end_datetime) : 0;
		int duration_minutesBuilder = this.duration_minutes != null ? builder.createString(this.duration_minutes) : 0;

		int[] optionsList = new int[this.options.size()];
		int i = 0;
		for(OptionEntity optionEntity : this.options) {
			optionsList[i] = optionEntity.flatBuffersWriter(builder);
			i++;
		}
		int optionsBuilder = PollEntityFBS.createOptionsVector(builder, optionsList);

		PollEntityFBS.startPollEntityFBS(builder);
		PollEntityFBS.addOptions(builder, optionsBuilder);
		PollEntityFBS.addEndDatetime(builder, end_datetimeBuilder);
		PollEntityFBS.addDurationMinutes(builder, duration_minutesBuilder);
		int orc = PollEntityFBS.endPollEntityFBS(builder);
		return orc;
	}

	public PollEntity flatBuffersDeserialization(PollEntityFBS pollEntityFBS) {

		for(int i = 0; i < pollEntityFBS.optionsLength(); i++) {
			OptionEntity optionEntity = new OptionEntity();
			optionEntity.flatBuffersDeserialization(pollEntityFBS.options(i));
			this.options.add(optionEntity);
		}

		this.end_datetime = pollEntityFBS.endDatetime();
		this.duration_minutes = pollEntityFBS.durationMinutes();

		return this;
	}
}
