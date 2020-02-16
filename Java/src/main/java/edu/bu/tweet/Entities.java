package edu.bu.tweet;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import edu.rice.dmodel.Base;
import edu.rice.dmodel.RootData;

import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonReader;
import javax.json.JsonWriter;
import javax.json.JsonWriterFactory;
import javax.json.stream.JsonGenerator;

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
		return new byte[0];
	}

	public RootData readByteBuffer(byte[] buffData) {
		return null;
	}

	public int compareTo(RootData o) {
		return 0;
	}
}