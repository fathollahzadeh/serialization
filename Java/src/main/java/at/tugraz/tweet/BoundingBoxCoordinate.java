package at.tugraz.tweet;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import javax.json.*;

import com.google.flatbuffers.FlatBufferBuilder;
import at.tugraz.tweet.flatbuffers.BoundingBoxCoordinateFBS;
import at.tugraz.tweet.flatbuffers.DoubleList1;
import at.tugraz.tweet.flatbuffers.DoubleList2;
import at.tugraz.util.Base;
import at.tugraz.util.RootData;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;

public class BoundingBoxCoordinate extends Base implements RootData {

	private String type;
	private List<List<List<Double>>> coordinates;

	public BoundingBoxCoordinate() {
		this.coordinates = new ArrayList<>();
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public List<List<List<Double>>> getCoordinates() {
		return coordinates;
	}

	public void setCoordinates(List<List<List<Double>>> coordinates) {
		this.coordinates = coordinates;
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

		byte[] typeBytes = (type != null) ? type.getBytes() : new byte[0];
		allocatedBufferSize += typeBytes.length + 4;

		allocatedBufferSize += 4;
		if(this.coordinates.size() > 0) {
			for(int i = 0; i < coordinates.size(); i++) {
				allocatedBufferSize += 4;
				for(int j = 0; j < coordinates.get(i).size(); j++) {
					allocatedBufferSize += 8 * coordinates.get(i).get(j).size();
					allocatedBufferSize += 4;
				}
			}
		}

		// array fields
		ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
		byteBuffer.putInt(typeBytes.length);
		byteBuffer.put(typeBytes);
		byteBuffer.putInt(coordinates.size());
		for(int i = 0; i < coordinates.size(); i++) {
			byteBuffer.putInt(coordinates.get(i).size());
			for(int j = 0; j < coordinates.get(i).size(); j++) {
				byteBuffer.putInt(coordinates.get(i).get(j).size());
				for(int k = 0; k < coordinates.get(i).get(j).size(); k++) {
					byteBuffer.putDouble(coordinates.get(i).get(j).get(k));
				}
			}
		}

		return byteBuffer.array();
	}

	public RootData readByteBuffer(byte[] buffData) {

		ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
		int stringSize;

		stringSize = byteBuffer.getInt();
		this.type = extractString(byteBuffer, stringSize);

		int numberOfCoordinates = byteBuffer.getInt();
		if(numberOfCoordinates != 0) {
			this.coordinates = new ArrayList<>();
			for(int i = 0; i < numberOfCoordinates; i++) {
				List<List<Double>> list2 = new ArrayList<>();
				int numberOfList2 = byteBuffer.getInt();
				for(int j = 0; j < numberOfList2; j++) {
					List<Double> list1 = new ArrayList<>();
					int numberOfList1 = byteBuffer.getInt();
					for(int k = 0; k < numberOfList1; k++) {
						list1.add(byteBuffer.getDouble());
					}
					list2.add(list1);
				}
				this.coordinates.add(list2);
			}
		}
		else {
			this.coordinates = new ArrayList<>();
		}
		return this;
	}

	public JsonObject jsonObjectBuilder() {
		JsonObjectBuilder boundingBoxCoordinateObjectBuilder = Json.createObjectBuilder();
		if(this.type != null && !this.type.isEmpty()) {
			boundingBoxCoordinateObjectBuilder.add("type", this.type);
		}

		JsonArrayBuilder jsonCoordinatesArray1 = Json.createArrayBuilder();
		JsonArrayBuilder jsonCoordinatesArray2;
		JsonArrayBuilder jsonCoordinatesArray3;

		for(int i = 0; i < this.coordinates.size(); i++) {
			jsonCoordinatesArray2 = Json.createArrayBuilder();
			for(int j = 0; j < this.coordinates.get(i).size(); j++) {
				jsonCoordinatesArray3 = Json.createArrayBuilder();
				for(Double d : this.coordinates.get(i).get(j)) {
					jsonCoordinatesArray3.add(d);
				}
				jsonCoordinatesArray2.add(jsonCoordinatesArray3);
			}
			jsonCoordinatesArray1.add(jsonCoordinatesArray2);
		}

		boundingBoxCoordinateObjectBuilder.add("coordinates", jsonCoordinatesArray1);
		JsonObject boundingBoxCoordinateObjectBuilderJsonObject = boundingBoxCoordinateObjectBuilder.build();
		return boundingBoxCoordinateObjectBuilderJsonObject;
	}

	public BoundingBoxCoordinate readJSONBoundingBoxCoordinate(JsonObject jsonObject) {

		if(jsonObject.get("type") != null && jsonObject.get("type") != JsonValue.NULL) {
			this.type = jsonObject.getString("type");
		}

		if(jsonObject.getJsonArray("coordinates") != null) {
			JsonArray coordinatesArray = jsonObject.getJsonArray("coordinates");
			for(int i = 0; i < coordinatesArray.size(); i++) {
				List<List<Double>> list2 = new ArrayList<>();
				JsonArray list2JsonArray = coordinatesArray.get(i).asJsonArray();
				for(int j = 0; j < list2JsonArray.size(); j++) {
					List<Double> list1 = new ArrayList<>();
					JsonArray list1JsonArray = list2JsonArray.get(j).asJsonArray();
					for(int k = 0; k < list1JsonArray.size(); k++) {
						list1.add(Double.parseDouble(list1JsonArray.getJsonNumber(k).toString()));
					}
					list2.add(list1);
				}
				this.coordinates.add(list2);
			}
		}
		return this;
	}

	public byte[] bsonSerialization() {
		BasicOutputBuffer outputBuffer = new BasicOutputBuffer();
		BsonBinaryWriter writer = new BsonBinaryWriter(outputBuffer);

		writer.writeStartDocument();
		if(this.type != null)
			writer.writeString("type", this.type);

		writer.writeInt32("coordinates_size", this.coordinates.size());
		writer.writeName("coordinates");
		writer.writeStartArray();
		for(List<List<Double>> list1 : this.coordinates) {

			writer.writeStartDocument();
			writer.writeInt32("coordinates_list2_size", list1.size());
			writer.writeName("coordinates_list2");
			writer.writeStartArray();
			for(List<Double> list2 : list1) {
				writer.writeStartDocument();
				writer.writeInt32("coordinates_list3_size", list2.size());
				writer.writeName("coordinates_list3");
				writer.writeStartArray();
				for(Double d : list2) {
					writer.writeDouble(d);
				}
				writer.writeEndArray();
				writer.writeEndDocument();
			}
			writer.writeEndArray();
			writer.writeEndDocument();
		}
		writer.writeEndArray();

		writer.writeEndDocument();

		return outputBuffer.toByteArray();
	}

	public RootData bsonDeSerialization(byte[] buffData) {
		ByteBuffer buf = ByteBuffer.wrap(buffData);
		BsonBinaryReader reader = new BsonBinaryReader(buf);

		reader.readStartDocument();
		String currentname = reader.readName();
		if(currentname.equals("type")) {
			this.type = reader.readString();
			reader.readName();
		}

		int coordinates_size = reader.readInt32();
		reader.readName("coordinates");
		reader.readStartArray();
		for(int i = 0; i < coordinates_size; i++) {
			reader.readStartDocument();
			List<List<Double>> list1 = new ArrayList<>();
			int coordinates_list2_size = reader.readInt32("coordinates_list2_size");
			reader.readName("coordinates_list2");
			reader.readStartArray();
			for(int j = 0; j < coordinates_list2_size; j++) {
				reader.readStartDocument();
				List<Double> list2 = new ArrayList<>();
				int coordinates_list3_size = reader.readInt32("coordinates_list3_size");
				reader.readName("coordinates_list3");
				reader.readStartArray();
				for(int k = 0; k < coordinates_list3_size; k++) {
					list2.add(reader.readDouble());
				}
				reader.readEndArray();
				list1.add(list2);
				reader.readEndDocument();
			}
			reader.readEndArray();

			this.coordinates.add(list1);
			reader.readEndDocument();
		}
		reader.readEndArray();
		reader.readEndDocument();

		return this;
	}

	public int flatBuffersWriter(FlatBufferBuilder builder) {

		int typeBuilder = this.type != null ? builder.createString(this.type) : 0;

		int[] coordinatesList = new int[this.coordinates.size()];
		for(int i = 0; i < this.coordinates.size(); i++) {

			int[] list1 = new int[this.coordinates.get(i).size()];
			for(int j = 0; j < this.coordinates.get(i).size(); j++) {

				double[] list2 = new double[this.coordinates.get(i).get(j).size()];
				for(int k = 0; k < this.coordinates.get(i).get(j).size(); k++) {
					list2[k] = this.coordinates.get(i).get(j).get(k);
				}
				list1[j] = DoubleList2.createValuesVector(builder, list2);
			}
			coordinatesList[i] = DoubleList1.createValuesVector(builder, list1);
		}
		int coordinateBuilder = BoundingBoxCoordinateFBS.createCoordinatesVector(builder, coordinatesList);

		BoundingBoxCoordinateFBS.startBoundingBoxCoordinateFBS(builder);

		BoundingBoxCoordinateFBS.addType(builder, typeBuilder);
		BoundingBoxCoordinateFBS.addCoordinates(builder, coordinateBuilder);
		int orc = BoundingBoxCoordinateFBS.endBoundingBoxCoordinateFBS(builder);
		return orc;
	}

	public BoundingBoxCoordinate flatBuffersDeserialization(BoundingBoxCoordinateFBS boundingBoxCoordinateFBS) {

		this.type = boundingBoxCoordinateFBS.type();
		//TODO
		//this.coordinates=boundingBoxCoordinateFBS.;
		return this;
	}

	public int compareTo(RootData o) {
		return 0;
	}
}
