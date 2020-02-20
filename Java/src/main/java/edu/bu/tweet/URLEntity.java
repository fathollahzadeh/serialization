package edu.bu.tweet;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import javax.json.*;
import org.apache.log4j.Logger;
import edu.bu.util.Base;
import edu.bu.util.RootData;

public class URLEntity extends Base implements RootData {

	private static final long serialVersionUID = -8770082770640711029L;
	static Logger logger = Logger.getLogger(URLEntity.class);

	private List<Integer> indices;
	private String display_url;
	private String expanded_url;
	private String url;

	public URLEntity() {
		this.indices=new ArrayList<>();
	}

	public List<Integer> getIndices() {
		return indices;
	}

	public void setIndices(List<Integer> indices) {
		this.indices = indices;
	}

	public String getDisplay_url() {
		return display_url;
	}

	public void setDisplay_url(String display_url) {
		this.display_url = display_url;
	}

	public String getExpanded_url() {
		return expanded_url;
	}

	public void setExpanded_url(String expanded_url) {
		this.expanded_url = expanded_url;
	}

	public String getUrl() {
		return url;
	}

	public void setUrl(String url) {
		this.url = url;
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
		allocatedBufferSize += 4 * (indices.size() + 1); //indices * sizeof integer

		byte[] display_urlBytes = (display_url != null) ? display_url.getBytes() : new byte[0];
		allocatedBufferSize += display_urlBytes.length + 4;

		byte[] expanded_urlBytes = (expanded_url != null) ? expanded_url.getBytes() : new byte[0];
		allocatedBufferSize += expanded_urlBytes.length + 4;

		byte[] urlBytes = (url != null) ? url.getBytes() : new byte[0];
		allocatedBufferSize += urlBytes.length + 4;

		// array fields
		ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
		byteBuffer.putInt(indices.size());
		for (int i=0;i<indices.size();i++){
			byteBuffer.putInt(indices.get(i));
		}
		byteBuffer.putInt(display_urlBytes.length);
		byteBuffer.put(display_urlBytes);
		byteBuffer.putInt(expanded_urlBytes.length);
		byteBuffer.put(expanded_urlBytes);
		byteBuffer.putInt(urlBytes.length);
		byteBuffer.put(urlBytes);
		return byteBuffer.array();
	}

	public RootData readByteBuffer(byte[] buffData) {
		ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
		int stringSize;

		int numberOfIndices = byteBuffer.getInt();
		for (int i = 0; i < numberOfIndices; i++) {
			this.indices.add(byteBuffer.getInt());
		}

		stringSize = byteBuffer.getInt();
		this.display_url = extractString(byteBuffer, stringSize);

		stringSize = byteBuffer.getInt();
		this.expanded_url = extractString(byteBuffer, stringSize);

		stringSize = byteBuffer.getInt();
		this.url = extractString(byteBuffer, stringSize);

		return this;
	}

	public JsonObject jsonObjectBuilder() {

		JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
		JsonArrayBuilder jsonIndicesArray = Json.createArrayBuilder();
		for (Integer integer : indices) {
			jsonIndicesArray.add(integer);
		}
		objectBuilder.add("indices", jsonIndicesArray);

		if (this.display_url != null && !this.display_url.isEmpty()) {
			objectBuilder.add("display_url", this.display_url);
		}
		if (this.expanded_url != null && !this.expanded_url.isEmpty()) {
			objectBuilder.add("expanded_url", this.expanded_url);
		}
		if (this.url != null && !this.url.isEmpty()) {
			objectBuilder.add("url", this.url);
		}
		JsonObject jsonObject = objectBuilder.build();
		return jsonObject;
	}

	public URLEntity readJSONURLEntity(JsonObject jsonObject) {

		if (jsonObject.getJsonArray("indices") != null) {
			JsonArray indicesArray = jsonObject.getJsonArray("indices");
			for (int i = 0; i < indicesArray.size(); i++) {
				this.indices.add(indicesArray.getInt(i));
			}
		}

		if (jsonObject.get("display_url") != null && jsonObject.get("display_url") != JsonValue.NULL) {
			this.display_url = jsonObject.getString("display_url");
		}
		if (jsonObject.get("expanded_url") != null && jsonObject.get("expanded_url") != JsonValue.NULL) {
			this.expanded_url = jsonObject.getString("expanded_url");
		}
		if (jsonObject.get("url") != null && jsonObject.get("url") != JsonValue.NULL) {
			this.url = jsonObject.getString("url");
		}
		return  this;
	}

	public int compareTo(RootData o) {
		return 0;
	}
}
