package at.tugraz.tweet;

import com.google.flatbuffers.FlatBufferBuilder;
import at.tugraz.tweet.flatbuffers.VideoEntityFBS;
import at.tugraz.util.Base;
import at.tugraz.util.RootData;
import org.bson.BsonBinary;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;

import javax.json.*;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

public class VideoEntity extends Base implements RootData {

	private List<Integer> aspect_ratio;
	private int duration_millis;
	private List<VariantEntity> variants;

	public VideoEntity() {
		this.aspect_ratio = new ArrayList<>();
		this.variants = new ArrayList<>();
	}

	public List<Integer> getAspect_ratio() {
		return aspect_ratio;
	}

	public void setAspect_ratio(List<Integer> aspect_ratio) {
		this.aspect_ratio = aspect_ratio;
	}

	public int getDuration_millis() {
		return duration_millis;
	}

	public void setDuration_millis(int duration_millis) {
		this.duration_millis = duration_millis;
	}

	public List<VariantEntity> getVariants() {
		return variants;
	}

	public void setVariants(List<VariantEntity> variants) {
		this.variants = variants;
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
		allocatedBufferSize += 4 * (aspect_ratio.size() + 1); //aspect_ratio
		allocatedBufferSize += 4;

		List<byte[]> variantsBytes = new ArrayList<>();
		for(VariantEntity variantEntity : variants) {
			byte[] variantBytes = variantEntity.writeByteBuffer();
			allocatedBufferSize += variantBytes.length;
			allocatedBufferSize += 4;
			variantsBytes.add(variantBytes);
		}
		allocatedBufferSize += 4;

		allocatedBufferSize += 4;//duration_millis

		// array fields
		ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
		byteBuffer.putInt(aspect_ratio.size());
		for(int i = 0; i < aspect_ratio.size(); i++) {
			byteBuffer.putInt(aspect_ratio.get(i));
		}
		byteBuffer.putInt(duration_millis);

		byteBuffer.putInt(variantsBytes.size());
		for(byte[] b : variantsBytes) {
			byteBuffer.putInt(b.length);
			byteBuffer.put(b);
		}

		return byteBuffer.array();
	}

	public RootData readByteBuffer(byte[] buffData) {
		ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);

		int numberOfAspect_ratio = byteBuffer.getInt();
		for(int i = 0; i < numberOfAspect_ratio; i++) {
			this.aspect_ratio.add(byteBuffer.getInt());
		}

		this.duration_millis = byteBuffer.getInt();

		int numberOfVariants = byteBuffer.getInt();
		for(int i = 0; i < numberOfVariants; i++) {
			byte[] variantBytes = new byte[byteBuffer.getInt()];
			byteBuffer.get(variantBytes, 0, variantBytes.length);
			VariantEntity variantEntity = new VariantEntity();
			variantEntity.readByteBuffer(variantBytes);
			this.variants.add(variantEntity);
		}
		return this;
	}

	public JsonObject jsonObjectBuilder() {
		JsonObjectBuilder objectBuilder = Json.createObjectBuilder();

		if(this.aspect_ratio != null) {
			JsonArrayBuilder jsonAspect_ratioArray = Json.createArrayBuilder();
			for(Integer integer : aspect_ratio) {
				jsonAspect_ratioArray.add(integer);
			}
			objectBuilder.add("aspect_ratio", jsonAspect_ratioArray);
		}

		objectBuilder.add("duration_millis", this.duration_millis);

		if(this.variants != null) {
			JsonArrayBuilder jsonVariantsArray = Json.createArrayBuilder();
			for(VariantEntity variantEntity : variants) {
				jsonVariantsArray.add(variantEntity.jsonObjectBuilder());
			}
			objectBuilder.add("variants", jsonVariantsArray);
		}
		JsonObject jsonObject = objectBuilder.build();
		return jsonObject;
	}

	public VideoEntity readJSONVideoEntity(JsonObject jsonObject) {
		if(jsonObject.getJsonArray("aspect_ratio") != null) {
			JsonArray aspect_ratioArray = jsonObject.getJsonArray("aspect_ratio");
			for(int i = 0; i < aspect_ratioArray.size(); i++) {
				this.aspect_ratio.add(aspect_ratioArray.getInt(i));
			}
		}
		this.duration_millis = jsonObject.getInt("duration_millis");

		if(jsonObject.getJsonArray("variants") != null) {
			JsonArray jsonVariantsArray = jsonObject.getJsonArray("variants");
			for(int i = 0; i < jsonVariantsArray.size(); i++) {
				JsonObject variantsJsonObject = jsonVariantsArray.getJsonObject(i);
				this.variants.add(new VariantEntity().readJSONVariantEntity(variantsJsonObject));
			}
		}
		return this;
	}

	public byte[] bsonSerialization() {
		BasicOutputBuffer outputBuffer = new BasicOutputBuffer();
		BsonBinaryWriter writer = new BsonBinaryWriter(outputBuffer);

		writer.writeStartDocument();

		writer.writeInt32("aspect_ratio_size", this.aspect_ratio.size());
		writer.writeName("aspect_ratio");
		writer.writeStartArray();
		for(Integer i : this.aspect_ratio) {
			writer.writeInt32(i);
		}
		writer.writeEndArray();

		writer.writeInt32("duration_millis", this.duration_millis);

		writer.writeInt32("variants_size", this.variants.size());
		writer.writeName("variants");
		writer.writeStartArray();
		for(VariantEntity variantEntity : this.variants) {
			writer.writeBinaryData(new BsonBinary(variantEntity.bsonSerialization()));
		}
		writer.writeEndArray();

		writer.writeEndDocument();
		return outputBuffer.toByteArray();
	}

	public RootData bsonDeSerialization(byte[] buffData) {
		ByteBuffer buf = ByteBuffer.wrap(buffData);
		BsonBinaryReader reader = new BsonBinaryReader(buf);

		reader.readStartDocument();

		int aspect_ratio_size = reader.readInt32("aspect_ratio_size");
		reader.readName("aspect_ratio");
		reader.readStartArray();
		for(int i = 0; i < aspect_ratio_size; i++) {
			this.aspect_ratio.add(reader.readInt32());
		}
		reader.readEndArray();

		this.duration_millis = reader.readInt32();

		int variants_size = reader.readInt32("variants_size");
		reader.readName("variants");
		reader.readStartArray();
		for(int i = 0; i < variants_size; i++) {
			VariantEntity variantEntity = new VariantEntity();
			variantEntity.bsonDeSerialization(reader.readBinaryData().getData());
			this.variants.add(variantEntity);
		}
		reader.readEndArray();
		reader.readEndDocument();
		return this;
	}

	public int compareTo(RootData o) {
		return 0;
	}

	public int flatBuffersWriter(FlatBufferBuilder builder) {

		int[] aspect_ratioList = new int[this.aspect_ratio.size()];
		for(int i = 0; i < this.aspect_ratio.size(); i++) {
			aspect_ratioList[i] = this.aspect_ratio.get(i);
		}
		int aspect_ratioBuilder = VideoEntityFBS.createAspectRatioVector(builder, aspect_ratioList);

		int[] variantsList = new int[this.variants.size()];
		int i = 0;
		for(VariantEntity variantEntity : this.variants) {
			variantsList[i] = variantEntity.flatBuffersWriter(builder);
			i++;
		}
		int variantsBuilder = VideoEntityFBS.createVariantsVector(builder, variantsList);

		VideoEntityFBS.startVideoEntityFBS(builder);

		VideoEntityFBS.addAspectRatio(builder, aspect_ratioBuilder);
		VideoEntityFBS.addDurationMillis(builder, this.duration_millis);
		VideoEntityFBS.addVariants(builder, variantsBuilder);
		int orc = VideoEntityFBS.endVideoEntityFBS(builder);
		return orc;
	}

	public VideoEntity flatBuffersDeserialization(VideoEntityFBS videoEntityFBS) {

		for(int i = 0; i < videoEntityFBS.aspectRatioLength(); i++) {
			this.aspect_ratio.add(videoEntityFBS.aspectRatio(i));
		}

		this.duration_millis = videoEntityFBS.durationMillis();

		for(int i = 0; i < videoEntityFBS.variantsLength(); i++) {
			VariantEntity variantEntity = new VariantEntity();
			variantEntity.flatBuffersDeserialization(videoEntityFBS.variants(i));
			this.variants.add(variantEntity);
		}

		return this;
	}
}
