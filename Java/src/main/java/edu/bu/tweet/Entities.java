package edu.bu.tweet;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import edu.bu.util.Base;
import edu.bu.util.RootData;
import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import org.apache.log4j.Logger;


public class Entities extends Base implements RootData {

	private static final long serialVersionUID = -8599446450468325664L;
	static Logger logger = Logger.getLogger(Entities.class);

	private List<HashtagEntity > hashtags;
	private List<MediaEntity > media;
	private List<URLEntity > urls;
	private List<UserMentionEntity > user_mentions;
	private List<SymbolEntity > symbols;
	private List<PollEntity > polls;

	public Entities() {
		this.hashtags=new ArrayList<>();
		this.media=new ArrayList<>();
		this.urls=new ArrayList<>();
		this.user_mentions=new ArrayList<>();
		this.symbols=new ArrayList<>();
		this.polls=new ArrayList<>();
	}

	public List<HashtagEntity> getHashtags() {
		return hashtags;
	}

	public void setHashtags(List<HashtagEntity> hashtags) {
		this.hashtags = hashtags;
	}

	public List<MediaEntity> getMedia() {
		return media;
	}

	public void setMedia(List<MediaEntity> media) {
		this.media = media;
	}

	public List<URLEntity> getUrls() {
		return urls;
	}

	public void setUrls(List<URLEntity> urls) {
		this.urls = urls;
	}

	public List<UserMentionEntity> getUser_mentions() {
		return user_mentions;
	}

	public void setUser_mentions(List<UserMentionEntity> user_mentions) {
		this.user_mentions = user_mentions;
	}

	public List<SymbolEntity> getSymbols() {
		return symbols;
	}

	public void setSymbols(List<SymbolEntity> symbols) {
		this.symbols = symbols;
	}

	public List<PollEntity> getPolls() {
		return polls;
	}

	public void setPolls(List<PollEntity> polls) {
		this.polls = polls;
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

		ArrayList<byte[]> hashtagsBytes = new ArrayList<byte[]>();
		for (HashtagEntity hashtagEntity:hashtags){
			byte[] hashtagBytes=hashtagEntity.writeByteBuffer();
			hashtagsBytes.add(hashtagBytes);
			allocatedBufferSize+=hashtagBytes.length;
			allocatedBufferSize+=4;
		}
		allocatedBufferSize+=4;

		ArrayList<byte[]> mediasBytes = new ArrayList<byte[]>();
		for (MediaEntity mediaEntity:media){
			byte[] mediaBytes=mediaEntity.writeByteBuffer();
			mediasBytes.add(mediaBytes);
			allocatedBufferSize+=mediaBytes.length;
			allocatedBufferSize+=4;

		}
		allocatedBufferSize+=4;

		ArrayList<byte[]> urlsBytes = new ArrayList<byte[]>();
		for (URLEntity urlEntity:urls){
			byte[] urlBytes=urlEntity.writeByteBuffer();
			urlsBytes.add(urlBytes);
			allocatedBufferSize+=urlBytes.length;
			allocatedBufferSize+=4;
		}
		allocatedBufferSize+=4;

		ArrayList<byte[]> user_mentionsBytes = new ArrayList<byte[]>();
		for (UserMentionEntity userMentionEntity:user_mentions){
			byte[] user_mentionBytes=userMentionEntity.writeByteBuffer();
			user_mentionsBytes.add(user_mentionBytes);
			allocatedBufferSize+=user_mentionBytes.length;
			allocatedBufferSize+=4;
		}
		allocatedBufferSize+=4;

		ArrayList<byte[]> symbolsBytes = new ArrayList<byte[]>();
		for (SymbolEntity symbolEntity:symbols){
			byte[] symbolBytes=symbolEntity.writeByteBuffer();
			symbolsBytes.add(symbolBytes);
			allocatedBufferSize+=symbolBytes.length;
			allocatedBufferSize+=4;
		}
		allocatedBufferSize+=4;

		ArrayList<byte[]> pollsBytes = new ArrayList<byte[]>();
		for (PollEntity pollEntity:polls){
			byte[] pollBytes=pollEntity.writeByteBuffer();
			symbolsBytes.add(pollBytes);
			allocatedBufferSize+=pollBytes.length;
			allocatedBufferSize+=4;
		}
		allocatedBufferSize+=4;

		// array fields
		ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
		byteBuffer.putInt(hashtagsBytes.size());
		for (byte[] b:hashtagsBytes){
			byteBuffer.putInt(b.length);
			byteBuffer.put(b);
		}

		byteBuffer.putInt(mediasBytes.size());
		for (byte[] b:mediasBytes){
			byteBuffer.putInt(b.length);
			byteBuffer.put(b);
		}

		byteBuffer.putInt(urlsBytes.size());
		for (byte[] b:urlsBytes){
			byteBuffer.putInt(b.length);
			byteBuffer.put(b);
		}

		byteBuffer.putInt(user_mentionsBytes.size());
		for (byte[] b:user_mentionsBytes){
			byteBuffer.putInt(b.length);
			byteBuffer.put(b);
		}

		byteBuffer.putInt(symbolsBytes.size());
		for (byte[] b:symbolsBytes){
			byteBuffer.putInt(b.length);
			byteBuffer.put(b);
		}

		byteBuffer.putInt(pollsBytes.size());
		for (byte[] b:pollsBytes){
			byteBuffer.putInt(b.length);
			byteBuffer.put(b);
		}

		return byteBuffer.array();
	}

	public RootData readByteBuffer(byte[] buffData) {

		ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);

		int numberOfHashtags=byteBuffer.getInt();
		this.hashtags=new ArrayList<>();
		for (int i=0;i<numberOfHashtags;i++){
			byte[] hashtagBytes=new byte[byteBuffer.getInt()];
			byteBuffer.get(hashtagBytes, 0, hashtagBytes.length);
			HashtagEntity hashtagEntity=new HashtagEntity();
			hashtagEntity.readByteBuffer(hashtagBytes);
			this.hashtags.add(hashtagEntity);
		}

		int numberOfMedias=byteBuffer.getInt();
		this.media=new ArrayList<>();
		for (int i=0;i<numberOfMedias;i++){
			byte[] mediaBytes=new byte[byteBuffer.getInt()];
			byteBuffer.get(mediaBytes, 0, mediaBytes.length);
			MediaEntity mediaEntity=new MediaEntity();
			mediaEntity.readByteBuffer(mediaBytes);
			this.media.add(mediaEntity);

		}

		int numberOfUrls=byteBuffer.getInt();
		this.urls=new ArrayList<>();
		for (int i=0;i<numberOfUrls;i++){
			byte[] urlsBytes=new byte[byteBuffer.getInt()];
			byteBuffer.get(urlsBytes, 0, urlsBytes.length);
			URLEntity urlEntity=new URLEntity();
			urlEntity.readByteBuffer(urlsBytes);
			this.urls.add(urlEntity);
		}

		int numberOfUser_mentions=byteBuffer.getInt();
		this.user_mentions=new ArrayList<>();
		for (int i=0;i<numberOfUser_mentions;i++){
			byte[] user_mentionsBytes=new byte[byteBuffer.getInt()];
			byteBuffer.get(user_mentionsBytes, 0, user_mentionsBytes.length);
			UserMentionEntity userMentionEntity=new UserMentionEntity();
			userMentionEntity.readByteBuffer(user_mentionsBytes);
			this.user_mentions.add(userMentionEntity);
		}

		int numberOfSymbols=byteBuffer.getInt();
		this.symbols=new ArrayList<>();
		for (int i=0;i<numberOfSymbols;i++){
			byte[] symbolsBytes=new byte[byteBuffer.getInt()];
			byteBuffer.get(symbolsBytes, 0, symbolsBytes.length);
			SymbolEntity symbolEntity=new SymbolEntity();
			symbolEntity.readByteBuffer(symbolsBytes);
			this.symbols.add(symbolEntity);
		}

		int numberOfPolls=byteBuffer.getInt();
		this.polls=new ArrayList<>();
		for (int i=0;i<numberOfPolls;i++){
			byte[] pollsBytes=new byte[byteBuffer.getInt()];
			byteBuffer.get(pollsBytes, 0, pollsBytes.length);
			PollEntity pollEntity=new PollEntity();
			pollEntity.readByteBuffer(pollsBytes);
			this.polls.add(pollEntity);
		}
		return this;
	}

	public int compareTo(RootData o) {
		return 0;
	}

    public JsonObject jsonObjectBuilder() {

		JsonObjectBuilder objectBuilder = Json.createObjectBuilder();

		if (this.hashtags.size()>0) {
			JsonArrayBuilder jsonHashtagsArray = Json.createArrayBuilder();
			for (HashtagEntity hashtagEntity : this.hashtags) {
				jsonHashtagsArray.add(hashtagEntity.jsonObjectBuilder());
			}
			objectBuilder.add("hashtags", jsonHashtagsArray);
		}

		if (this.media.size()>0) {
			JsonArrayBuilder jsonMediaArray = Json.createArrayBuilder();
			for (MediaEntity mediaEntity : this.media) {
				jsonMediaArray.add(mediaEntity.jsonObjectBuilder());
			}
			objectBuilder.add("media", jsonMediaArray);
		}
		if (this.urls.size()>0) {
			JsonArrayBuilder jsonURLArray = Json.createArrayBuilder();
			for (URLEntity urlEntity : this.urls) {
				jsonURLArray.add(urlEntity.jsonObjectBuilder());
			}
			objectBuilder.add("urls", jsonURLArray);
		}
		if (this.user_mentions.size()>0) {
			JsonArrayBuilder jsonUser_mentionsArray = Json.createArrayBuilder();
			for (UserMentionEntity userMentionEntity : this.user_mentions) {
				jsonUser_mentionsArray.add(userMentionEntity.jsonObjectBuilder());
			}
			objectBuilder.add("user_mentions", jsonUser_mentionsArray);
		}

		if (this.symbols.size()>0) {
			JsonArrayBuilder jsonSymbolsArray = Json.createArrayBuilder();
			for (SymbolEntity symbolEntity : this.symbols) {
				jsonSymbolsArray.add(symbolEntity.jsonObjectBuilder());
			}
			objectBuilder.add("symbols", jsonSymbolsArray);
		}

		if (this.polls.size()>0) {
			JsonArrayBuilder jsonPollsArray = Json.createArrayBuilder();
			for (PollEntity pollEntity : this.polls) {
				jsonPollsArray.add(pollEntity.jsonObjectBuilder());
			}
			objectBuilder.add("polls", jsonPollsArray);
		}

		JsonObject jsonObject = objectBuilder.build();
		return jsonObject;
    }

	public Entities readJSONEntities(JsonObject jsonObject) {
		if (jsonObject.getJsonArray("hashtags") != null) {
			JsonArray jsonHashtagsArray = jsonObject.getJsonArray("hashtags");
			for (int i = 0; i < jsonHashtagsArray.size(); i++) {
				JsonObject hashtagsJsonObject = jsonHashtagsArray.getJsonObject(i);
				this.hashtags.add(new HashtagEntity().readJSONHashtagEntity(hashtagsJsonObject));
			}
		}
		if (jsonObject.getJsonArray("media") != null) {
			JsonArray jsonMediaArray = jsonObject.getJsonArray("media");
			for (int i = 0; i < jsonMediaArray.size(); i++) {
				JsonObject mediaJsonObject = jsonMediaArray.getJsonObject(i);
				this.media.add(new MediaEntity().readJSONMediaEntity(mediaJsonObject));
			}
		}
		if (jsonObject.getJsonArray("urls") != null) {
			JsonArray jsonUrlsArray = jsonObject.getJsonArray("urls");
			for (int i = 0; i < jsonUrlsArray.size(); i++) {
				JsonObject urlsJsonObject = jsonUrlsArray.getJsonObject(i);
				this.urls.add(new URLEntity().readJSONURLEntity(urlsJsonObject));
			}
		}
		if (jsonObject.getJsonArray("user_mentions") != null) {
			JsonArray jsonUser_mentionsArray = jsonObject.getJsonArray("user_mentions");
			for (int i = 0; i < jsonUser_mentionsArray.size(); i++) {
				JsonObject user_mentionsJsonObject = jsonUser_mentionsArray.getJsonObject(i);
				this.user_mentions.add(new UserMentionEntity().readJSONUserMentionEntity(user_mentionsJsonObject));
			}
		}

		if (jsonObject.getJsonArray("symbols") != null) {
			JsonArray jsonSymbolsArray = jsonObject.getJsonArray("symbols");
			for (int i = 0; i < jsonSymbolsArray.size(); i++) {
				JsonObject symbolsJsonObject = jsonSymbolsArray.getJsonObject(i);
				this.symbols.add(new SymbolEntity().readJSONSymbolEntity(symbolsJsonObject));
			}
		}

		if (jsonObject.getJsonArray("polls") != null) {
			JsonArray jsonPollsArray = jsonObject.getJsonArray("polls");
			for (int i = 0; i < jsonPollsArray.size(); i++) {
				JsonObject pollsJsonObject = jsonPollsArray.getJsonObject(i);
				this.polls.add(new PollEntity().readJSONPollEntity(pollsJsonObject));
			}
		}
		return this;
	}
}