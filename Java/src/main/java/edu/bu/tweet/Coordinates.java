package edu.bu.tweet;


import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.List;
import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonValue;
import org.apache.log4j.Logger;

import edu.rice.dmodel.Base;
import edu.rice.dmodel.RootData;

public class Coordinates extends Base implements RootData {

	private static final long serialVersionUID = 767200407069467768L;

	static Logger logger = Logger.getLogger(Coordinates.class);

	private String type;
	private double[] coordinates;

	public Coordinates() {
		this.coordinates=new double[0];
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public double[] getCoordinates() {
		return coordinates;
	}

	public void setCoordinates(double[] coordinates) {
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

		byte[] typeBytes = type.getBytes(Charset.forName("UTF-8"));
		allocatedBufferSize += typeBytes.length + 4;

		//coordinate size
		// 4 bytes is for an additional integer for write the size byteArray
		allocatedBufferSize+=8* this.coordinates.length+4;

		// array fields
		ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);

		byteBuffer.putInt(typeBytes.length);
		byteBuffer.put(typeBytes);

		byteBuffer.putInt(coordinates.length);
		for (double d:coordinates){
			byteBuffer.putDouble(d);
		}
		return byteBuffer.array();
	}

	public RootData readByteBuffer(byte[] buffData) {

		ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
		int stringSize;

		stringSize=byteBuffer.getInt();
		this.type=extractString(byteBuffer,stringSize);

		int numOfCoordinates=byteBuffer.getInt();
		this.coordinates=new double[numOfCoordinates];
		for (int i=0;i<numOfCoordinates;i++){
			this.coordinates[i]=byteBuffer.getDouble();
		}

		return this;
	}

	public int compareTo(RootData o) {
		return 0;
	}

    public JsonObject jsonObjectBuilder() {

		JsonObjectBuilder coordinatesObjectBuilder = Json.createObjectBuilder();
		coordinatesObjectBuilder.add("type",this.type);

		JsonArrayBuilder jsonCoordinatesArray = Json.createArrayBuilder();
		for (Double d : this.coordinates) {
			jsonCoordinatesArray.add(d);
		}
		coordinatesObjectBuilder.add("coordinates",jsonCoordinatesArray);
		JsonObject coordinatesJsonObject = coordinatesObjectBuilder.build();
		return coordinatesJsonObject;

    }

	public Coordinates readJSONCoordinates(JsonObject jsonObject) {
		if (jsonObject.get("type") != null && jsonObject.get("type") != JsonValue.NULL) {
			this.type=jsonObject.getString("type");
		}

		if (jsonObject.getJsonArray("coordinates") != null) {
			JsonArray coordinatesArray = jsonObject.getJsonArray("coordinates");
			this.coordinates=new double[coordinatesArray.size()];
			for (int i = 0; i < coordinatesArray.size(); i++) {
				this.coordinates[i]=Double.parseDouble(coordinatesArray.getJsonNumber(i).toString());
			}
		}
		return this;
	}
}