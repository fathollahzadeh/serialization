package edu.bu.tweet;

import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.List;
import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonValue;
import org.apache.log4j.Logger;
import edu.bu.util.Base;
import edu.bu.util.RootData;

public class Place extends Base implements RootData {

	private static final long serialVersionUID = -8678000885337272677L;

	static Logger logger = Logger.getLogger(Place.class);

	private String name;
	private String country_code;
	private String id;
	private String country;
	private String place_type;
	private String url;
	private String full_name;
	private BoundingBoxCoordinate bounding_box;

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getCountry_code() {
		return country_code;
	}

	public void setCountry_code(String country_code) {
		this.country_code = country_code;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getCountry() {
		return country;
	}

	public void setCountry(String country) {
		this.country = country;
	}

	public String getPlace_type() {
		return place_type;
	}

	public void setPlace_type(String place_type) {
		this.place_type = place_type;
	}

	public String getUrl() {
		return url;
	}

	public void setUrl(String url) {
		this.url = url;
	}

	public String getFull_name() {
		return full_name;
	}

	public void setFull_name(String full_name) {
		this.full_name = full_name;
	}

	public BoundingBoxCoordinate getBounding_box() {
		return bounding_box;
	}

	public void setBounding_box(BoundingBoxCoordinate bounding_box) {
		this.bounding_box = bounding_box;
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

		byte[] nameBytes = name.getBytes(Charset.forName("UTF-8"));
		allocatedBufferSize += nameBytes.length + 4;

		byte[] country_codeBytes = country_code.getBytes();
		allocatedBufferSize += country_codeBytes.length + 4;

		byte[] idBytes = id.getBytes();
		allocatedBufferSize += idBytes.length + 4;

		byte[] countryBytes = country.getBytes();
		allocatedBufferSize += countryBytes.length + 4;

		byte[] place_typeBytes = place_type.getBytes(Charset.forName("UTF-8"));
		allocatedBufferSize += place_typeBytes.length + 4;

		byte[] urlBytes = url.getBytes();
		allocatedBufferSize += urlBytes.length + 4;

		byte[] full_nameBytes = full_name.getBytes();
		allocatedBufferSize += full_nameBytes.length + 4;

		byte[] bounding_boxBytes=(bounding_box != null) ? bounding_box.writeByteBuffer() : new byte[0];
		allocatedBufferSize +=bounding_boxBytes.length+4;

		// array fields
		ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
		byteBuffer.putInt(nameBytes.length);
		byteBuffer.put(nameBytes);
		byteBuffer.putInt(country_codeBytes.length);
		byteBuffer.put(country_codeBytes);
		byteBuffer.putInt(idBytes.length);
		byteBuffer.put(idBytes);
		byteBuffer.putInt(countryBytes.length);
		byteBuffer.put(countryBytes);
		byteBuffer.putInt(place_typeBytes.length);
		byteBuffer.put(place_typeBytes);
		byteBuffer.putInt(urlBytes.length);
		byteBuffer.put(urlBytes);
		byteBuffer.putInt(full_nameBytes.length);
		byteBuffer.put(full_nameBytes);
		byteBuffer.putInt(bounding_boxBytes.length);
		byteBuffer.put(bounding_boxBytes);

		return byteBuffer.array();
	}

	public RootData readByteBuffer(byte[] buffData) {
		ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
		int stringSize;

		stringSize=byteBuffer.getInt();
		this.country_code=extractString(byteBuffer,stringSize);
		stringSize=byteBuffer.getInt();
		this.name=extractString(byteBuffer,stringSize);
		stringSize=byteBuffer.getInt();
		this.id=extractString(byteBuffer,stringSize);
		stringSize=byteBuffer.getInt();
		this.country=extractString(byteBuffer,stringSize);
		stringSize=byteBuffer.getInt();
		this.place_type=extractString(byteBuffer,stringSize);
		stringSize=byteBuffer.getInt();
		this.url=extractString(byteBuffer,stringSize);
		stringSize=byteBuffer.getInt();
		this.full_name=extractString(byteBuffer,stringSize);

		byte[] bounding_boxBytes = new byte[byteBuffer.getInt()];
		if (bounding_boxBytes.length>0) {
			byteBuffer.get(bounding_boxBytes, 0, bounding_boxBytes.length);
			this.bounding_box = new BoundingBoxCoordinate();
			this.bounding_box.readByteBuffer(bounding_boxBytes);
		}else
			this.bounding_box=null;

		return this;
	}

	public int compareTo(RootData o) {
		return 0;
	}

    public JsonObject jsonObjectBuilder() {

		JsonObjectBuilder objectBuilder = Json.createObjectBuilder();

		if (this.name != null && !this.name.isEmpty()) {
			objectBuilder.add("name", this.name);
		}
		if (this.country_code != null && !this.country_code.isEmpty()) {
			objectBuilder.add("country_code", this.country_code);
		}
		if (this.id != null && !this.id.isEmpty()) {
			objectBuilder.add("id", this.id);
		}
		if (this.country != null && !this.country.isEmpty()) {
			objectBuilder.add("country", this.country);
		}
		if (this.place_type != null && !this.place_type.isEmpty()) {
			objectBuilder.add("place_type", this.place_type);
		}
		if (this.url != null && !this.url.isEmpty()) {
			objectBuilder.add("url", this.url);
		}
		if (this.full_name != null && !this.full_name.isEmpty()) {
			objectBuilder.add("full_name", this.full_name);
		}
		if (this.bounding_box != null ) {
			objectBuilder.add("bounding_box", this.bounding_box.jsonObjectBuilder());
		}

		JsonObject jsonObject = objectBuilder.build();
		return jsonObject;
    }

	public Place readJSONPlace(JsonObject jsonObject) {

		if (jsonObject.get("name") != null && jsonObject.get("name") != JsonValue.NULL) {
			this.name = jsonObject.getString("name");
		}
		if (jsonObject.get("country_code") != null && jsonObject.get("country_code") != JsonValue.NULL) {
			this.country_code = jsonObject.getString("country_code");
		}
		if (jsonObject.get("id") != null && jsonObject.get("id") != JsonValue.NULL) {
			this.id = jsonObject.getString("id");
		}
		if (jsonObject.get("country") != null && jsonObject.get("country") != JsonValue.NULL) {
			this.country = jsonObject.getString("country");
		}
		if (jsonObject.get("place_type") != null && jsonObject.get("place_type") != JsonValue.NULL) {
			this.place_type = jsonObject.getString("place_type");
		}
		if (jsonObject.get("url") != null && jsonObject.get("url") != JsonValue.NULL) {
			this.url = jsonObject.getString("url");
		}
		if (jsonObject.get("full_name") != null && jsonObject.get("full_name") != JsonValue.NULL) {
			this.full_name = jsonObject.getString("full_name");
		}

		if (jsonObject.getJsonObject("bounding_box") != null && jsonObject.getJsonObject("bounding_box") != JsonValue.NULL) {
			JsonObject bounding_boxJsonObject = jsonObject.getJsonObject("bounding_box");
			this.bounding_box=new BoundingBoxCoordinate().readJSONBoundingBoxCoordinate(bounding_boxJsonObject);
		}
		return this;
	}
}
