package at.tugraz.tweet;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.ArrayList;
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

import com.google.flatbuffers.FlatBufferBuilder;
import com.google.gson.Gson;
import com.google.protobuf.CodedInputStream;
import at.tugraz.tweet.flatbuffers.MapStringBool;
import at.tugraz.tweet.flatbuffers.TweetStatusFBS;
import at.tugraz.tweet.proto.TweetStatusProtos;
import org.apache.log4j.Logger;
import at.tugraz.util.Base;
import at.tugraz.util.RootData;
import org.bson.BsonBinary;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;

public class TweetStatus extends Base implements RootData {

	static Logger logger = Logger.getLogger(TweetStatus.class);
	private String created_at;
	private long id;
	private String id_str;
	private String text;
	private String source;
	private boolean truncated;
	private long in_reply_to_status_id;//nullable
	private long in_reply_to_user_id;//nullable
	private String in_reply_to_screen_name;//nullable
	private User user;
	private Coordinates coordinates;//nullable
	private Place place;//nullable
	private long quoted_status_id;
	private boolean is_quote_status;
	private TweetStatus quoted_status;
	private TweetStatus retweeted_status;
	private int quote_count;//nullable
	private int reply_count;
	private int retweet_count;
	private int favorite_count;//nullable
	private Entities entities;
	private ExtendedTweet extended_tweet;
	private boolean favorited;//nullable
	private boolean retweeted;
	private boolean possibly_sensitive;//nullable
	private String filter_level;
	private String lang;//nullable
	private List<MatchingRulesEntity> matching_rules;
	private long current_user_retweet;//nullable
	private Map<String, Boolean> scopes;//nullable
	private boolean withheld_copyright;//nullable
	private List<String> withheld_in_countries;//nullable
	private String withheld_scope;//nullable

	private List<Integer> display_text_range; //nullable

	private TweetStatusFBS tweetStatusFBS;
	private TweetStatusProtos.TweetStatusP tweetStatusP;

	public TweetStatus() {
		in_reply_to_status_id = -999;
		in_reply_to_user_id = -999;
		quote_count = -999;
		favorite_count = -999;
		favorited = false;
		possibly_sensitive = false;
		current_user_retweet = -999;
		withheld_copyright = false;
		withheld_in_countries = new ArrayList<String>();
		matching_rules = new ArrayList<>();
		scopes = new HashMap<>();
		this.tweetStatusFBS = null;
		this.tweetStatusP = null;

	}

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

	public ExtendedTweet getExtended_tweet() {
		return extended_tweet;
	}

	public void setExtended_tweet(ExtendedTweet extended_tweet) {
		this.extended_tweet = extended_tweet;
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


	public String getId_str() {
		return id_str;
	}

	public void setId_str(String id_str) {
		this.id_str = id_str;
	}

	public List<Integer> getDisplay_text_range() {
		return display_text_range;
	}

	public void setDisplay_text_range(List<Integer> display_text_range) {
		this.display_text_range = display_text_range;
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
		ByteArrayInputStream b = new ByteArrayInputStream(buf);
		ObjectInputStream objectInputStream;

		TweetStatus p = null;

		try {
			objectInputStream = new ObjectInputStream(b);
			p = (TweetStatus) objectInputStream.readObject();

		}
		catch(IOException | ClassNotFoundException e) {
			logger.error("Can't read object from byteArray", e);
		}
		return p;
	}

	public byte[] jsonSerialization() {
		Map<String, Object> properties = new HashMap<String, Object>(1);
		//		properties.put(JsonGenerator.PRETTY_PRINTING, true);

		JsonWriterFactory writerFactory = Json.createWriterFactory(properties);
		ByteArrayOutputStream bos = new ByteArrayOutputStream();

		try {
			JsonWriter jsonWriter = writerFactory.createWriter(bos);
			jsonWriter.writeObject(this.jsonObjectBuilder());
			jsonWriter.close();
		}
		catch(Exception e) {
			logger.error(e);
		}

		// Get the bytes of the serialized JSON object
		byte[] buf = bos.toByteArray();
		return buf;

	}

	private JsonObject jsonObjectBuilder() {
		JsonObjectBuilder tweetStatusObjectBuilder = Json.createObjectBuilder();
		tweetStatusObjectBuilder.add("created_at", this.getCreated_at());
		tweetStatusObjectBuilder.add("id", this.getId());
		tweetStatusObjectBuilder.add("id_str", this.getId_str());
		tweetStatusObjectBuilder.add("text", this.getText());
		tweetStatusObjectBuilder.add("source", this.getSource());
		tweetStatusObjectBuilder.add("truncated", this.isTruncated());
		tweetStatusObjectBuilder.add("in_reply_to_status_id", this.getIn_reply_to_status_id());
		tweetStatusObjectBuilder.add("in_reply_to_user_id", this.getIn_reply_to_user_id());
		if(this.getIn_reply_to_screen_name() != null && !this.getIn_reply_to_screen_name().isEmpty()) {
			tweetStatusObjectBuilder.add("in_reply_to_screen_name", this.getIn_reply_to_screen_name());
		}
		tweetStatusObjectBuilder.add("user", this.getUser().jsonObjectBuilder());

		if(this.getCoordinates() != null)
			tweetStatusObjectBuilder.add("coordinates", this.getCoordinates().jsonObjectBuilder());

		if(this.getPlace() != null)
			tweetStatusObjectBuilder.add("place", this.getPlace().jsonObjectBuilder());

		tweetStatusObjectBuilder.add("quoted_status_id", this.getQuoted_status_id());
		tweetStatusObjectBuilder.add("is_quote_status", this.isIs_quote_status());

		if(this.getQuoted_status() != null)
			tweetStatusObjectBuilder.add("quoted_status", this.getQuoted_status().jsonObjectBuilder());

		if(this.getRetweeted_status() != null)
			tweetStatusObjectBuilder.add("retweeted_status", this.getRetweeted_status().jsonObjectBuilder());

		tweetStatusObjectBuilder.add("quote_count", this.getQuote_count());
		tweetStatusObjectBuilder.add("reply_count", this.getReply_count());
		tweetStatusObjectBuilder.add("retweet_count", this.getRetweet_count());
		tweetStatusObjectBuilder.add("favorite_count", this.getFavorite_count());

		if(this.getEntities() != null)
			tweetStatusObjectBuilder.add("entities", this.getEntities().jsonObjectBuilder());

		if(this.getExtended_tweet() != null)
			tweetStatusObjectBuilder.add("extended_tweet", this.getExtended_tweet().jsonObjectBuilder());

		tweetStatusObjectBuilder.add("favorited", this.isFavorited());
		tweetStatusObjectBuilder.add("retweeted", this.isRetweeted());
		tweetStatusObjectBuilder.add("possibly_sensitive", this.isPossibly_sensitive());

		if(this.getFilter_level() != null && !this.getFilter_level().isEmpty()) {
			tweetStatusObjectBuilder.add("filter_level", this.getFilter_level());
		}
		if(this.getLang() != null && !this.getLang().isEmpty()) {
			tweetStatusObjectBuilder.add("lang", this.getLang());
		}

		JsonArrayBuilder jsonMatching_rulesArray = Json.createArrayBuilder();
		for(MatchingRulesEntity matchingRulesEntity : this.matching_rules) {
			jsonMatching_rulesArray.add(matchingRulesEntity.jsonObjectBuilder());
		}
		tweetStatusObjectBuilder.add("matching_rules", jsonMatching_rulesArray);
		tweetStatusObjectBuilder.add("current_user_retweet", this.getCurrent_user_retweet());

		JsonObjectBuilder scopesObjectBuilder = Json.createObjectBuilder();
		this.scopes.keySet().stream().forEach((key) -> scopesObjectBuilder.add(key, this.scopes.get(key)));

		tweetStatusObjectBuilder.add("scopes", scopesObjectBuilder);
		tweetStatusObjectBuilder.add("withheld_copyright", this.isWithheld_copyright());

		JsonArrayBuilder jsonWithheld_in_countriesArray = Json.createArrayBuilder();
		for(String s : this.withheld_in_countries) {
			jsonWithheld_in_countriesArray.add(s);
		}
		tweetStatusObjectBuilder.add("withheld_in_countries", jsonWithheld_in_countriesArray);
		if(this.withheld_scope != null && !this.withheld_scope.isEmpty()) {
			tweetStatusObjectBuilder.add("withheld_scope", this.getWithheld_scope());
		}

		JsonArrayBuilder jsonDisplayTextRangeArray = Json.createArrayBuilder();
		for(Integer integer : display_text_range) {
			jsonDisplayTextRangeArray.add(integer);
		}
		tweetStatusObjectBuilder.add("display_text_range", jsonDisplayTextRangeArray);

		JsonObject tweetStatusJsonObject = tweetStatusObjectBuilder.build();
		return tweetStatusJsonObject;
	}

	public RootData jsonDeserialization(byte[] buf) {
		TweetStatus tweetStatus;
		ByteArrayInputStream b = new ByteArrayInputStream(buf);

		try {
			// create JsonReader object
			JsonReader jsonReader = Json.createReader(b);

			// get JsonObject from JsonReader
			JsonObject jsonObject = jsonReader.readObject();

			tweetStatus = readJSONTweetStatus(jsonObject);

			// we can close IO resource and JsonReader now
			b.close();
			jsonReader.close();

		}
		catch(Exception e) {
			logger.error("Can not read JSON object TweetStatus from byteArray", e);
			return null;
		}

		return tweetStatus;
	}

	private TweetStatus readJSONTweetStatus(JsonObject jsonObject) {

		if(jsonObject.get("created_at") != null && jsonObject.get("created_at") != JsonValue.NULL) {
			this.created_at = jsonObject.getString("created_at");
		}
		this.id = Long.parseLong(jsonObject.getJsonNumber("id").toString());
		this.id_str = jsonObject.getString("id_str");

		if(jsonObject.get("text") != null && jsonObject.get("text") != JsonValue.NULL) {
			this.text = jsonObject.getString("text");
		}

		if(jsonObject.get("source") != null && jsonObject.get("source") != JsonValue.NULL) {
			this.source = jsonObject.getString("source");
		}

		if(jsonObject.get("truncated") != null && jsonObject.get("truncated") != JsonValue.NULL) {
			this.truncated = jsonObject.getBoolean("truncated");
		}
		this.in_reply_to_status_id = Long.parseLong(jsonObject.getJsonNumber("in_reply_to_status_id").toString());
		this.in_reply_to_user_id = Long.parseLong(jsonObject.getJsonNumber("in_reply_to_user_id").toString());

		if(jsonObject.get("in_reply_to_screen_name") != null && jsonObject
			.get("in_reply_to_screen_name") != JsonValue.NULL) {
			this.in_reply_to_screen_name = jsonObject.getString("in_reply_to_screen_name");
		}

		if(jsonObject.getJsonObject("user") != null && jsonObject.getJsonObject("user") != JsonValue.NULL) {
			JsonObject userJsonObject = jsonObject.getJsonObject("user");
			this.user = new User().readJSONUser(userJsonObject);
		}

		if(jsonObject.getJsonObject("coordinates") != null && jsonObject
			.getJsonObject("coordinates") != JsonValue.NULL) {
			JsonObject coordinatesJsonObject = jsonObject.getJsonObject("coordinates");
			this.coordinates = new Coordinates().readJSONCoordinates(coordinatesJsonObject);
		}

		if(jsonObject.getJsonObject("place") != null && jsonObject.getJsonObject("place") != JsonValue.NULL) {
			JsonObject placeJsonObject = jsonObject.getJsonObject("place");
			this.place = new Place().readJSONPlace(placeJsonObject);
		}
		this.quoted_status_id = Long.parseLong(jsonObject.getJsonNumber("quoted_status_id").toString());
		this.is_quote_status = jsonObject.getBoolean("is_quote_status");

		if(jsonObject.getJsonObject("quoted_status") != null && jsonObject
			.getJsonObject("quoted_status") != JsonValue.NULL) {
			JsonObject quoted_statusJsonObject = jsonObject.getJsonObject("quoted_status");
			this.quoted_status = new TweetStatus().readJSONTweetStatus(quoted_statusJsonObject);
		}

		if(jsonObject.getJsonObject("retweeted_status") != null && jsonObject
			.getJsonObject("retweeted_status") != JsonValue.NULL) {
			JsonObject retweeted_statusJsonObject = jsonObject.getJsonObject("retweeted_status");
			this.retweeted_status = new TweetStatus().readJSONTweetStatus(retweeted_statusJsonObject);
		}
		this.quote_count = jsonObject.getInt("quote_count");
		this.reply_count = jsonObject.getInt("reply_count");
		this.retweet_count = jsonObject.getInt("retweet_count");
		this.favorite_count = jsonObject.getInt("favorite_count");

		if(jsonObject.getJsonObject("entities") != null && jsonObject.getJsonObject("entities") != JsonValue.NULL) {
			JsonObject entitiesJsonObject = jsonObject.getJsonObject("entities");
			this.entities = new Entities().readJSONEntities(entitiesJsonObject);
		}

		if(jsonObject.getJsonObject("entities") != null && jsonObject.getJsonObject("entities") != JsonValue.NULL) {
			JsonObject entitiesJsonObject = jsonObject.getJsonObject("entities");
			this.entities = new Entities().readJSONEntities(entitiesJsonObject);
		}

		if(jsonObject.getJsonObject("extended_tweet") != null && jsonObject
			.getJsonObject("extended_tweet") != JsonValue.NULL) {
			JsonObject extended_tweetJsonObject = jsonObject.getJsonObject("extended_tweet");
			this.extended_tweet = new ExtendedTweet().readJSONExtendedTweet(extended_tweetJsonObject);
		}

		this.favorited = jsonObject.getBoolean("favorited");
		this.retweeted = jsonObject.getBoolean("retweeted");
		this.possibly_sensitive = jsonObject.getBoolean("possibly_sensitive");

		if(jsonObject.get("filter_level") != null && jsonObject.get("filter_level") != JsonValue.NULL) {
			this.filter_level = jsonObject.getString("filter_level");
		}

		if(jsonObject.get("lang") != null && jsonObject.get("lang") != JsonValue.NULL) {
			this.lang = jsonObject.getString("lang");
		}

		if(jsonObject.getJsonArray("matching_rules") != null) {
			JsonArray jsonMatching_rulesArray = jsonObject.getJsonArray("matching_rules");
			for(int i = 0; i < jsonMatching_rulesArray.size(); i++) {
				JsonObject matching_ruleJsonObject = jsonMatching_rulesArray.getJsonObject(i);
				this.matching_rules.add(new MatchingRulesEntity().readJSONMatchingRulesEntity(matching_ruleJsonObject));
			}
		}

		this.current_user_retweet = Long.parseLong(jsonObject.getJsonNumber("current_user_retweet").toString());

		if(jsonObject.getJsonObject("scopes") != null && jsonObject.getJsonObject("scopes") != JsonValue.NULL) {
			JsonObject scopesJsonObject = jsonObject.getJsonObject("scopes");

			for(String k : scopesJsonObject.keySet()) {
				this.scopes.put(k, scopesJsonObject.getBoolean(k));
			}
		}

		this.withheld_copyright = jsonObject.getBoolean("withheld_copyright");

		if(jsonObject.getJsonArray("withheld_in_countries") != null) {
			JsonArray jsonWithheld_in_countriesArray = jsonObject.getJsonArray("withheld_in_countries");
			for(int i = 0; i < jsonWithheld_in_countriesArray.size(); i++) {
				this.withheld_in_countries.add(jsonWithheld_in_countriesArray.getString(i));
			}
		}
		if(jsonObject.get("withheld_scope") != null && jsonObject.get("withheld_scope") != JsonValue.NULL) {
			this.withheld_scope = jsonObject.getString("withheld_scope");
		}

		if(jsonObject.getJsonArray("display_text_range") != null) {
			JsonArray displayTextRangeArray = jsonObject.getJsonArray("display_text_range");
			for(int i = 0; i < displayTextRangeArray.size(); i++) {
				this.display_text_range.add(displayTextRangeArray.getInt(i));
			}
		}
		return this;
	}

	public byte[] jsonSerialization_withGZIP() {
		return this.gZIPCompression(this.jsonSerialization());
	}

	public RootData jsonDeserialization_withGZIP(byte[] buf) {
		return jsonDeserialization(this.gZIP_DE_Compression(buf));
	}

	public byte[] protocolBufferWrite() {
		byte[] data;
		if(this.tweetStatusP == null) {
			data = this.protoObjectBuilder().toByteArray();
		}
		else
			data = this.tweetStatusP.toByteArray();
		return data;
	}

	public TweetStatusProtos.TweetStatusP protoObjectBuilder() {
		TweetStatusProtos.TweetStatusP.Builder tweetP = TweetStatusProtos.TweetStatusP.newBuilder();

		tweetP.setCreatedAt(this.created_at);
		tweetP.setId(this.id);
		if(this.text != null)
			tweetP.setText(this.text);
		if(this.source != null)
			tweetP.setSource(this.source);
		tweetP.setIsTruncated(this.truncated);
		tweetP.setInReplyToStatusId(this.in_reply_to_status_id);
		tweetP.setInReplyToUserId(this.in_reply_to_user_id);
		if(this.in_reply_to_screen_name != null)
			tweetP.setInReplyToScreenName(this.in_reply_to_screen_name);

		// set user:
		TweetStatusProtos.TweetStatusP.UserP.Builder userP = TweetStatusProtos.TweetStatusP.UserP.newBuilder();
		userP.setId(this.user.getId());
		if(this.user.getName() != null)
			userP.setName(this.user.getName());
		if(this.user.getScreen_name() != null)
			userP.setScreenName(this.user.getScreen_name());
		if(this.user.getLocation() != null)
			userP.setLocation(this.user.getLocation());
		if(this.user.getUrl() != null)
			userP.setUrl(this.user.getUrl());
		if(this.user.getDescription() != null)
			userP.setDescription(this.user.getDescription());
		userP.setIsProtected(this.user.isProtected());
		userP.setIsVerified(this.user.isVerified());
		userP.setFollowersCount(this.user.getFollowers_count());
		userP.setFriendsCount(this.user.getFriends_count());
		userP.setListedCount(this.user.getListed_count());
		userP.setFavouritesCount(this.user.getFavourites_count());
		userP.setStatusesCount(this.user.getStatuses_count());
		if(this.user.getCreated_at() != null)
			userP.setCreatedAt(this.user.getCreated_at());
		if(this.user.getProfile_banner_url() != null)
			userP.setProfileBannerImageUrl(this.user.getProfile_banner_url());
		if(this.user.getProfile_image_url_https() != null)
			userP.setProfileImageUrlHttps(this.user.getProfile_image_url_https());
		userP.setIsDefaultProfile(this.user.isDefault_profile());

		for(String s : this.user.getWithheld_in_countries()) {
			userP.addWithheldInCountries(s);
		}
		if(this.user.getWithheld_scope() != null)
			userP.setWithheldScope(this.user.getWithheld_scope());
		for(URLEntity urlEntity : this.user.getDescriptionURLEntities()) {
			TweetStatusProtos.URLEntityP.Builder urlEntityP = TweetStatusProtos.URLEntityP.newBuilder();
			if(urlEntity.getDisplay_url() != null)
				urlEntityP.setDisplayURL(urlEntity.getDisplay_url());
			if(urlEntity.getUrl() != null)
				urlEntityP.setUrl(urlEntity.getUrl());
			if(urlEntity.getExpanded_url() != null)
				urlEntityP.setExpandedURL(urlEntity.getExpanded_url());

			for(Integer integer : urlEntity.getIndices()) {
				urlEntityP.addIndices(integer);
			}
			userP.addDescriptionURLEntities(urlEntityP);
		}
		userP.setIsGeoEnabled(this.user.isGeo_enabled());
		if(this.user.getLang() != null)
			userP.setLang(this.user.getLang());
		userP.setIsContributorsEnabled(this.user.isContributors_enabled());
		if(this.user.getProfile_background_color() != null)
			userP.setProfileBackgroundColor(this.user.getProfile_background_color());
		if(this.user.getProfile_background_image_url() != null)
			userP.setProfileBackgroundImageUrl(this.user.getProfile_background_image_url());
		if(this.user.getProfile_background_image_url_https() != null)
			userP.setProfileBackgroundImageUrlHttps(this.user.getProfile_background_image_url_https());
		userP.setProfileBackgroundTiled(this.user.isProfile_background_tile());
		if(this.user.getProfile_image_url() != null)
			userP.setProfileImageUrl(this.user.getProfile_image_url());
		if(this.user.getProfile_link_color() != null)
			userP.setProfileLinkColor(this.user.getProfile_link_color());
		if(this.user.getProfile_sidebar_border_color() != null)
			userP.setProfileSidebarBorderColor(this.user.getProfile_sidebar_border_color());
		if(this.user.getProfile_sidebar_fill_color() != null)
			userP.setProfileSidebarFillColor(this.user.getProfile_sidebar_fill_color());
		if(this.user.getProfile_text_color() != null)
			userP.setProfileTextColor(this.user.getProfile_text_color());
		userP.setProfileUseBackgroundImage(this.user.isProfile_use_background_image());
		userP.setIsDefaultProfileImage(this.user.isDefault_profile());
		userP.setUtcOffset(this.user.getUtc_offset());
		if(this.user.getTime_zone() != null)
			userP.setTimeZone(this.user.getTime_zone());
		userP.setTranslator(this.user.isIs_translator());
		userP.setIsFollowRequestSent(this.user.isFollow_request_sent());
		userP.setShowAllInlineMedia(this.user.isShowAllInlineMedia());
		tweetP.setUserP(userP);
		// end set user

		//set coordinates:
		if(this.coordinates != null && this.coordinates.getCoordinates().length > 0) {

			TweetStatusProtos.TweetStatusP.CoordinatesP.Builder coordinatesP = TweetStatusProtos.TweetStatusP.CoordinatesP
				.newBuilder();
			if(this.getCoordinates().getType() != null)
				coordinatesP.setType(this.getCoordinates().getType());
			for(int i = 0; i < 2; ++i) {
				coordinatesP.addCoordinates(this.getCoordinates().getCoordinates()[i]);
			}
			tweetP.setCoordinates(coordinatesP);
		}

		// set place:
		if(this.place != null) {
			TweetStatusProtos.TweetStatusP.PlaceP.Builder placeP = TweetStatusProtos.TweetStatusP.PlaceP.newBuilder();
			if(this.getPlace().getName() != null)
				placeP.setName(this.getPlace().getName());
			if(this.getPlace().getId() != null)
				placeP.setId(this.getPlace().getId());
			if(this.getPlace().getCountry() != null)
				placeP.setCountry(this.getPlace().getCountry());
			if(this.getPlace().getPlace_type() != null)
				placeP.setPlaceType(this.getPlace().getPlace_type());
			if(this.getPlace().getUrl() != null)
				placeP.setUrl(this.getPlace().getUrl());
			if(this.getPlace().getFull_name() != null)
				placeP.setFullName(this.getPlace().getFull_name());

			if(this.getPlace().getBounding_box() != null) {
				TweetStatusProtos.TweetStatusP.PlaceP.BoundingBoxCoordinateP.Builder boundingBoxCoordinateP = TweetStatusProtos.TweetStatusP.PlaceP.BoundingBoxCoordinateP
					.newBuilder();
				if(this.getPlace().getBounding_box().getType() != null)
					boundingBoxCoordinateP.setType(this.getPlace().getBounding_box().getType());

				for(int i = 0; i < this.getPlace().getBounding_box().getCoordinates().size(); ++i) {
					TweetStatusProtos.TweetStatusP.PlaceP.BoundingBoxCoordinateP.RowsOneP.Builder rowsOneP = TweetStatusProtos.TweetStatusP.PlaceP.BoundingBoxCoordinateP.RowsOneP
						.newBuilder();

					for(int j = 0; j < this.getPlace().getBounding_box().getCoordinates().get(i).size(); ++j) {
						TweetStatusProtos.TweetStatusP.PlaceP.BoundingBoxCoordinateP.RowsOneP.RowsTwoP.Builder rowsTwoP = TweetStatusProtos.TweetStatusP.PlaceP.BoundingBoxCoordinateP.RowsOneP.RowsTwoP
							.newBuilder();

						for(int k = 0; k < this.getPlace().getBounding_box().getCoordinates().get(i).get(j)
							.size(); ++k) {
							rowsTwoP
								.addCoordinate(this.getPlace().getBounding_box().getCoordinates().get(i).get(j).get(k));
						}
						rowsOneP.addRowsTwoP(rowsTwoP);
					}
				}
			}
			tweetP.setPlace(placeP);
		}
		// end set place

		tweetP.setQuotedStatusId(this.getQuoted_status_id());
		tweetP.setIsQuoteStatus(this.isIs_quote_status());

		if(this.quoted_status != null) {
			tweetP.setQuotedStatus(this.quoted_status.protoObjectBuilder());
		}

		if(this.retweeted_status != null) {
			tweetP.setRetweetedStatus(this.retweeted_status.protoObjectBuilder());
		}

		tweetP.setQuoteCount(this.getQuote_count());
		tweetP.setReplyCount(this.reply_count);
		tweetP.setRetweetCount(this.retweet_count);
		tweetP.setFavoriteCount(this.favorite_count);

		//Entities
		if(this.entities != null) {

			TweetStatusProtos.TweetStatusP.EntitiesP.Builder entitiesP = TweetStatusProtos.TweetStatusP.EntitiesP
				.newBuilder();

			//HashtagEntity
			for(HashtagEntity hashtagEntity : this.entities.getHashtags()) {
				TweetStatusProtos.HashtagEntityP.Builder hashtagEntityP = TweetStatusProtos.HashtagEntityP.newBuilder();
				if(hashtagEntity.getText() != null)
					hashtagEntityP.setText(hashtagEntity.getText());

				for(Integer integer : hashtagEntity.getIndices()) {
					hashtagEntityP.addIndices(integer);
				}
				entitiesP.addHashtagEntityP(hashtagEntityP);
			}

			//MediaEntity
			for(MediaEntity mediaEntity : this.entities.getMedia()) {
				TweetStatusProtos.MediaEntityP.Builder mediaEntityP = TweetStatusProtos.MediaEntityP.newBuilder();
				setMediaEntityP(mediaEntityP, mediaEntity);
				entitiesP.addMediaEntityP(mediaEntityP);
			}

			//URLEntity
			for(URLEntity urlEntity : this.entities.getUrls()) {
				TweetStatusProtos.URLEntityP.Builder urlEntityP = TweetStatusProtos.URLEntityP.newBuilder();
				if(urlEntity.getDisplay_url() != null)
					urlEntityP.setDisplayURL(urlEntity.getDisplay_url());
				if(urlEntity.getUrl() != null)
					urlEntityP.setUrl(urlEntity.getUrl());
				if(urlEntity.getExpanded_url() != null)
					urlEntityP.setExpandedURL(urlEntity.getExpanded_url());

				for(Integer integer : urlEntity.getIndices()) {
					urlEntityP.addIndices(integer);
				}
				entitiesP.addUrlEntityP(urlEntityP);
			}
			//UserMentionEntity
			for(UserMentionEntity userMentionEntity : this.entities.getUser_mentions()) {
				TweetStatusProtos.UserMentionEntityP.Builder userMentionEntityP = TweetStatusProtos.UserMentionEntityP
					.newBuilder();
				userMentionEntityP.setId(userMentionEntity.getId());
				if(userMentionEntity.getId_str() != null)
					userMentionEntityP.setIdStr(userMentionEntity.getId_str());

				for(Integer integer : userMentionEntity.getIndices()) {
					userMentionEntityP.addIndices(integer);
				}
				if(userMentionEntity.getName() != null)
					userMentionEntityP.setName(userMentionEntity.getName());
				if(userMentionEntity.getScreen_name() != null)
					userMentionEntityP.setScreenName(userMentionEntity.getScreen_name());
				entitiesP.addUserMentionEntityP(userMentionEntityP);

			}

			//SymbolEntity
			for(SymbolEntity symbolEntity : this.entities.getSymbols()) {
				TweetStatusProtos.SymbolEntityP.Builder symbolEntityP = TweetStatusProtos.SymbolEntityP.newBuilder();
				if(symbolEntity.getText() != null)
					symbolEntityP.setText(symbolEntity.getText());

				for(Integer integer : symbolEntity.getIndices()) {
					symbolEntityP.addIndices(integer);
				}
				entitiesP.addSymbolEntityP(symbolEntityP);
			}

			//PollEntity
			for(PollEntity pollEntity : this.entities.getPolls()) {
				TweetStatusProtos.PollEntityP.Builder pollEntityP = TweetStatusProtos.PollEntityP.newBuilder();

				if(pollEntity.getEnd_datetime() != null)
					pollEntityP.setEndDatetime(pollEntity.getEnd_datetime());
				if(pollEntity.getDuration_minutes() != null)
					pollEntityP.setDurationMinutes(pollEntity.getDuration_minutes());

				for(OptionEntity optionEntity : pollEntity.getOptions()) {
					TweetStatusProtos.OptionEntityP.Builder optionEntityP = TweetStatusProtos.OptionEntityP
						.newBuilder();
					optionEntityP.setPosition(optionEntity.getPosition());
					if(optionEntity.getText() != null)
						optionEntityP.setText(optionEntity.getText());
					pollEntityP.addOptions(optionEntityP);
				}
				entitiesP.addPollEntityP(pollEntityP);
			}

			tweetP.setEntitiesP(entitiesP);
		}

		if(this.getExtended_entities() != null) {

			TweetStatusProtos.TweetStatusP.ExtendedEntitiesP.Builder extendedEntitiesP = TweetStatusProtos.TweetStatusP.ExtendedEntitiesP
				.newBuilder();

			for(MediaEntity mediaEntity : this.extended_entities.getMedia()) {
				TweetStatusProtos.MediaEntityP.Builder mediaEntityP = TweetStatusProtos.MediaEntityP.newBuilder();
				setMediaEntityP(mediaEntityP, mediaEntity);
				extendedEntitiesP.addMedia(mediaEntityP);
			}
			tweetP.setExtendedEntities(extendedEntitiesP);

		}

		tweetP.setIsFavorited(this.isFavorited());
		tweetP.setIsRetweeted(this.isRetweeted());
		tweetP.setIsPossiblySensitive(this.isPossibly_sensitive());
		if(this.getFilter_level() != null)
			tweetP.setFilterLevel(this.getFilter_level());
		if(this.getLang() != null)
			tweetP.setLang(this.getLang());

		for(MatchingRulesEntity matchingRulesEntity : this.matching_rules) {
			TweetStatusProtos.MatchingRulesEntityP.Builder matchingRulesEntityP = TweetStatusProtos.MatchingRulesEntityP
				.newBuilder();
			if(matchingRulesEntity.getTag() != null)
				matchingRulesEntityP.setTag(matchingRulesEntity.getTag());
			matchingRulesEntityP.setId(matchingRulesEntity.getId());
			if(matchingRulesEntity.getId_str() != null)
				matchingRulesEntityP.setIdStr(matchingRulesEntity.getId_str());
			tweetP.addMatchingRules(matchingRulesEntityP);
		}

		tweetP.setCurrentUserRetweetedId(this.getCurrent_user_retweet());

		for(String key : this.scopes.keySet()) {
			TweetStatusProtos.MapFieldEntry.Builder mapFieldEntry = TweetStatusProtos.MapFieldEntry.newBuilder();
			mapFieldEntry.setKey(key);
			mapFieldEntry.setValue(this.scopes.get(key));
			tweetP.addScopes(mapFieldEntry);
		}

		tweetP.setWithheldCopyright(this.withheld_copyright);

		for(String s : this.withheld_in_countries) {
			tweetP.addWithheldInCountries(s);
		}
		if(this.withheld_scope != null)
			tweetP.setWithheldScope(this.withheld_scope);

		return tweetP.build();
	}

	void setMediaEntityP(TweetStatusProtos.MediaEntityP.Builder mediaEntityP, MediaEntity mediaEntity) {

		if(mediaEntity.getDisplay_url() != null)
			mediaEntityP.setDisplayURL(mediaEntity.getDisplay_url());
		if(mediaEntity.getExpanded_url() != null)
			mediaEntityP.setExpandedURL(mediaEntity.getExpanded_url());
		mediaEntityP.setId(mediaEntity.getId());
		for(Integer integer : mediaEntity.getIndices()) {
			mediaEntityP.addIndices(integer);
		}
		if(mediaEntity.getMedia_url() != null)
			mediaEntityP.setMediaURL(mediaEntity.getMedia_url());
		if(mediaEntity.getMedia_url_https() != null)
			mediaEntityP.setMediaURLHttps(mediaEntity.getMedia_url_https());

		if(mediaEntity.getSizes() != null) {
			TweetStatusProtos.MediaSizesEntityP.Builder mediaSizesEntityP = TweetStatusProtos.MediaSizesEntityP
				.newBuilder();

			if(mediaEntity.getSizes().getThumb() != null) {
				TweetStatusProtos.SizeEntityP.Builder sizeEntityP = TweetStatusProtos.SizeEntityP.newBuilder();
				setSizeEntityP(sizeEntityP, mediaEntity.getSizes().getThumb());
				mediaSizesEntityP.setThumb(sizeEntityP);
			}

			if(mediaEntity.getSizes().getLarge() != null) {
				TweetStatusProtos.SizeEntityP.Builder sizeEntityP = TweetStatusProtos.SizeEntityP.newBuilder();
				setSizeEntityP(sizeEntityP, mediaEntity.getSizes().getLarge());
				mediaSizesEntityP.setLarge(sizeEntityP);
			}

			if(mediaEntity.getSizes().getMedium() != null) {
				TweetStatusProtos.SizeEntityP.Builder sizeEntityP = TweetStatusProtos.SizeEntityP.newBuilder();
				setSizeEntityP(sizeEntityP, mediaEntity.getSizes().getMedium());
				mediaSizesEntityP.setMedium(sizeEntityP);
			}

			if(mediaEntity.getSizes().getSmall() != null) {
				TweetStatusProtos.SizeEntityP.Builder sizeEntityP = TweetStatusProtos.SizeEntityP.newBuilder();
				setSizeEntityP(sizeEntityP, mediaEntity.getSizes().getSmall());
				mediaSizesEntityP.setSmall(sizeEntityP);
			}

		}
		if(mediaEntity.getType() != null)
			mediaEntityP.setType(mediaEntity.getType());
		mediaEntityP.setSourceStatusId(mediaEntity.getSource_status_id());
		if(mediaEntity.getSource_status_id_str() != null)
			mediaEntityP.setSourceStatusIdStr(mediaEntity.getSource_status_id_str());
		if(mediaEntity.getUrl() != null)
			mediaEntityP.setUrl(mediaEntity.getUrl());

		//VideoEntity
		if(mediaEntity.getVideo_info() != null) {
			TweetStatusProtos.VideoEntityP.Builder videoEntityP = TweetStatusProtos.VideoEntityP.newBuilder();
			for(Integer integer : mediaEntity.getVideo_info().getAspect_ratio()) {
				videoEntityP.addAspectRatio(integer);
			}
			videoEntityP.setDurationMillis(mediaEntity.getVideo_info().getDuration_millis());

			for(VariantEntity variantEntity : mediaEntity.getVideo_info().getVariants()) {
				TweetStatusProtos.VariantEntityP.Builder variantEntityP = TweetStatusProtos.VariantEntityP.newBuilder();
				variantEntityP.setBitrate(variantEntity.getBitrate());
				if(variantEntity.getContent_type() != null)
					variantEntityP.setContentType(variantEntity.getContent_type());
				if(variantEntity.getUrl() != null)
					variantEntityP.setUrl(mediaEntity.getUrl());
			}
		}

		//AdditionalMediaInfoEntity
		if(mediaEntity.getAdditional_media_info() != null) {
			TweetStatusProtos.AdditionalMediaInfoEntityP.Builder additionalMediaInfoEntityP = TweetStatusProtos.AdditionalMediaInfoEntityP
				.newBuilder();
			if(mediaEntity.getAdditional_media_info().getTitle() != null)
				additionalMediaInfoEntityP.setTitle(mediaEntity.getAdditional_media_info().getTitle());
			if(mediaEntity.getAdditional_media_info().getDescription() != null)
				additionalMediaInfoEntityP.setDescription(mediaEntity.getAdditional_media_info().getDescription());
			additionalMediaInfoEntityP.setEmbeddable(mediaEntity.getAdditional_media_info().isEmbeddable());
			additionalMediaInfoEntityP.setMonetizable(mediaEntity.getAdditional_media_info().isMonetizable());
		}
	}

	void setSizeEntityP(TweetStatusProtos.SizeEntityP.Builder sizeEntityP, SizeEntity sizeEntity) {
		sizeEntityP.setWidth(sizeEntity.getWidth());
		sizeEntityP.setHeight(sizeEntity.getHeight());
		if(sizeEntity.getResize() != null)
			sizeEntityP.setResize(sizeEntity.getResize());
	}

	public RootData protocolBufferRead(byte[] buf) {
		ByteArrayInputStream b = new ByteArrayInputStream(buf);

		TweetStatusProtos.TweetStatusP.Builder protocTweet = TweetStatusProtos.TweetStatusP.newBuilder();
		CodedInputStream stream = CodedInputStream.newInstance(b);

		try {
			protocTweet.mergeFrom(stream);
		}
		catch(IOException e) {
			logger.error(" Protocol Buffer Reader  in TweetStatus ", e);
		}

		//TweetStatus tweet = tweetObjectBuilder(protocTweet.build());
		this.tweetStatusP = protocTweet.build();

		return this;
	}

	public TweetStatus tweetObjectBuilder(TweetStatusProtos.TweetStatusP protoTweet) {

		this.created_at = protoTweet.getCreatedAt();
		this.id = protoTweet.getId();
		//this.id_str = protoTweet.getId();
		if(protoTweet.getText() != null)
			this.text = protoTweet.getText();
		if(protoTweet.getSource() != null)
			this.source = protoTweet.getSource();
		this.truncated = protoTweet.getIsTruncated();
		this.in_reply_to_status_id = protoTweet.getInReplyToStatusId();
		this.in_reply_to_user_id = protoTweet.getInReplyToUserId();
		if(protoTweet.getInReplyToScreenName() != null)
			this.in_reply_to_screen_name = protoTweet.getInReplyToScreenName();

		// set user:
		this.user = new User();
		TweetStatusProtos.TweetStatusP.UserP userP = protoTweet.getUserP();
		this.user.setId(userP.getId());
		if(userP.getName() != null)
			this.user.setName(userP.getName());
		if(userP.getScreenName() != null)
			this.user.setScreen_name(userP.getScreenName());
		if(userP.getLocation() != null)
			this.user.setLocation(userP.getLocation());
		if(userP.getUrl() != null)
			this.user.setUrl(userP.getUrl());
		if(userP.getDescription() != null)
			this.user.setDescription(userP.getDescription());
		this.user.setProtected(userP.getIsProtected());
		this.user.setVerified(userP.getIsVerified());
		this.user.setFollowers_count(userP.getFollowersCount());
		this.user.setFriends_count(userP.getFriendsCount());
		this.user.setListed_count(userP.getListedCount());
		this.user.setFavourites_count(userP.getFavouritesCount());
		this.user.setStatuses_count(userP.getStatusesCount());
		if(userP.getCreatedAt() != null)
			this.user.setCreated_at(userP.getCreatedAt());
		if(userP.getProfileBannerImageUrl() != null)
			this.user.setProfile_banner_url(userP.getProfileBannerImageUrl());
		if(userP.getProfileImageUrlHttps() != null)
			this.user.setProfile_image_url_https(userP.getProfileImageUrlHttps());
		this.user.setDefault_profile(userP.getIsDefaultProfile());

		for(String s : userP.getWithheldInCountriesList()) {
			this.user.getWithheld_in_countries().add(s);
		}
		if(userP.getWithheldScope() != null)
			this.user.setWithheld_scope(userP.getWithheldScope());

		for(TweetStatusProtos.URLEntityP urlEntityP : userP.getDescriptionURLEntitiesList()) {
			URLEntity urlEntity = new URLEntity();
			if(urlEntityP.getDisplayURL() != null)
				urlEntity.setDisplay_url(urlEntityP.getDisplayURL());
			if(urlEntityP.getUrl() != null)
				urlEntity.setUrl(urlEntityP.getUrl());
			if(urlEntityP.getExpandedURL() != null)
				urlEntity.setExpanded_url(urlEntityP.getExpandedURL());

			for(Integer integer : urlEntityP.getIndicesList()) {
				urlEntity.getIndices().add(integer);
			}
			this.user.getDescriptionURLEntities().add(urlEntity);
		}
		this.user.setGeo_enabled(userP.getIsGeoEnabled());
		if(userP.getLang() != null)
			this.user.setLang(userP.getLang());
		this.user.setContributors_enabled(userP.getIsContributorsEnabled());
		if(userP.getProfileBackgroundColor() != null)
			this.user.setProfile_background_color(userP.getProfileBackgroundColor());
		if(userP.getProfileBackgroundImageUrl() != null)
			this.user.setProfile_background_image_url(userP.getProfileBackgroundImageUrl());
		if(userP.getProfileBackgroundImageUrlHttps() != null)
			this.user.setProfile_background_image_url_https(userP.getProfileBackgroundImageUrlHttps());
		this.user.setProfile_background_tile(userP.getProfileBackgroundTiled());
		if(userP.getProfileImageUrl() != null)
			this.user.setProfile_image_url(userP.getProfileImageUrl());
		if(userP.getProfileLinkColor() != null)
			this.user.setProfile_link_color(userP.getProfileLinkColor());
		if(userP.getProfileSidebarBorderColor() != null)
			this.user.setProfile_sidebar_border_color(userP.getProfileSidebarBorderColor());
		if(userP.getProfileSidebarFillColor() != null)
			this.user.setProfile_sidebar_fill_color(userP.getProfileSidebarFillColor());
		if(userP.getProfileTextColor() != null)
			this.user.setProfile_text_color(userP.getProfileTextColor());
		this.user.setProfile_use_background_image(userP.getProfileUseBackgroundImage());
		this.user.setDefault_profile(userP.getIsDefaultProfile());
		this.user.setUtc_offset(userP.getUtcOffset());
		if(userP.getTimeZone() != null)
			this.user.setTime_zone(userP.getTimeZone());
		this.user.setIs_translator(userP.getTranslator());
		this.user.setFollow_request_sent(userP.getIsFollowRequestSent());
		this.user.setShowAllInlineMedia(userP.getShowAllInlineMedia());
		// end set user

		//set coordinates:
		if(protoTweet.getCoordinates() != null) {
			this.coordinates = new Coordinates();
			TweetStatusProtos.TweetStatusP.CoordinatesP coordinatesP = protoTweet.getCoordinates();
			if(coordinatesP.getType() != null)
				this.coordinates.setType(coordinatesP.getType());
			double coordinates[] = new double[coordinatesP.getCoordinatesList().size()];
			int i = 0;
			for(Double d : coordinatesP.getCoordinatesList()) {
				coordinates[i] = d;
				i++;
			}
			this.coordinates.setCoordinates(coordinates);
		}

		// set place:
		if(this.place != null) {
			TweetStatusProtos.TweetStatusP.PlaceP.Builder placeP = TweetStatusProtos.TweetStatusP.PlaceP.newBuilder();
			if(placeP.getName() != null)
				this.place.setName(placeP.getName());
			if(placeP.getId() != null)
				this.place.setId(placeP.getId());
			if(placeP.getCountry() != null)
				this.getPlace().setCountry(placeP.getCountry());
			if(placeP.getPlaceType() != null)
				this.place.setPlace_type(placeP.getPlaceType());
			if(placeP.getUrl() != null)
				this.place.setUrl(placeP.getUrl());
			if(placeP.getFullName() != null)
				this.place.setFull_name(placeP.getFullName());

			if(placeP.getBoundingBoxCoordinateP() != null) {
				this.place.setBounding_box(new BoundingBoxCoordinate());
				TweetStatusProtos.TweetStatusP.PlaceP.BoundingBoxCoordinateP boundingBoxCoordinateP = placeP
					.getBoundingBoxCoordinateP();
				if(boundingBoxCoordinateP.getType() != null)
					this.place.getBounding_box().setType(boundingBoxCoordinateP.getType());

				List<List<List<Double>>> coordinates = new ArrayList<>();
				for(TweetStatusProtos.TweetStatusP.PlaceP.BoundingBoxCoordinateP.RowsOneP rowsOneP : boundingBoxCoordinateP
					.getThreeDimArrayList()) {

					List<List<Double>> list2 = new ArrayList<>();
					for(TweetStatusProtos.TweetStatusP.PlaceP.BoundingBoxCoordinateP.RowsOneP.RowsTwoP rowsTwoP : rowsOneP
						.getRowsTwoPList()) {
						List<Double> list1 = new ArrayList<>();
						for(Double d : rowsTwoP.getCoordinateList()) {
							list1.add(d);
						}
						list2.add(list1);
					}
					coordinates.add(list2);
				}
				this.place.getBounding_box().setCoordinates(coordinates);
			}
		}
		// end set place

		this.setQuoted_status_id(protoTweet.getQuotedStatusId());
		this.setIs_quote_status(protoTweet.getIsQuoteStatus());

		if(protoTweet.getQuotedStatus() != null && protoTweet.getQuotedStatus().getId() != 0) {
			TweetStatus quotedStatus = new TweetStatus();
			quotedStatus.tweetObjectBuilder(protoTweet.getQuotedStatus());
			this.setQuoted_status(quotedStatus);

		}

		if(protoTweet.getRetweetedStatus() != null && protoTweet.getRetweetedStatus().getId() != 0) {
			TweetStatus retweetedStatus = new TweetStatus();
			retweetedStatus.tweetObjectBuilder(protoTweet.getRetweetedStatus());
			this.setRetweeted_status(retweetedStatus);
		}
		this.quote_count = protoTweet.getQuoteCount();
		this.reply_count = protoTweet.getReplyCount();
		this.retweet_count = protoTweet.getRetweetCount();
		this.favorite_count = protoTweet.getFavoriteCount();

		//Entities
		if(protoTweet.getEntitiesP() != null) {
			this.entities = new Entities();

			TweetStatusProtos.TweetStatusP.EntitiesP entitiesP = protoTweet.getEntitiesP();

			//HashtagEntity
			for(TweetStatusProtos.HashtagEntityP hashtagEntityP : entitiesP.getHashtagEntityPList()) {
				HashtagEntity hashtagEntity = new HashtagEntity();
				if(hashtagEntityP.getText() != null)
					hashtagEntity.setText(hashtagEntityP.getText());

				for(Integer integer : hashtagEntityP.getIndicesList()) {
					hashtagEntity.getIndices().add(integer);
				}
				this.entities.getHashtags().add(hashtagEntity);
			}

			//MediaEntity
			for(TweetStatusProtos.MediaEntityP mediaEntityP : entitiesP.getMediaEntityPList()) {
				this.entities.getMedia().add(getMediaEntity(mediaEntityP));
			}

			//URLEntity
			for(TweetStatusProtos.URLEntityP urlEntityP : protoTweet.getEntitiesP().getUrlEntityPList()) {
				URLEntity urlEntity = new URLEntity();
				if(urlEntityP.getDisplayURL() != null)
					urlEntity.setDisplay_url(urlEntityP.getDisplayURL());
				if(urlEntityP.getUrl() != null)
					urlEntity.setUrl(urlEntityP.getUrl());
				if(urlEntityP.getExpandedURL() != null)
					urlEntity.setExpanded_url(urlEntityP.getExpandedURL());

				for(Integer integer : urlEntityP.getIndicesList()) {
					urlEntity.getIndices().add(integer);
				}
				this.entities.getUrls().add(urlEntity);
			}
			//UserMentionEntity
			for(TweetStatusProtos.UserMentionEntityP userMentionEntityP : protoTweet.getEntitiesP()
				.getUserMentionEntityPList()) {
				UserMentionEntity userMentionEntity = new UserMentionEntity();
				userMentionEntity.setId(userMentionEntityP.getId());
				if(userMentionEntityP.getIdStr() != null)
					userMentionEntity.setId_str(userMentionEntityP.getIdStr());

				for(Integer integer : userMentionEntityP.getIndicesList()) {
					userMentionEntity.getIndices().add(integer);
				}
				if(userMentionEntityP.getName() != null)
					userMentionEntity.setName(userMentionEntityP.getName());
				if(userMentionEntityP.getScreenName() != null)
					userMentionEntity.setScreen_name(userMentionEntityP.getScreenName());
				this.entities.getUser_mentions().add(userMentionEntity);
			}

			//SymbolEntity
			for(TweetStatusProtos.SymbolEntityP symbolEntityP : protoTweet.getEntitiesP().getSymbolEntityPList()) {
				SymbolEntity symbolEntity = new SymbolEntity();
				if(symbolEntityP.getText() != null)
					symbolEntity.setText(symbolEntityP.getText());

				for(Integer integer : symbolEntityP.getIndicesList()) {
					symbolEntity.getIndices().add(integer);
				}
				this.entities.getSymbols().add(symbolEntity);
			}

			//PollEntity
			for(TweetStatusProtos.PollEntityP pollEntityP : protoTweet.getEntitiesP().getPollEntityPList()) {
				PollEntity pollEntity = new PollEntity();
				if(pollEntityP.getEndDatetime() != null)
					pollEntity.setEnd_datetime(pollEntityP.getEndDatetime());
				if(pollEntityP.getDurationMinutes() != null)
					pollEntity.setDuration_minutes(pollEntityP.getDurationMinutes());

				for(TweetStatusProtos.OptionEntityP optionEntityP : pollEntityP.getOptionsList()) {
					OptionEntity optionEntity = new OptionEntity();
					optionEntity.setPosition(optionEntityP.getPosition());
					if(optionEntityP.getText() != null)
						optionEntity.setText(optionEntityP.getText());
					pollEntity.getOptions().add(optionEntity);
				}
				this.entities.getPolls().add(pollEntity);
			}
		}

		if(protoTweet.getExtendedEntities() != null) {

			ExtendedEntities extendedEntities = new ExtendedEntities();
			TweetStatusProtos.TweetStatusP.ExtendedEntitiesP extendedEntitiesP = protoTweet.getExtendedEntities();

			for(TweetStatusProtos.MediaEntityP mediaEntityP : extendedEntitiesP.getMediaList()) {
				extendedEntities.getMedia().add(getMediaEntity(mediaEntityP));
			}

			this.setExtended_entities(extendedEntities);
		}

		this.favorited = protoTweet.getIsFavorited();
		this.retweeted = protoTweet.getIsRetweeted();
		this.possibly_sensitive = protoTweet.getIsPossiblySensitive();
		if(protoTweet.getFilterLevel() != null)
			this.filter_level = protoTweet.getFilterLevel();
		if(protoTweet.getLang() != null)
			this.lang = protoTweet.getLang();

		for(TweetStatusProtos.MatchingRulesEntityP matchingRulesEntityP : protoTweet.getMatchingRulesList()) {
			MatchingRulesEntity matchingRulesEntity = new MatchingRulesEntity();
			if(matchingRulesEntityP.getTag() != null)
				matchingRulesEntity.setTag(matchingRulesEntityP.getTag());
			matchingRulesEntity.setId(matchingRulesEntityP.getId());
			if(matchingRulesEntityP.getIdStr() != null)
				matchingRulesEntity.setId_str(matchingRulesEntityP.getIdStr());
			this.matching_rules.add(matchingRulesEntity);
		}

		this.setCurrent_user_retweet(protoTweet.getCurrentUserRetweetedId());

		for(TweetStatusProtos.MapFieldEntry mapFieldEntry : protoTweet.getScopesList()) {
			this.scopes.put(mapFieldEntry.getKey(), mapFieldEntry.getValue());
		}

		this.withheld_copyright = protoTweet.getWithheldCopyright();

		for(String s : protoTweet.getWithheldInCountriesList()) {
			this.withheld_in_countries.add(s);
		}
		if(protoTweet.getWithheldScope() != null)
			this.withheld_scope = protoTweet.getWithheldScope();

		return this;
	}

	private MediaEntity getMediaEntity(TweetStatusProtos.MediaEntityP mediaEntityP) {

		MediaEntity mediaEntity = new MediaEntity();

		if(mediaEntityP.getDisplayURL() != null)
			mediaEntity.setDisplay_url(mediaEntityP.getDisplayURL());
		if(mediaEntityP.getExpandedURL() != null)
			mediaEntity.setExpanded_url(mediaEntity.getExpanded_url());
		mediaEntity.setId(mediaEntityP.getId());
		for(Integer integer : mediaEntityP.getIndicesList()) {
			mediaEntity.getIndices().add(integer);
		}
		if(mediaEntityP.getMediaURL() != null)
			mediaEntity.setMedia_url(mediaEntityP.getMediaURL());
		if(mediaEntityP.getMediaURLHttps() != null)
			mediaEntity.setMedia_url_https(mediaEntityP.getMediaURLHttps());

		if(mediaEntityP.getSizes() != null) {
			mediaEntity.setSizes(new MediaSizesEntity());
			TweetStatusProtos.MediaSizesEntityP mediaSizesEntityP = mediaEntityP.getSizes();

			if(mediaSizesEntityP.getThumb() != null) {
				TweetStatusProtos.SizeEntityP sizeEntityThumbP = mediaSizesEntityP.getThumb();
				mediaEntity.getSizes().setThumb(getSizeEntity(sizeEntityThumbP));
			}

			if(mediaSizesEntityP.getLarge() != null) {
				TweetStatusProtos.SizeEntityP sizeEntityLargeP = mediaSizesEntityP.getLarge();
				mediaEntity.getSizes().setLarge(getSizeEntity(sizeEntityLargeP));
			}

			if(mediaSizesEntityP.getMedium() != null) {
				TweetStatusProtos.SizeEntityP sizeEntityMediumP = mediaSizesEntityP.getMedium();
				mediaEntity.getSizes().setMedium(getSizeEntity(sizeEntityMediumP));
			}

			if(mediaSizesEntityP.getSmall() != null) {
				TweetStatusProtos.SizeEntityP sizeEntitySmallP = mediaSizesEntityP.getSmall();
				mediaEntity.getSizes().setSmall(getSizeEntity(sizeEntitySmallP));
			}
		}
		if(mediaEntityP.getType() != null)
			mediaEntity.setType(mediaEntityP.getType());
		mediaEntity.setSource_status_id(mediaEntityP.getSourceStatusId());
		if(mediaEntityP.getSourceStatusIdStr() != null)
			mediaEntity.setSource_status_id_str(mediaEntityP.getSourceStatusIdStr());
		if(mediaEntityP.getUrl() != null)
			mediaEntity.setUrl(mediaEntityP.getUrl());

		//VideoEntity
		if(mediaEntityP.getVideoInfo() != null) {
			VideoEntity videoEntity = new VideoEntity();

			TweetStatusProtos.VideoEntityP videoEntityP = mediaEntityP.getVideoInfo();
			for(Integer integer : videoEntityP.getAspectRatioList()) {
				videoEntity.getAspect_ratio().add(integer);
			}
			videoEntity.setDuration_millis(mediaEntityP.getVideoInfo().getDurationMillis());

			for(TweetStatusProtos.VariantEntityP variantEntityP : videoEntityP.getVariantsList()) {
				VariantEntity variantEntity = new VariantEntity();
				variantEntity.setBitrate(variantEntityP.getBitrate());
				if(variantEntityP.getContentType() != null)
					variantEntity.setContent_type(variantEntityP.getContentType());
				if(variantEntityP.getUrl() != null)
					variantEntity.setUrl(mediaEntityP.getUrl());
				videoEntity.getVariants().add(variantEntity);
			}

			mediaEntity.setVideo_info(videoEntity);
		}

		//AdditionalMediaInfoEntity
		if(mediaEntityP.getAdditionalMediaInfo() != null) {
			AdditionalMediaInfoEntity additionalMediaInfoEntity = new AdditionalMediaInfoEntity();
			TweetStatusProtos.AdditionalMediaInfoEntityP additionalMediaInfoEntityP = mediaEntityP
				.getAdditionalMediaInfo();
			if(additionalMediaInfoEntityP.getTitle() != null)
				additionalMediaInfoEntity.setTitle(additionalMediaInfoEntity.getTitle());
			if(additionalMediaInfoEntityP.getDescription() != null)
				additionalMediaInfoEntity.setDescription(additionalMediaInfoEntityP.getDescription());
			additionalMediaInfoEntity.setEmbeddable(additionalMediaInfoEntityP.getEmbeddable());
			additionalMediaInfoEntity.setMonetizable(additionalMediaInfoEntityP.getMonetizable());
			mediaEntity.setAdditional_media_info(additionalMediaInfoEntity);
		}
		return mediaEntity;
	}

	private SizeEntity getSizeEntity(TweetStatusProtos.SizeEntityP sizeEntityP) {
		SizeEntity sizeEntity = new SizeEntity();
		sizeEntity.setWidth(sizeEntityP.getWidth());
		sizeEntity.setHeight(sizeEntityP.getHeight());
		if(sizeEntityP.getResize() != null)
			sizeEntity.setResize(sizeEntityP.getResize());
		return sizeEntity;
	}

	public byte[] writeByteBuffer() {

		int allocatedBufferSize = 0;

		byte[] id_strBytes = id_str.getBytes(Charset.forName("UTF-8"));
		allocatedBufferSize += id_strBytes.length + 4;

		byte[] created_atBytes = created_at.getBytes(Charset.forName("UTF-8"));
		allocatedBufferSize += created_atBytes.length + 4;

		byte[] textBytes = text.getBytes(Charset.forName("UTF-8"));
		allocatedBufferSize += textBytes.length + 4;

		byte[] sourceBytes = source.getBytes(Charset.forName("UTF-8"));
		allocatedBufferSize += sourceBytes.length + 4;

		byte[] in_reply_to_screen_nameBytes = (in_reply_to_screen_name != null) ? in_reply_to_screen_name
			.getBytes(Charset.forName("UTF-8")) : new byte[0];
		allocatedBufferSize += in_reply_to_screen_nameBytes.length + 4;

		byte[] userBytes = user.writeByteBuffer();
		allocatedBufferSize += userBytes.length + 4;

		byte[] coordinateBytes = (coordinates != null) ? coordinates.writeByteBuffer() : new byte[0];
		allocatedBufferSize += coordinateBytes.length + 4;

		byte[] placeBytes = (place != null) ? place.writeByteBuffer() : new byte[0];
		allocatedBufferSize += placeBytes.length + 4;

		byte[] quoted_statusBytes = (quoted_status != null) ? quoted_status.writeByteBuffer() : new byte[0];
		allocatedBufferSize += quoted_statusBytes.length + 4;

		byte[] retweeted_statusBytes = (retweeted_status != null) ? retweeted_status.writeByteBuffer() : new byte[0];
		allocatedBufferSize += retweeted_statusBytes.length + 4;

		byte[] entityBytes = entities.writeByteBuffer();
		allocatedBufferSize += entityBytes.length + 4;

		byte[] extended_tweetBytes = (extended_tweet != null) ? extended_tweet.writeByteBuffer() : new byte[0];
		allocatedBufferSize += extended_tweetBytes.length + 4;

		byte[] filter_levelByte = (filter_level != null) ? filter_level.getBytes() : new byte[0];
		allocatedBufferSize += filter_levelByte.length + 4;

		byte[] langBytes = (lang != null) ? lang.getBytes() : new byte[0];
		allocatedBufferSize += langBytes.length + 4;

		byte[] withheld_scopeBytes = (withheld_scope != null) ? withheld_scope.getBytes() : new byte[0];
		allocatedBufferSize += withheld_scopeBytes.length + 4;

		ArrayList<byte[]> matching_rulesBytes = new ArrayList<byte[]>();
		for(MatchingRulesEntity matchingRulesEntity : matching_rules) {
			byte[] matching_ruleBytes = matchingRulesEntity.writeByteBuffer();
			matching_rulesBytes.add(matching_ruleBytes);
			// 4 bytes is for an additional integer for write the size byteArray
			allocatedBufferSize += matching_ruleBytes.length + 4;

		}
		allocatedBufferSize += 4;

		ArrayList<byte[]> scopesBytes = new ArrayList<byte[]>();

		if(scopes != null) {
			for(String s : scopes.keySet()) {
				byte[] scopeBytes = s.getBytes();
				scopesBytes.add(scopeBytes);
				// 4 bytes is for an additional integer for write the size byteArray
				//1 byte for bool value map
				allocatedBufferSize += scopeBytes.length + 4 + 1;
			}
		}
		allocatedBufferSize += 4;

		ArrayList<byte[]> withheld_in_countriesBytes = new ArrayList<byte[]>();
		if(withheld_in_countries != null) {
			for(String s : withheld_in_countries) {
				byte[] withheld_in_countryBytes = s.getBytes();
				withheld_in_countriesBytes.add(withheld_in_countryBytes);
				// 4 bytes is for an additional integer for write the size byteArray
				allocatedBufferSize += withheld_in_countryBytes.length + 4;

			}
		}
		allocatedBufferSize += 4;

		//reserve size for primitive variables:
		allocatedBufferSize += 8; //id
		allocatedBufferSize += 1; //truncated
		allocatedBufferSize += 8; //in_reply_to_status_id
		allocatedBufferSize += 8; //in_reply_to_user_id
		allocatedBufferSize += 8; //quoted_status_id
		allocatedBufferSize += 1; //is_quote_status
		allocatedBufferSize += 4; //quote_count
		allocatedBufferSize += 4; //reply_count
		allocatedBufferSize += 4; //retweet_count
		allocatedBufferSize += 4; //favorite_count
		allocatedBufferSize += 1; //favorited
		allocatedBufferSize += 1; //retweeted
		allocatedBufferSize += 1; //possibly_sensitive
		allocatedBufferSize += 8; //current_user_retweet
		allocatedBufferSize += 1; //withheld_copyright

		// array fields
		ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);

		byteBuffer.putInt(created_atBytes.length);
		byteBuffer.put(created_atBytes);
		byteBuffer.putLong(id);
		byteBuffer.putInt(id_strBytes.length);
		byteBuffer.put(id_strBytes);
		byteBuffer.putInt(textBytes.length);
		byteBuffer.put(textBytes);
		byteBuffer.putInt(sourceBytes.length);
		byteBuffer.put(sourceBytes);
		byteBuffer.put(convertToByte(truncated));
		byteBuffer.putLong(in_reply_to_status_id);
		byteBuffer.putLong(in_reply_to_user_id);
		byteBuffer.putInt(in_reply_to_screen_nameBytes.length);
		byteBuffer.put(in_reply_to_screen_nameBytes);
		byteBuffer.putInt(userBytes.length);
		byteBuffer.put(userBytes);
		byteBuffer.putInt(coordinateBytes.length);
		byteBuffer.put(coordinateBytes);
		byteBuffer.putInt(placeBytes.length);
		byteBuffer.put(placeBytes);
		byteBuffer.putLong(quoted_status_id);
		byteBuffer.put(convertToByte(is_quote_status));
		byteBuffer.putInt(quoted_statusBytes.length);
		byteBuffer.put(quoted_statusBytes);
		byteBuffer.putInt(retweeted_statusBytes.length);
		byteBuffer.put(retweeted_statusBytes);
		byteBuffer.putInt(quote_count);
		byteBuffer.putInt(reply_count);
		byteBuffer.putInt(retweet_count);
		byteBuffer.putInt(favorite_count);
		byteBuffer.putInt(entityBytes.length);
		byteBuffer.put(entityBytes);
		byteBuffer.putInt(extended_tweetBytes.length);
		byteBuffer.put(extended_tweetBytes);
		byteBuffer.put(convertToByte(favorited));
		byteBuffer.put(convertToByte(retweeted));
		byteBuffer.put(convertToByte(possibly_sensitive));
		byteBuffer.putInt(filter_levelByte.length);
		byteBuffer.put(filter_levelByte);
		byteBuffer.putInt(langBytes.length);
		byteBuffer.put(langBytes);
		byteBuffer.putInt(matching_rulesBytes.size());
		for(byte[] matching_ruleBytes : matching_rulesBytes) {
			byteBuffer.putInt(matching_ruleBytes.length);
			byteBuffer.put(matching_ruleBytes);
		}

		byteBuffer.putLong(current_user_retweet);
		byteBuffer.putInt(scopesBytes.size());
		if(scopes != null) {
			int i = 0;
			for(String k : scopes.keySet()) {
				byteBuffer.putInt(scopesBytes.get(i).length);
				byteBuffer.put(scopesBytes.get(i));
				byteBuffer.put(convertToByte(scopes.get(k)));
				i++;
			}
		}

		byteBuffer.put(convertToByte(withheld_copyright));

		byteBuffer.putInt(withheld_in_countries.size());
		for(byte[] withheld_in_countryByte : withheld_in_countriesBytes) {
			byteBuffer.putInt(withheld_in_countryByte.length);
			byteBuffer.put(withheld_in_countryByte);
		}

		byteBuffer.putInt(withheld_scopeBytes.length);
		byteBuffer.put(withheld_scopeBytes);

		byteBuffer.putInt(display_text_range.size());
		for (int i:display_text_range)
			byteBuffer.putInt(i);

		return byteBuffer.array();
	}

	public RootData readByteBuffer(byte[] buffData) {

		ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
		int stringSize;

		stringSize = byteBuffer.getInt();
		this.id_str = extractString(byteBuffer, stringSize);

		stringSize = byteBuffer.getInt();
		this.created_at = extractString(byteBuffer, stringSize);

		this.id = byteBuffer.getLong();
		stringSize = byteBuffer.getInt();
		this.text = extractString(byteBuffer, stringSize);
		stringSize = byteBuffer.getInt();
		this.source = extractString(byteBuffer, stringSize);
		this.truncated = convertToBoolean(byteBuffer.get());

		this.in_reply_to_status_id = byteBuffer.getLong();
		this.in_reply_to_user_id = byteBuffer.getLong();

		stringSize = byteBuffer.getInt();
		this.in_reply_to_screen_name = extractString(byteBuffer, stringSize);

		byte[] userBytes = new byte[byteBuffer.getInt()];
		byteBuffer.get(userBytes, 0, userBytes.length);
		this.user = new User();
		this.user.readByteBuffer(userBytes);

		byte[] coordinateBytes = new byte[byteBuffer.getInt()];
		if(coordinateBytes.length > 0) {
			byteBuffer.get(coordinateBytes, 0, coordinateBytes.length);
			this.coordinates = new Coordinates();
			this.coordinates.readByteBuffer(coordinateBytes);
		}
		else
			this.coordinates = null;

		byte[] placeBytes = new byte[byteBuffer.getInt()];
		if(placeBytes.length > 0) {
			byteBuffer.get(placeBytes, 0, placeBytes.length);
			this.place = new Place();
			this.place.readByteBuffer(placeBytes);
		}
		else
			this.place = null;

		this.quoted_status_id = byteBuffer.getLong();
		this.is_quote_status = convertToBoolean(byteBuffer.get());

		byte[] quoted_statusBytes = new byte[byteBuffer.getInt()];
		if(quoted_statusBytes.length > 0) {
			byteBuffer.get(quoted_statusBytes, 0, quoted_statusBytes.length);
			this.quoted_status = new TweetStatus();
			this.quoted_status.readByteBuffer(quoted_statusBytes);
		}
		else
			this.quoted_status = null;

		byte[] retweeted_statusBytes = new byte[byteBuffer.getInt()];
		if(retweeted_statusBytes.length > 0) {
			byteBuffer.get(retweeted_statusBytes, 0, retweeted_statusBytes.length);
			this.retweeted_status = new TweetStatus();
			this.retweeted_status.readByteBuffer(retweeted_statusBytes);
		}
		else
			this.retweeted_status = null;

		this.quote_count = byteBuffer.getInt();
		this.reply_count = byteBuffer.getInt();
		this.retweet_count = byteBuffer.getInt();
		this.favorite_count = byteBuffer.getInt();

		byte[] entityBytes = new byte[byteBuffer.getInt()];
		if(entityBytes.length > 0) {
			byteBuffer.get(entityBytes, 0, entityBytes.length);
			this.entities = new Entities();
			this.entities.readByteBuffer(entityBytes);
		}
		else
			this.entities = null;

		byte[] extended_tweetBytes = new byte[byteBuffer.getInt()];
		if(extended_tweetBytes.length > 0) {
			byteBuffer.get(extended_tweetBytes, 0, extended_tweetBytes.length);
			this.extended_tweet = new ExtendedTweet();
			this.extended_tweet.readByteBuffer(extended_tweetBytes);
		}
		else
			this.extended_tweet = null;

		this.favorited = convertToBoolean(byteBuffer.get());
		this.retweeted = convertToBoolean(byteBuffer.get());
		this.possibly_sensitive = convertToBoolean(byteBuffer.get());
		stringSize = byteBuffer.getInt();
		this.filter_level = extractString(byteBuffer, stringSize);

		stringSize = byteBuffer.getInt();
		this.lang = extractString(byteBuffer, stringSize);

		int numberofmatching_rules = byteBuffer.getInt();
		if(numberofmatching_rules > 0) {
			this.matching_rules = new ArrayList<>();
			for(int i = 0; i < numberofmatching_rules; i++) {
				byte[] matching_ruleBytes = new byte[byteBuffer.getInt()];
				byteBuffer.get(matching_ruleBytes, 0, matching_ruleBytes.length);
				MatchingRulesEntity matchingRulesEntity = new MatchingRulesEntity();
				matchingRulesEntity.readByteBuffer(matching_ruleBytes);
				this.matching_rules.add(matchingRulesEntity);
			}
		}

		this.current_user_retweet = byteBuffer.getLong();

		int numberofscopes = byteBuffer.getInt();
		if(numberofscopes > 0) {
			this.scopes = new HashMap<>();
			for(int i = 0; i < numberofscopes; i++) {
				stringSize = byteBuffer.getInt();
				String key = extractString(byteBuffer, stringSize);
				boolean value = convertToBoolean(byteBuffer.get());
				this.scopes.put(key, value);
			}
		}

		this.withheld_copyright = convertToBoolean(byteBuffer.get());

		int numberofwithheld_in_countries = byteBuffer.getInt();
		if(numberofwithheld_in_countries > 0) {
			this.withheld_in_countries = new ArrayList<>();
			for(int i = 0; i < numberofwithheld_in_countries; i++) {
				stringSize = byteBuffer.getInt();
				this.withheld_in_countries.add(extractString(byteBuffer, stringSize));
			}
		}

		stringSize = byteBuffer.getInt();
		this.withheld_scope = extractString(byteBuffer, stringSize);

		int numberSize = byteBuffer.getInt();
		this.display_text_range = new ArrayList<>();
		for(int i = 0; i < numberSize; i++) {
			this.display_text_range.add(byteBuffer.getInt());
		}

		return this;
	}

	public int compareTo(RootData o) {
		TweetStatus other = (TweetStatus) o;
		int countLevel = 0;
		int countLevelOtherTweet = 0;

		if(this.tweetStatusFBS == null & this.tweetStatusP == null) {

			// get text
			countLevel += this.text.length();

			countLevelOtherTweet += other.text.length();

			// get QuoteStatus
			if(this.quoted_status != null)
				countLevel += this.quoted_status.getText().length();

			if(other.getQuoted_status() != null)
				countLevelOtherTweet += other.getQuoted_status().getText().length();

			// get Retweet
			if(this.retweeted_status != null)
				countLevel += this.retweeted_status.getRetweet_count();

			if(other.getRetweeted_status() != null)
				countLevelOtherTweet += other.getRetweeted_status().getRetweet_count();
		}
		else if(this.tweetStatusFBS != null & this.tweetStatusP == null) {

			// get text
			countLevel += this.tweetStatusFBS.text().length();

			countLevelOtherTweet += other.tweetStatusFBS.text().length();

			// get QuoteStatus
			if(this.tweetStatusFBS.quotedStatus() != null)
				countLevel += this.tweetStatusFBS.quotedStatus().text().length();

			if(other.tweetStatusFBS.quotedStatus() != null)
				countLevelOtherTweet += other.tweetStatusFBS.quotedStatus().text().length();

			// get Retweet
			if(this.tweetStatusFBS.retweetedStatus() != null)
				countLevel += this.tweetStatusFBS.retweetedStatus().retweetCount();

			if(other.tweetStatusFBS.retweetedStatus() != null)
				countLevelOtherTweet += other.tweetStatusFBS.retweetedStatus().retweetCount();
		}
		else {
			// get text
			countLevel += this.tweetStatusP.getText().length();

			countLevelOtherTweet += other.tweetStatusP.getText().length();

			// get QuoteStatus
			if(this.tweetStatusP.getQuotedStatus() != null)
				countLevel += this.tweetStatusP.getQuotedStatus().getText().length();

			if(other.tweetStatusP.getQuotedStatus() != null)
				countLevelOtherTweet += other.tweetStatusP.getQuotedStatus().getText().length();

			// get Retweet
			if(this.tweetStatusP.getRetweetedStatus() != null)
				countLevel += this.tweetStatusP.getRetweetedStatus().getRetweetCount();

			if(other.tweetStatusP.getRetweetedStatus() != null)
				countLevelOtherTweet += other.tweetStatusP.getRetweetedStatus().getRetweetCount();
		}
		return Integer.compare(countLevel, countLevelOtherTweet);
	}

	public byte[] bsonSerialization() {
		BasicOutputBuffer outputBuffer = new BasicOutputBuffer();
		BsonBinaryWriter writer = new BsonBinaryWriter(outputBuffer);

		writer.writeStartDocument();
		writer.writeString("created_at", this.created_at);
		writer.writeInt64("id", this.id);
		writer.writeString("id_str", this.id_str);
		writer.writeString("text", this.text);
		writer.writeString("source", this.source);
		writer.writeBoolean("truncated", this.truncated);
		writer.writeInt64("in_reply_to_status_id", this.in_reply_to_status_id);
		writer.writeInt64("in_reply_to_user_id", this.in_reply_to_user_id);

		if(this.in_reply_to_screen_name != null)
			writer.writeString("in_reply_to_screen_name", this.in_reply_to_screen_name);

		writer.writeName("user");
		writer.writeBinaryData(new BsonBinary(this.user.bsonSerialization()));

		if(this.coordinates != null)
			writer.writeBinaryData("coordinates", new BsonBinary(this.coordinates.bsonSerialization()));

		if(this.place != null)
			writer.writeBinaryData("place", new BsonBinary(this.place.bsonSerialization()));
		writer.writeInt64("quoted_status_id", this.quoted_status_id);
		writer.writeBoolean("is_quote_status", this.is_quote_status);

		if(this.quoted_status != null)
			writer.writeBinaryData("quoted_status", new BsonBinary(this.quoted_status.bsonSerialization()));

		if(this.retweeted_status != null)
			writer.writeBinaryData("retweeted_status", new BsonBinary(this.retweeted_status.bsonSerialization()));

		writer.writeInt32("quote_count", this.quote_count);
		writer.writeInt32("reply_count", this.reply_count);
		writer.writeInt32("retweet_count", this.retweet_count);
		writer.writeInt32("favorite_count", this.favorite_count);

		if(this.entities != null)
			writer.writeBinaryData("entities", new BsonBinary(this.entities.bsonSerialization()));

		if(this.extended_tweet!= null)
			writer.writeBinaryData("extended_tweet", new BsonBinary(this.extended_tweet.bsonSerialization()));

		writer.writeBoolean("favorited", this.favorited);
		writer.writeBoolean("retweeted", this.retweeted);
		writer.writeBoolean("possibly_sensitive", this.possibly_sensitive);
		writer.writeString("filter_level", this.filter_level);
		if(this.lang != null)
			writer.writeString("lang", this.lang);

		writer.writeInt32("matching_rules_size", this.matching_rules.size());
		writer.writeName("matching_rules");
		writer.writeStartArray();
		for(MatchingRulesEntity matchingRulesEntity : this.matching_rules) {
			writer.writeBinaryData(new BsonBinary(matchingRulesEntity.bsonSerialization()));
		}
		writer.writeEndArray();

		writer.writeInt64("current_user_retweet", this.current_user_retweet);

		writer.writeInt32("scopes_size", this.scopes.size());
		writer.writeName("scopes");
		writer.writeStartDocument();
		for(String k : this.scopes.keySet()) {
			writer.writeBoolean(k, this.scopes.get(k));
		}
		writer.writeEndDocument();

		writer.writeBoolean("withheld_copyright", this.withheld_copyright);

		if(this.withheld_scope != null)
			writer.writeString("withheld_scope", this.withheld_scope);

		writer.writeInt32("withheld_in_countries_size", this.withheld_in_countries.size());
		writer.writeName("withheld_in_countries");
		writer.writeStartArray();
		for(String s : this.withheld_in_countries) {
			writer.writeString(s);
		}

		writer.writeInt32("display_text_range_size", this.display_text_range.size());
		writer.writeName("display_text_range");
		writer.writeStartArray();
		for(Integer i : this.display_text_range) {
			writer.writeInt32(i);
		}

		writer.writeEndArray();

		writer.writeEndDocument();

		return outputBuffer.toByteArray();
	}

	public byte[] flatBuffersSerialization() {
		byte[] data;
		if(tweetStatusFBS == null) {
			FlatBufferBuilder builder = new FlatBufferBuilder(4096);
			int orc = flatBuffersWriter(builder);
			builder.finish(orc);
			data = builder.sizedByteArray();
		}
		else
			data = tweetStatusFBS.getByteBuffer().array();
		return data;
	}

	public int flatBuffersWriter(FlatBufferBuilder builder) {

		int created_atBuilder = builder.createString(this.created_at);
		int textBuilder = this.text != null ? builder.createString(this.text) : 0;
		int sourceBuilder = this.source != null ? builder.createString(this.source) : 0;
		int in_reply_to_screen_nameBuilder = this.in_reply_to_screen_name != null ? builder
			.createString(this.in_reply_to_screen_name) : 0;
		int filter_levelBuilder = this.filter_level != null ? builder.createString(this.filter_level) : 0;
		int langBuilder = this.lang != null ? builder.createString(this.lang) : 0;
		int withheld_scopeBuilder = this.withheld_scope != null ? builder.createString(this.withheld_scope) : 0;
		int quoted_statusBuilder = this.quoted_status != null ? this.quoted_status.flatBuffersWriter(builder) : 0;
		int retweeted_statusBuilder = this.retweeted_status != null ? this.retweeted_status
			.flatBuffersWriter(builder) : 0;

		int[] scopesList = new int[this.scopes.size()];
		int i = 0;
		for(String key : this.scopes.keySet()) {
			int keyBuilder = builder.createString(key);
			boolean valueBuilder = this.scopes.get(key);

			int mapitem = MapStringBool.createMapStringBool(builder, keyBuilder, valueBuilder);
			scopesList[i] = mapitem;
			i++;
		}
		int scopesBuilder = TweetStatusFBS.createScopesVector(builder, scopesList);

		int[] withheld_in_countriesList = new int[this.withheld_in_countries.size()];
		i = 0;
		for(String s : this.withheld_in_countries) {
			int item = builder.createString(s);
			withheld_in_countriesList[i] = item;
			i++;
		}

		int withheld_in_countriesBuilder = TweetStatusFBS
			.createWithheldInCountriesVector(builder, withheld_in_countriesList);
		int userBuilder = this.user.flatBuffersWriter(builder);
		int coordinatesBuilder = this.coordinates != null ? this.coordinates.flatBuffersWriter(builder) : 0;
		int placeBuilder = this.place != null ? this.place.flatBuffersWriter(builder) : 0;
		int entitiesBuilder = this.entities != null ? this.entities.flatBuffersWriter(builder) : 0;
		int extended_entitiesBuilder = this.extended_entities != null ? this.extended_entities
			.flatBuffersWriter(builder) : 0;

		int[] matching_rulesList = new int[this.matching_rules.size()];
		i = 0;
		for(MatchingRulesEntity matchingRulesEntity : this.matching_rules) {
			matching_rulesList[i] = matchingRulesEntity.flatBuffersWriter(builder);
			i++;
		}
		int matching_rulesBuilder = TweetStatusFBS.createMatchingRulesVector(builder, matching_rulesList);

		TweetStatusFBS.startTweetStatusFBS(builder);
		TweetStatusFBS.addCreatedAt(builder, created_atBuilder);
		TweetStatusFBS.addId(builder, this.id);
		TweetStatusFBS.addText(builder, textBuilder);
		TweetStatusFBS.addSource(builder, sourceBuilder);
		TweetStatusFBS.addTruncated(builder, this.isTruncated());
		TweetStatusFBS.addInReplyToStatusId(builder, this.in_reply_to_status_id);
		TweetStatusFBS.addInReplyToScreenName(builder, in_reply_to_screen_nameBuilder);
		TweetStatusFBS.addUser(builder, userBuilder);
		TweetStatusFBS.addCoordinates(builder, coordinatesBuilder);
		TweetStatusFBS.addPlace(builder, placeBuilder);
		TweetStatusFBS.addQuotedStatusId(builder, this.quoted_status_id);
		TweetStatusFBS.addIsQuoteStatus(builder, this.is_quote_status);
		TweetStatusFBS.addQuotedStatus(builder, quoted_statusBuilder);
		TweetStatusFBS.addRetweetedStatus(builder, retweeted_statusBuilder);
		TweetStatusFBS.addQuoteCount(builder, this.getQuote_count());
		TweetStatusFBS.addReplyCount(builder, this.reply_count);
		TweetStatusFBS.addRetweetCount(builder, this.retweet_count);
		TweetStatusFBS.addFavoriteCount(builder, this.favorite_count);
		TweetStatusFBS.addEntities(builder, entitiesBuilder);
		TweetStatusFBS.addExtendedEntities(builder, extended_entitiesBuilder);
		TweetStatusFBS.addFavorited(builder, this.favorited);
		TweetStatusFBS.addRetweeted(builder, this.retweeted);
		TweetStatusFBS.addPossiblySensitive(builder, this.isPossibly_sensitive());
		TweetStatusFBS.addFilterLevel(builder, filter_levelBuilder);
		TweetStatusFBS.addLang(builder, langBuilder);
		TweetStatusFBS.addMatchingRules(builder, matching_rulesBuilder);
		TweetStatusFBS.addCurrentUserRetweet(builder, this.current_user_retweet);
		TweetStatusFBS.addScopes(builder, scopesBuilder);
		TweetStatusFBS.addWithheldCopyright(builder, this.withheld_copyright);
		TweetStatusFBS.addWithheldInCountries(builder, withheld_in_countriesBuilder);
		TweetStatusFBS.addWithheldScope(builder, withheld_scopeBuilder);

		int orc = TweetStatusFBS.endTweetStatusFBS(builder);
		return orc;
	}

	public TweetStatus flatBuffersDeserialization(byte[] buffData) {
		java.nio.ByteBuffer buf = java.nio.ByteBuffer.wrap(buffData);
		this.tweetStatusFBS = TweetStatusFBS.getRootAsTweetStatusFBS(buf);

		return this;// getFlatBuffersDeserialization(tweetStatusFBS);
	}

	//    public TweetStatus getFlatBuffersDeserialization(TweetStatusFBS tweetStatusFBS) {
	//
	//
	//        this.created_at = tweetStatusFBS.createdAt();
	//        this.id = tweetStatusFBS.id();
	//        this.text = tweetStatusFBS.text();
	//        this.source = tweetStatusFBS.source();
	//        this.truncated = tweetStatusFBS.truncated();
	//        this.in_reply_to_status_id = tweetStatusFBS.inReplyToStatusId();
	//        this.in_reply_to_user_id = tweetStatusFBS.inReplyToUserId();
	//        this.in_reply_to_screen_name = tweetStatusFBS.inReplyToScreenName();
	//        this.user=new User();
	//        this.user.flatBuffersDeserialization(tweetStatusFBS.user());
	//        if (tweetStatusFBS.coordinates()!=null) {
	//            this.coordinates = new Coordinates();
	//            this.coordinates.flatBuffersDeserialization(tweetStatusFBS.coordinates());
	//        }
	//        if (tweetStatusFBS.place()!=null) {
	//            this.place = new Place();
	//            this.place.flatBuffersDeserialization(tweetStatusFBS.place());
	//        }
	//        this.quoted_status_id = tweetStatusFBS.quotedStatusId();
	//        this.is_quote_status = tweetStatusFBS.isQuoteStatus();
	//
	//        if (tweetStatusFBS.quotedStatus()!=null) {
	//            this.quoted_status = new TweetStatus();
	//            this.quoted_status.getFlatBuffersDeserialization(tweetStatusFBS.quotedStatus());
	//        }
	//        if (tweetStatusFBS.place()!=null) {
	//            this.retweeted_status = new TweetStatus();
	//            this.retweeted_status.getFlatBuffersDeserialization(tweetStatusFBS.retweetedStatus());
	//        }
	//        this.quote_count = tweetStatusFBS.quoteCount();
	//        this.reply_count = tweetStatusFBS.replyCount();
	//        this.retweet_count = tweetStatusFBS.retweetCount();
	//        this.favorite_count = tweetStatusFBS.favoriteCount();
	//        //this.entities=tweetStatusFBS.;
	//        //this.extended_entities=tweetStatusFBS.;
	//        this.favorited = tweetStatusFBS.favorited();
	//        this.retweeted = tweetStatusFBS.retweeted();
	//        this.possibly_sensitive = tweetStatusFBS.possiblySensitive();
	//        this.filter_level = tweetStatusFBS.filterLevel();
	//        this.lang = tweetStatusFBS.lang();
	//        //this.matching_rules=tweetStatusFBS.;
	//        this.current_user_retweet = tweetStatusFBS.currentUserRetweet();
	//        //this.scopes=tweetStatusFBS.;
	//        this.withheld_copyright = tweetStatusFBS.withheldCopyright();
	//        //this.withheld_in_countries=tweetStatusFBS.;
	//        this.withheld_scope = tweetStatusFBS.withheldScope();
	//        return this;
	//    }

	public RootData bsonDeSerialization(byte[] buffData) {
		ByteBuffer buf = ByteBuffer.wrap(buffData);
		BsonBinaryReader reader = new BsonBinaryReader(buf);

		reader.readStartDocument();
		this.created_at = reader.readString("created_at");
		this.id = reader.readInt64("id");
		this.id_str = reader.readString("id_str");
		this.text = reader.readString("text");
		this.source = reader.readString("source");
		this.truncated = reader.readBoolean("truncated");
		this.in_reply_to_status_id = reader.readInt64("in_reply_to_status_id");
		this.in_reply_to_user_id = reader.readInt64("in_reply_to_user_id");

		String currentName = reader.readName();
		if(currentName.equals("in_reply_to_screen_name")) {
			this.in_reply_to_screen_name = reader.readString();
			reader.readName();
		}

		this.user = new User();
		this.user.bsonDeSerialization(reader.readBinaryData().getData());

		currentName = reader.readName();
		if(currentName.equals("coordinates")) {
			this.coordinates = new Coordinates();
			this.coordinates.bsonDeSerialization(reader.readBinaryData().getData());
			currentName = reader.readName();
		}

		if(currentName.equals("place")) {
			this.place = new Place();
			this.place.bsonDeSerialization(reader.readBinaryData().getData());
			reader.readName();
		}

		this.quoted_status_id = reader.readInt64();
		this.is_quote_status = reader.readBoolean("is_quote_status");

		currentName = reader.readName();
		if(currentName.equals("quoted_status")) {
			this.quoted_status = new TweetStatus();
			this.quoted_status.bsonDeSerialization(reader.readBinaryData().getData());
			currentName = reader.readName();
		}

		if(currentName.equals("retweeted_status")) {
			this.retweeted_status = new TweetStatus();
			this.retweeted_status.bsonDeSerialization(reader.readBinaryData().getData());
			reader.readName();
		}

		this.quote_count = reader.readInt32();
		this.reply_count = reader.readInt32("reply_count");
		this.retweet_count = reader.readInt32("retweet_count");
		this.favorite_count = reader.readInt32("favorite_count");

		currentName = reader.readName();
		if(currentName.equals("entities")) {
			this.entities = new Entities();
			this.entities.bsonDeSerialization(reader.readBinaryData().getData());
			currentName = reader.readName();
		}

		if(currentName.equals("extended_tweet")) {
			this.extended_tweet = new ExtendedTweet();
			this.extended_tweet.bsonDeSerialization(reader.readBinaryData().getData());
			reader.readName();
		}

		this.favorited = reader.readBoolean();
		this.retweeted = reader.readBoolean("retweeted");
		this.possibly_sensitive = reader.readBoolean("possibly_sensitive");
		this.filter_level = reader.readString("filter_level");

		currentName = reader.readName();
		if(currentName.equals("lang")) {
			this.lang = reader.readString();
			reader.readName();
		}

		int list_size = reader.readInt32();
		reader.readName("matching_rules");
		reader.readStartArray();
		for(int i = 0; i < list_size; i++) {
			MatchingRulesEntity matchingRulesEntity = new MatchingRulesEntity();
			matchingRulesEntity.bsonDeSerialization(reader.readBinaryData().getData());
			this.matching_rules.add(matchingRulesEntity);
		}
		reader.readEndArray();

		this.current_user_retweet = reader.readInt64("current_user_retweet");

		int scopes_size = reader.readInt32("scopes_size");
		reader.readName("scopes");
		reader.readStartDocument();
		for(int i = 0; i < scopes_size; i++) {
			String key = reader.readName();
			Boolean value = reader.readBoolean();
			this.scopes.put(key, value);
		}
		reader.readEndDocument();
		this.withheld_copyright = reader.readBoolean("withheld_copyright");

		currentName = reader.readName();
		if(currentName.equals("withheld_scope")) {
			this.withheld_scope = reader.readString();
			reader.readName();
		}

		int withheld_in_countries_size = reader.readInt32();
		reader.readName("withheld_in_countries");
		reader.readStartArray();
		for(int i = 0; i < withheld_in_countries_size; i++) {
			this.withheld_in_countries.add(reader.readString());
		}

		int display_text_range_size = reader.readInt32("display_text_range_size");
		reader.readName("display_text_range");
		reader.readStartArray();
		for(int i = 0; i < display_text_range_size; i++) {
			this.display_text_range.add(reader.readInt32());
		}

		reader.readEndArray();
		reader.readEndDocument();

		return this;
	}
}
