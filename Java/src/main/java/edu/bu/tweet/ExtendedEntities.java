package edu.bu.tweet;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import edu.rice.dmodel.Base;
import edu.rice.dmodel.RootData;
import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;

import org.apache.log4j.Logger;


public class ExtendedEntities extends Base implements RootData {

	private static final long serialVersionUID = -2991751584291760543L;
	static Logger logger = Logger.getLogger(ExtendedEntities.class);

	private List<MediaEntity > media;

	public ExtendedEntities() {
		this.media=new ArrayList<>();
	}

	public List<MediaEntity> getMedia() {
		return media;
	}

	public void setMedia(List<MediaEntity> media) {
		this.media = media;
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

		ArrayList<byte[]> mediasBytes = new ArrayList<byte[]>();
		for (MediaEntity mediaEntity:media){
			byte[] mediaBytes=mediaEntity.writeByteBuffer();
			mediasBytes.add(mediaBytes);
			allocatedBufferSize+=mediaBytes.length;
			allocatedBufferSize+=4;
		}
		allocatedBufferSize+=4;

		// array fields
		ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);

		byteBuffer.putInt(mediasBytes.size());
		for (byte[] b:mediasBytes){
			byteBuffer.putInt(b.length);
			byteBuffer.put(b);
		}
		return byteBuffer.array();
	}

	public RootData readByteBuffer(byte[] buffData) {
		ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);

		int numberOfMedias=byteBuffer.getInt();
		this.media=new ArrayList<>();
		for (int i=0;i<numberOfMedias;i++){
			byte[] mediaBytes=new byte[byteBuffer.getInt()];
			byteBuffer.get(mediaBytes, 0, mediaBytes.length);
			MediaEntity mediaEntity=new MediaEntity();
			mediaEntity.readByteBuffer(mediaBytes);
			this.media.add(mediaEntity);
		}

		return this;
	}

	public int compareTo(RootData o) {
		return 0;
	}

    public JsonObject jsonObjectBuilder() {
		JsonObjectBuilder objectBuilder = Json.createObjectBuilder();

		if (this.media.size()>0) {
			JsonArrayBuilder jsonMediaArray = Json.createArrayBuilder();
			for (MediaEntity mediaEntity : this.media) {
				jsonMediaArray.add(mediaEntity.jsonObjectBuilder());
			}
			objectBuilder.add("media", jsonMediaArray);
		}

		JsonObject jsonObject = objectBuilder.build();
		return jsonObject;
    }

	public ExtendedEntities readJSONExtendedEntities(JsonObject jsonObject) {
		if (jsonObject.getJsonArray("media") != null) {
			JsonArray jsonMediaArray = jsonObject.getJsonArray("media");
			for (int i = 0; i < jsonMediaArray.size(); i++) {
				JsonObject mediaJsonObject = jsonMediaArray.getJsonObject(i);
				this.media.add(new MediaEntity().readJSONMediaEntity(mediaJsonObject));
			}
		}
		return this;
	}
}