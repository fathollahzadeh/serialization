package edu.bu.tweet;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonReader;
import javax.json.JsonValue;
import javax.json.JsonWriter;
import javax.json.JsonWriterFactory;
import javax.json.stream.JsonGenerator;

import org.apache.log4j.Logger;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.protobuf.CodedInputStream;

import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.CoordinatesP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.UserP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.CoordinatesP.RowsP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.HashtagEntityP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.MediaEntityP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.PlaceP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.PlaceP.BoundingBoxCoordinateP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.PlaceP.BoundingBoxCoordinateP.BoundingBoxP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.URLEntityP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.UserMentionEntityP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.MediaEntityP.MediaSizesEntityP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.MediaEntityP.MediaSizesEntityP.SizeEntityP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.MediaEntityP.VariantEntityP;
import edu.bu.tweet.proto.TweetStatusProtos.TweetStatusP.SymbolEntityP;
import edu.rice.dmodel.Base;
import edu.rice.dmodel.RootData;

public class TweetStatus extends Base implements RootData {

	private static final long serialVersionUID = -8518719681928439765L;

	static Logger logger = Logger.getLogger(TweetStatus.class);

	private  String created_at;
	private  long id;
	private  String text;
	private  String source;
	private  boolean truncated;
	private  long in_reply_to_status_id;//nullable
	private  long in_reply_to_user_id;//nullable
	private  String in_reply_to_screen_name;//nullable
	private  User user;
	private  Coordinates coordinates;//nullable
	private  Place place;//nullable
	private  long quoted_status_id;
	private  boolean is_quote_status;
	private  TweetStatus quoted_status;
	private  TweetStatus retweeted_status;
	private  int quote_count;//nullable
	private  int reply_count;
	private  int retweet_count;
	private  int favorite_count;//nullable
	private  Entities entities;
	private  ExtendedEntities extended_entities;
	private  boolean favorited;//nullable
	private  boolean retweeted;
	private  boolean possibly_sensitive;//nullable
	private  String filter_level;
	private  String lang;//nullable
	private  List<MatchingRulesEntity> matching_rules;
	private  long current_user_retweet;//nullable
	private  Map<String,Boolean > scopes;//nullable
	private  boolean withheld_copyright;//nullable
	private  List<String> withheld_in_countries;//nullable
	private  String  withheld_scope;//nullable

	public String getCreated_at() {
		return created_at;
	}

	public void setCreated_at(String created_at) {
		this.created_at = created_at;
	}

	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public String getText() {
		return text;
	}

	public void setText(String text) {
		this.text = text;
	}

	public String getSource() {
		return source;
	}

	public void setSource(String source) {
		this.source = source;
	}

	public boolean isTruncated() {
		return truncated;
	}

	public void setTruncated(boolean truncated) {
		this.truncated = truncated;
	}

	public long getIn_reply_to_status_id() {
		return in_reply_to_status_id;
	}

	public void setIn_reply_to_status_id(long in_reply_to_status_id) {
		this.in_reply_to_status_id = in_reply_to_status_id;
	}

	public long getIn_reply_to_user_id() {
		return in_reply_to_user_id;
	}

	public void setIn_reply_to_user_id(long in_reply_to_user_id) {
		this.in_reply_to_user_id = in_reply_to_user_id;
	}

	public String getIn_reply_to_screen_name() {
		return in_reply_to_screen_name;
	}

	public void setIn_reply_to_screen_name(String in_reply_to_screen_name) {
		this.in_reply_to_screen_name = in_reply_to_screen_name;
	}

	public User getUser() {
		return user;
	}

	public void setUser(User user) {
		this.user = user;
	}

	public Coordinates getCoordinates() {
		return coordinates;
	}

	public void setCoordinates(Coordinates coordinates) {
		this.coordinates = coordinates;
	}

	public Place getPlace() {
		return place;
	}

	public void setPlace(Place place) {
		this.place = place;
	}

	public long getQuoted_status_id() {
		return quoted_status_id;
	}

	public void setQuoted_status_id(long quoted_status_id) {
		this.quoted_status_id = quoted_status_id;
	}

	public boolean isIs_quote_status() {
		return is_quote_status;
	}

	public void setIs_quote_status(boolean is_quote_status) {
		this.is_quote_status = is_quote_status;
	}

	public TweetStatus getQuoted_status() {
		return quoted_status;
	}

	public void setQuoted_status(TweetStatus quoted_status) {
		this.quoted_status = quoted_status;
	}

	public TweetStatus getRetweeted_status() {
		return retweeted_status;
	}

	public void setRetweeted_status(TweetStatus retweeted_status) {
		this.retweeted_status = retweeted_status;
	}

	public int getQuote_count() {
		return quote_count;
	}

	public void setQuote_count(int quote_count) {
		this.quote_count = quote_count;
	}

	public int getReply_count() {
		return reply_count;
	}

	public void setReply_count(int reply_count) {
		this.reply_count = reply_count;
	}

	public int getRetweet_count() {
		return retweet_count;
	}

	public void setRetweet_count(int retweet_count) {
		this.retweet_count = retweet_count;
	}

	public int getFavorite_count() {
		return favorite_count;
	}

	public void setFavorite_count(int favorite_count) {
		this.favorite_count = favorite_count;
	}

	public Entities getEntities() {
		return entities;
	}

	public void setEntities(Entities entities) {
		this.entities = entities;
	}

	public ExtendedEntities getExtended_entities() {
		return extended_entities;
	}

	public void setExtended_entities(ExtendedEntities extended_entities) {
		this.extended_entities = extended_entities;
	}

	public boolean isFavorited() {
		return favorited;
	}

	public void setFavorited(boolean favorited) {
		this.favorited = favorited;
	}

	public boolean isRetweeted() {
		return retweeted;
	}

	public void setRetweeted(boolean retweeted) {
		this.retweeted = retweeted;
	}

	public boolean isPossibly_sensitive() {
		return possibly_sensitive;
	}

	public void setPossibly_sensitive(boolean possibly_sensitive) {
		this.possibly_sensitive = possibly_sensitive;
	}

	public String getFilter_level() {
		return filter_level;
	}

	public void setFilter_level(String filter_level) {
		this.filter_level = filter_level;
	}

	public String getLang() {
		return lang;
	}

	public void setLang(String lang) {
		this.lang = lang;
	}

	public List<MatchingRulesEntity> getMatching_rules() {
		return matching_rules;
	}

	public void setMatching_rules(List<MatchingRulesEntity> matching_rules) {
		this.matching_rules = matching_rules;
	}

	public long getCurrent_user_retweet() {
		return current_user_retweet;
	}

	public void setCurrent_user_retweet(long current_user_retweet) {
		this.current_user_retweet = current_user_retweet;
	}

	public Map<String, Boolean> getScopes() {
		return scopes;
	}

	public void setScopes(Map<String, Boolean> scopes) {
		this.scopes = scopes;
	}

	public boolean isWithheld_copyright() {
		return withheld_copyright;
	}

	public void setWithheld_copyright(boolean withheld_copyright) {
		this.withheld_copyright = withheld_copyright;
	}

	public List<String> getWithheld_in_countries() {
		return withheld_in_countries;
	}

	public void setWithheld_in_countries(List<String> withheld_in_countries) {
		this.withheld_in_countries = withheld_in_countries;
	}

	public String getWithheld_scope() {
		return withheld_scope;
	}

	public void setWithheld_scope(String withheld_scope) {
		this.withheld_scope = withheld_scope;
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