package edu.bu.tweet;

import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.List;

import com.google.flatbuffers.FlatBufferBuilder;
import edu.bu.tweet.flatbuffers.TweetStatusFBS;
import edu.bu.tweet.flatbuffers.UserFBS;
import edu.bu.util.Base;
import edu.bu.util.RootData;

import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonValue;

import org.apache.log4j.Logger;
import org.bson.BsonBinary;
import org.bson.BsonBinaryReader;
import org.bson.BsonBinaryWriter;
import org.bson.io.BasicOutputBuffer;


public class User extends Base implements RootData {

    private static final long serialVersionUID = -552271746474217669L;

    static Logger logger = Logger.getLogger(User.class);

    private long id;
    private String name;
    private String screen_name;
    private String location;//nullable
    private String url;//nullable
    private String description;//nullable
    //TODO: protected is a java keyboard so we need a solution for get data from text string
    private boolean isProtected;
    private boolean verified;
    private int followers_count;
    private int friends_count;
    private int listed_count;
    private int favourites_count;
    private int statuses_count;
    private String created_at;
    private String profile_banner_url;
    private String profile_image_url_https;
    private boolean default_profile;
    private List<String> withheld_in_countries;
    private String withheld_scope;

    //No longer supported (deprecated) attributes
    private List<URLEntity> descriptionURLEntities;
    private boolean geo_enabled;
    private String lang;
    private boolean contributors_enabled;
    private String profile_background_color;
    private String profile_background_image_url;
    private String profile_background_image_url_https;
    private boolean profile_background_tile;
    private String profile_image_url;
    private String profile_link_color;
    private String profile_sidebar_border_color;
    private String profile_sidebar_fill_color;
    private String profile_text_color;
    private boolean profile_use_background_image;
    private int utc_offset;
    private String time_zone;
    private boolean is_translator;
    private boolean follow_request_sent;
    private boolean showAllInlineMedia;

    public User() {
        withheld_in_countries = new ArrayList<>();
        descriptionURLEntities = new ArrayList<>();
        geo_enabled = false;
        contributors_enabled = false;
        profile_background_tile = false;
        profile_use_background_image = false;
        utc_offset = -999;
        is_translator = false;
        follow_request_sent = false;
        showAllInlineMedia = false;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getScreen_name() {
        return screen_name;
    }

    public void setScreen_name(String screen_name) {
        this.screen_name = screen_name;
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public boolean isProtected() {
        return isProtected;
    }

    public void setProtected(boolean aProtected) {
        isProtected = aProtected;
    }

    public boolean isVerified() {
        return verified;
    }

    public void setVerified(boolean verified) {
        this.verified = verified;
    }

    public int getFollowers_count() {
        return followers_count;
    }

    public void setFollowers_count(int followers_count) {
        this.followers_count = followers_count;
    }

    public int getFriends_count() {
        return friends_count;
    }

    public void setFriends_count(int friends_count) {
        this.friends_count = friends_count;
    }

    public int getListed_count() {
        return listed_count;
    }

    public void setListed_count(int listed_count) {
        this.listed_count = listed_count;
    }

    public int getFavourites_count() {
        return favourites_count;
    }

    public void setFavourites_count(int favourites_count) {
        this.favourites_count = favourites_count;
    }

    public int getStatuses_count() {
        return statuses_count;
    }

    public void setStatuses_count(int statuses_count) {
        this.statuses_count = statuses_count;
    }

    public String getCreated_at() {
        return created_at;
    }

    public void setCreated_at(String created_at) {
        this.created_at = created_at;
    }

    public String getProfile_banner_url() {
        return profile_banner_url;
    }

    public void setProfile_banner_url(String profile_banner_url) {
        this.profile_banner_url = profile_banner_url;
    }

    public String getProfile_image_url_https() {
        return profile_image_url_https;
    }

    public void setProfile_image_url_https(String profile_image_url_https) {
        this.profile_image_url_https = profile_image_url_https;
    }

    public boolean isDefault_profile() {
        return default_profile;
    }

    public void setDefault_profile(boolean default_profile) {
        this.default_profile = default_profile;
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

    public List<URLEntity> getDescriptionURLEntities() {
        return descriptionURLEntities;
    }

    public void setDescriptionURLEntities(List<URLEntity> descriptionURLEntities) {
        this.descriptionURLEntities = descriptionURLEntities;
    }

    public boolean isGeo_enabled() {
        return geo_enabled;
    }

    public void setGeo_enabled(boolean geo_enabled) {
        this.geo_enabled = geo_enabled;
    }

    public String getLang() {
        return lang;
    }

    public void setLang(String lang) {
        this.lang = lang;
    }

    public boolean isContributors_enabled() {
        return contributors_enabled;
    }

    public void setContributors_enabled(boolean contributors_enabled) {
        this.contributors_enabled = contributors_enabled;
    }

    public String getProfile_background_color() {
        return profile_background_color;
    }

    public void setProfile_background_color(String profile_background_color) {
        this.profile_background_color = profile_background_color;
    }

    public String getProfile_background_image_url() {
        return profile_background_image_url;
    }

    public void setProfile_background_image_url(String profile_background_image_url) {
        this.profile_background_image_url = profile_background_image_url;
    }

    public String getProfile_background_image_url_https() {
        return profile_background_image_url_https;
    }

    public void setProfile_background_image_url_https(String profile_background_image_url_https) {
        this.profile_background_image_url_https = profile_background_image_url_https;
    }

    public boolean isProfile_background_tile() {
        return profile_background_tile;
    }

    public void setProfile_background_tile(boolean profile_background_tile) {
        this.profile_background_tile = profile_background_tile;
    }

    public String getProfile_image_url() {
        return profile_image_url;
    }

    public void setProfile_image_url(String profile_image_url) {
        this.profile_image_url = profile_image_url;
    }

    public String getProfile_link_color() {
        return profile_link_color;
    }

    public void setProfile_link_color(String profile_link_color) {
        this.profile_link_color = profile_link_color;
    }

    public String getProfile_sidebar_border_color() {
        return profile_sidebar_border_color;
    }

    public void setProfile_sidebar_border_color(String profile_sidebar_border_color) {
        this.profile_sidebar_border_color = profile_sidebar_border_color;
    }

    public String getProfile_sidebar_fill_color() {
        return profile_sidebar_fill_color;
    }

    public void setProfile_sidebar_fill_color(String profile_sidebar_fill_color) {
        this.profile_sidebar_fill_color = profile_sidebar_fill_color;
    }

    public String getProfile_text_color() {
        return profile_text_color;
    }

    public void setProfile_text_color(String profile_text_color) {
        this.profile_text_color = profile_text_color;
    }

    public boolean isProfile_use_background_image() {
        return profile_use_background_image;
    }

    public void setProfile_use_background_image(boolean profile_use_background_image) {
        this.profile_use_background_image = profile_use_background_image;
    }

    public int getUtc_offset() {
        return utc_offset;
    }

    public void setUtc_offset(int utc_offset) {
        this.utc_offset = utc_offset;
    }

    public String getTime_zone() {
        return time_zone;
    }

    public void setTime_zone(String time_zone) {
        this.time_zone = time_zone;
    }

    public boolean isIs_translator() {
        return is_translator;
    }

    public void setIs_translator(boolean is_translator) {
        this.is_translator = is_translator;
    }

    public boolean isFollow_request_sent() {
        return follow_request_sent;
    }

    public void setFollow_request_sent(boolean follow_request_sent) {
        this.follow_request_sent = follow_request_sent;
    }

    public boolean isShowAllInlineMedia() {
        return showAllInlineMedia;
    }

    public void setShowAllInlineMedia(boolean showAllInlineMedia) {
        this.showAllInlineMedia = showAllInlineMedia;
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

        byte[] screen_nameBytes = screen_name.getBytes(Charset.forName("UTF-8"));
        allocatedBufferSize += screen_nameBytes.length + 4;

        byte[] locationBytes = (location != null) ? location.getBytes() : new byte[0];
        allocatedBufferSize += locationBytes.length + 4;

        byte[] urlBytes = (url != null) ? url.getBytes() : new byte[0];
        allocatedBufferSize += urlBytes.length + 4;

        byte[] descriptionBytes = (description != null) ? description.getBytes() : new byte[0];
        allocatedBufferSize += descriptionBytes.length + 4;

        byte[] created_atBytes = created_at.getBytes();
        allocatedBufferSize += created_atBytes.length + 4;

        byte[] profile_banner_urlBytes = (profile_banner_url != null) ? profile_banner_url.getBytes() : new byte[0];
        allocatedBufferSize += profile_banner_urlBytes.length + 4;

        byte[] profile_image_url_httpsBytes = profile_image_url_https.getBytes();
        allocatedBufferSize += profile_image_url_httpsBytes.length + 4;

        ArrayList<byte[]> withheld_in_countriesBytes = new ArrayList<>();
        for (String s : withheld_in_countries) {
            byte[] withheld_in_countryByte = s.getBytes();
            withheld_in_countriesBytes.add(withheld_in_countryByte);
            allocatedBufferSize += withheld_in_countryByte.length + 4;
        }
        allocatedBufferSize += 4;

        byte[] withheld_scopeBytes = (withheld_scope != null) ? withheld_scope.getBytes() : new byte[0];
        allocatedBufferSize += withheld_scopeBytes.length + 4;

        ArrayList<byte[]> descriptionURLEntitiesBytes = new ArrayList<>();
        for (URLEntity urlEntity : descriptionURLEntities) {
            byte[] urlEntityBytes = urlEntity.writeByteBuffer();
            descriptionURLEntitiesBytes.add(urlEntityBytes);
            allocatedBufferSize += urlEntityBytes.length + 4;
        }
        allocatedBufferSize += 4;

        byte[] langBytes = (lang != null) ? lang.getBytes() : new byte[0];
        allocatedBufferSize += langBytes.length + 4;

        byte[] profile_background_colorBytes = (profile_background_color != null) ? profile_background_color.getBytes() : new byte[0];
        allocatedBufferSize += profile_background_colorBytes.length + 4;

        byte[] profile_background_image_urlBytes = (profile_background_image_url != null) ? profile_background_image_url.getBytes() : new byte[0];
        allocatedBufferSize += profile_background_image_urlBytes.length + 4;

        byte[] profile_background_image_url_httpsBytes = (profile_background_image_url_https != null) ? profile_background_image_url_https.getBytes() : new byte[0];
        allocatedBufferSize += profile_background_image_url_httpsBytes.length + 4;

        byte[] profile_image_urlBytes = (profile_image_url != null) ? profile_image_url.getBytes() : new byte[0];
        allocatedBufferSize += profile_image_urlBytes.length + 4;

        byte[] profile_link_colorBytes = (profile_link_color != null) ? profile_link_color.getBytes() : new byte[0];
        allocatedBufferSize += profile_link_colorBytes.length + 4;

        byte[] profile_sidebar_border_colorBytes = (profile_sidebar_border_color != null) ? profile_sidebar_border_color.getBytes() : new byte[0];
        allocatedBufferSize += profile_sidebar_border_colorBytes.length + 4;

        byte[] profile_sidebar_fill_colorBytes = (profile_sidebar_fill_color != null) ? profile_sidebar_fill_color.getBytes() : new byte[0];
        allocatedBufferSize += profile_sidebar_fill_colorBytes.length + 4;

        byte[] profile_text_colorBytes = (profile_text_color != null) ? profile_text_color.getBytes() : new byte[0];
        allocatedBufferSize += profile_text_colorBytes.length + 4;

        byte[] time_zoneBytes = (time_zone != null) ? time_zone.getBytes() : new byte[0];
        allocatedBufferSize += time_zoneBytes.length + 4;

        allocatedBufferSize += 8; // id;
        allocatedBufferSize += 1; // isProtected;
        allocatedBufferSize += 1; // verified;
        allocatedBufferSize += 4; // followers_count;
        allocatedBufferSize += 4; // friends_count;
        allocatedBufferSize += 4; // listed_count;
        allocatedBufferSize += 4; // favourites_count;
        allocatedBufferSize += 4; // statuses_count;
        allocatedBufferSize += 1; // default_profile;
        allocatedBufferSize += 1; // geo_enabled;
        allocatedBufferSize += 1; // contributors_enabled;
        allocatedBufferSize += 1; // profile_background_tile;
        allocatedBufferSize += 1; // profile_use_background_image;
        allocatedBufferSize += 4; // utc_offset;
        allocatedBufferSize += 1; //is_translator;
        allocatedBufferSize += 1; // follow_request_sent;
        allocatedBufferSize += 1; // showAllInlineMedia;

        // array fields
        ByteBuffer byteBuffer = ByteBuffer.allocate(allocatedBufferSize);
        byteBuffer.putLong(id);
        byteBuffer.putInt(nameBytes.length);
        byteBuffer.put(nameBytes);
        byteBuffer.putInt(screen_nameBytes.length);
        byteBuffer.put(screen_nameBytes);
        byteBuffer.putInt(locationBytes.length);
        byteBuffer.put(locationBytes);
        byteBuffer.putInt(urlBytes.length);
        byteBuffer.put(urlBytes);
        byteBuffer.putInt(descriptionBytes.length);
        byteBuffer.put(descriptionBytes);
        byteBuffer.put(convertToByte(isProtected));
        byteBuffer.put(convertToByte(verified));
        byteBuffer.putInt(followers_count);
        byteBuffer.putInt(friends_count);
        byteBuffer.putInt(listed_count);
        byteBuffer.putInt(favourites_count);
        byteBuffer.putInt(statuses_count);

        byteBuffer.putInt(created_atBytes.length);
        byteBuffer.put(created_atBytes);
        byteBuffer.putInt(profile_banner_urlBytes.length);
        byteBuffer.put(profile_banner_urlBytes);
        byteBuffer.putInt(profile_image_url_httpsBytes.length);
        byteBuffer.put(profile_image_url_httpsBytes);
        byteBuffer.put(convertToByte(default_profile));
        byteBuffer.putInt(withheld_in_countriesBytes.size());
        for (byte[] withheld_in_countryByte : withheld_in_countriesBytes) {
            byteBuffer.putInt(withheld_in_countryByte.length);
            byteBuffer.put(withheld_in_countryByte);
        }

        byteBuffer.putInt(withheld_scopeBytes.length);
        byteBuffer.put(withheld_scopeBytes);
        byteBuffer.putInt(descriptionURLEntitiesBytes.size());
        for (byte[] descriptionURLEntitiesByte : descriptionURLEntitiesBytes) {
            byteBuffer.putInt(descriptionURLEntitiesByte.length);
            byteBuffer.put(descriptionURLEntitiesByte);
        }
        byteBuffer.put(convertToByte(geo_enabled));
        byteBuffer.putInt(langBytes.length);
        byteBuffer.put(langBytes);
        byteBuffer.put(convertToByte(contributors_enabled));
        byteBuffer.putInt(profile_background_colorBytes.length);
        byteBuffer.put(profile_background_colorBytes);
        byteBuffer.putInt(profile_background_image_urlBytes.length);
        byteBuffer.put(profile_background_image_urlBytes);
        byteBuffer.putInt(profile_background_image_url_httpsBytes.length);
        byteBuffer.put(profile_background_image_url_httpsBytes);
        byteBuffer.put(convertToByte(profile_background_tile));
        byteBuffer.putInt(profile_image_urlBytes.length);
        byteBuffer.put(profile_image_urlBytes);
        byteBuffer.putInt(profile_link_colorBytes.length);
        byteBuffer.put(profile_link_colorBytes);
        byteBuffer.putInt(profile_sidebar_border_colorBytes.length);
        byteBuffer.put(profile_sidebar_border_colorBytes);
        byteBuffer.putInt(profile_sidebar_fill_colorBytes.length);
        byteBuffer.put(profile_sidebar_fill_colorBytes);
        byteBuffer.putInt(profile_text_colorBytes.length);
        byteBuffer.put(profile_text_colorBytes);
        byteBuffer.put(convertToByte(profile_use_background_image));
        byteBuffer.putInt(utc_offset);
        byteBuffer.putInt(time_zoneBytes.length);
        byteBuffer.put(time_zoneBytes);
        byteBuffer.put(convertToByte(is_translator));
        byteBuffer.put(convertToByte(follow_request_sent));
        byteBuffer.put(convertToByte(showAllInlineMedia));

        return byteBuffer.array();
    }

    public RootData readByteBuffer(byte[] buffData) {
        ByteBuffer byteBuffer = ByteBuffer.wrap(buffData);
        int stringSize;

        this.id = byteBuffer.getLong();
        stringSize = byteBuffer.getInt();
        this.name = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.screen_name = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.location = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.url = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.description = extractString(byteBuffer, stringSize);
        this.isProtected = convertToBoolean(byteBuffer.get());
        this.verified = convertToBoolean(byteBuffer.get());
        this.followers_count = byteBuffer.getInt();
        this.friends_count = byteBuffer.getInt();
        this.listed_count = byteBuffer.getInt();
        this.favourites_count = byteBuffer.getInt();
        this.statuses_count = byteBuffer.getInt();
        stringSize = byteBuffer.getInt();
        this.created_at = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.profile_banner_url = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.profile_image_url_https = extractString(byteBuffer, stringSize);
        this.default_profile = convertToBoolean(byteBuffer.get());
        for (int i = 0; i < byteBuffer.getInt(); i++) {
            stringSize = byteBuffer.getInt();
            this.withheld_in_countries.add(extractString(byteBuffer, stringSize));
        }
        stringSize = byteBuffer.getInt();
        this.withheld_scope = extractString(byteBuffer, stringSize);


        int numberOfUrlEntities = byteBuffer.getInt();
        if (numberOfUrlEntities > 0) {
            for (int i = 0; i < numberOfUrlEntities; i++) {
                byte[] urlEntityBytes = new byte[byteBuffer.getInt()];
                byteBuffer.get(urlEntityBytes, 0, urlEntityBytes.length);
                URLEntity urlEntity = new URLEntity();
                urlEntity.readByteBuffer(urlEntityBytes);
                this.descriptionURLEntities.add(urlEntity);
            }
        }

        this.geo_enabled = convertToBoolean(byteBuffer.get());
        stringSize = byteBuffer.getInt();
        this.lang = extractString(byteBuffer, stringSize);
        this.contributors_enabled = convertToBoolean(byteBuffer.get());
        stringSize = byteBuffer.getInt();
        this.profile_background_color = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.profile_background_image_url = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.profile_background_image_url_https = extractString(byteBuffer, stringSize);
        this.profile_background_tile = convertToBoolean(byteBuffer.get());
        stringSize = byteBuffer.getInt();
        this.profile_image_url = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.profile_link_color = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.profile_sidebar_border_color = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.profile_sidebar_fill_color = extractString(byteBuffer, stringSize);
        stringSize = byteBuffer.getInt();
        this.profile_text_color = extractString(byteBuffer, stringSize);
        this.profile_use_background_image = convertToBoolean(byteBuffer.get());
        this.utc_offset = byteBuffer.getInt();
        stringSize = byteBuffer.getInt();
        this.time_zone = extractString(byteBuffer, stringSize);
        this.is_translator = convertToBoolean(byteBuffer.get());
        this.follow_request_sent = convertToBoolean(byteBuffer.get());
        this.showAllInlineMedia = convertToBoolean(byteBuffer.get());

        return this;
        //TODO: protected is a java keyboard so we need a solution for get data from text string

    }

    public int compareTo(RootData o) {
        return 0;
    }

    public JsonObject jsonObjectBuilder() {

        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
        objectBuilder.add("id", this.id);
        if (this.name != null && !this.name.isEmpty()) {
            objectBuilder.add("name", this.name);
        }
        if (this.screen_name != null && !this.screen_name.isEmpty()) {
            objectBuilder.add("screen_name", this.screen_name);
        }
        if (this.location != null && !this.location.isEmpty()) {
            objectBuilder.add("location", this.location);
        }
        if (this.url != null && !this.url.isEmpty()) {
            objectBuilder.add("url", this.url);
        }
        if (this.description != null && !this.description.isEmpty()) {
            objectBuilder.add("description", this.description);
        }
        objectBuilder.add("isProtected", this.isProtected);
        objectBuilder.add("verified", this.verified);
        objectBuilder.add("followers_count", this.followers_count);
        objectBuilder.add("friends_count", this.friends_count);
        objectBuilder.add("listed_count", this.listed_count);
        objectBuilder.add("favourites_count", this.favourites_count);
        objectBuilder.add("statuses_count", this.statuses_count);

        if (this.created_at != null && !this.created_at.isEmpty()) {
            objectBuilder.add("created_at", this.created_at);
        }
        if (this.profile_banner_url != null && !this.profile_banner_url.isEmpty()) {
            objectBuilder.add("profile_banner_url", this.profile_banner_url);
        }
        if (this.profile_image_url_https != null && !this.profile_image_url_https.isEmpty()) {
            objectBuilder.add("profile_image_url_https", this.profile_image_url_https);
        }
        objectBuilder.add("default_profile", this.default_profile);

        JsonArrayBuilder jsonWithheld_in_countriesArray = Json.createArrayBuilder();
        for (String s : withheld_in_countries) {
            jsonWithheld_in_countriesArray.add(s);
        }
        objectBuilder.add("withheld_in_countries", jsonWithheld_in_countriesArray);

        if (this.withheld_scope != null && !this.withheld_scope.isEmpty()) {
            objectBuilder.add("withheld_scope", this.withheld_scope);
        }
        if (descriptionURLEntities.size() > 0) {
            JsonArrayBuilder jsonDescriptionURLEntitiesArray = Json.createArrayBuilder();
            for (URLEntity urlEntity : descriptionURLEntities) {
                jsonDescriptionURLEntitiesArray.add(urlEntity.jsonObjectBuilder());
            }
            objectBuilder.add("descriptionURLEntities", jsonDescriptionURLEntitiesArray);
        }
        objectBuilder.add("geo_enabled", this.geo_enabled);

        if (this.lang != null && !this.lang.isEmpty()) {
            objectBuilder.add("lang", this.lang);
        }
        objectBuilder.add("contributors_enabled", this.contributors_enabled);

        if (this.profile_background_color != null && !this.profile_background_color.isEmpty()) {
            objectBuilder.add("profile_background_color", this.profile_background_color);
        }
        if (this.profile_background_image_url != null && !this.profile_background_image_url.isEmpty()) {
            objectBuilder.add("profile_background_image_url", this.profile_background_image_url);
        }
        if (this.profile_background_image_url_https != null && !this.profile_background_image_url_https.isEmpty()) {
            objectBuilder.add("profile_background_image_url_https", this.profile_background_image_url_https);
        }
        objectBuilder.add("profile_background_tile", this.profile_background_tile);
        if (this.profile_image_url != null && !this.profile_image_url.isEmpty()) {
            objectBuilder.add("profile_image_url", this.profile_image_url);
        }
        if (this.profile_link_color != null && !this.profile_link_color.isEmpty()) {
            objectBuilder.add("profile_link_color", this.profile_link_color);
        }
        if (this.profile_sidebar_border_color != null && !this.profile_sidebar_border_color.isEmpty()) {
            objectBuilder.add("profile_sidebar_border_color", this.profile_sidebar_border_color);
        }
        if (this.profile_sidebar_fill_color != null && !this.profile_sidebar_fill_color.isEmpty()) {
            objectBuilder.add("profile_sidebar_fill_color", this.profile_sidebar_fill_color);
        }
        if (this.profile_text_color != null && !this.profile_text_color.isEmpty()) {
            objectBuilder.add("profile_text_color", this.profile_text_color);
        }
        objectBuilder.add("profile_use_background_image", this.profile_use_background_image);
        objectBuilder.add("utc_offset", this.utc_offset);
        if (this.time_zone != null && !this.time_zone.isEmpty()) {
            objectBuilder.add("time_zone", this.time_zone);
        }
        objectBuilder.add("is_translator", this.is_translator);
        objectBuilder.add("follow_request_sent", this.follow_request_sent);
        objectBuilder.add("showAllInlineMedia", this.showAllInlineMedia);

        JsonObject jsonObject = objectBuilder.build();
        return jsonObject;
    }

    public User readJSONUser(JsonObject jsonObject) {

        this.id = Long.parseLong(jsonObject.getJsonNumber("id").toString());
        if (jsonObject.get("name") != null && jsonObject.get("name") != JsonValue.NULL) {
            this.name = jsonObject.getString("name");
        }
        if (jsonObject.get("screen_name") != null && jsonObject.get("screen_name") != JsonValue.NULL) {
            this.screen_name = jsonObject.getString("screen_name");
        }
        if (jsonObject.get("location") != null && jsonObject.get("location") != JsonValue.NULL) {
            this.location = jsonObject.getString("location");
        }
        if (jsonObject.get("url") != null && jsonObject.get("url") != JsonValue.NULL) {
            this.url = jsonObject.getString("url");
        }
        if (jsonObject.get("description") != null && jsonObject.get("description") != JsonValue.NULL) {
            this.description = jsonObject.getString("description");
        }
        this.isProtected = jsonObject.getBoolean("isProtected");
        this.verified = jsonObject.getBoolean("verified");
        this.followers_count = jsonObject.getInt("followers_count");
        this.friends_count = jsonObject.getInt("friends_count");
        this.listed_count = jsonObject.getInt("listed_count");
        this.favourites_count = jsonObject.getInt("favourites_count");
        this.statuses_count = jsonObject.getInt("statuses_count");
        if (jsonObject.get("created_at") != null && jsonObject.get("created_at") != JsonValue.NULL) {
            this.created_at = jsonObject.getString("created_at");
        }
        if (jsonObject.get("profile_banner_url") != null && jsonObject.get("profile_banner_url") != JsonValue.NULL) {
            this.profile_banner_url = jsonObject.getString("profile_banner_url");
        }
        if (jsonObject.get("profile_image_url_https") != null && jsonObject.get("profile_image_url_https") != JsonValue.NULL) {
            this.profile_image_url_https = jsonObject.getString("profile_image_url_https");
        }
        this.default_profile = jsonObject.getBoolean("default_profile");

        if (jsonObject.getJsonArray("withheld_in_countries") != null) {
            JsonArray jsonWithheld_in_countriesArray = jsonObject.getJsonArray("withheld_in_countries");
            for (int i = 0; i < jsonWithheld_in_countriesArray.size(); i++) {
                this.withheld_in_countries.add(jsonWithheld_in_countriesArray.getString(i));
            }
        }
        if (jsonObject.get("withheld_scope") != null && jsonObject.get("withheld_scope") != JsonValue.NULL) {
            this.withheld_scope = jsonObject.getString("withheld_scope");
        }

        if (jsonObject.getJsonArray("descriptionURLEntities") != null) {
            JsonArray jsonDescriptionURLEntitiesArray = jsonObject.getJsonArray("descriptionURLEntities");
            for (int i = 0; i < jsonDescriptionURLEntitiesArray.size(); i++) {
                JsonObject urlEntityJsonObject = jsonDescriptionURLEntitiesArray.getJsonObject(i);
                this.descriptionURLEntities.add(new URLEntity().readJSONURLEntity(urlEntityJsonObject));
            }
        }
        this.geo_enabled = jsonObject.getBoolean("geo_enabled");
        if (jsonObject.get("lang") != null && jsonObject.get("lang") != JsonValue.NULL) {
            this.lang = jsonObject.getString("lang");
        }
        this.contributors_enabled = jsonObject.getBoolean("contributors_enabled");
        this.geo_enabled = jsonObject.getBoolean("geo_enabled");

        if (jsonObject.get("profile_background_color") != null && jsonObject.get("profile_background_color") != JsonValue.NULL) {
            this.profile_background_color = jsonObject.getString("profile_background_color");
        }

        if (jsonObject.get("profile_background_image_url") != null && jsonObject.get("profile_background_image_url") != JsonValue.NULL) {
            this.profile_background_image_url = jsonObject.getString("profile_background_image_url");
        }

        if (jsonObject.get("profile_background_image_url_https") != null && jsonObject.get("profile_background_image_url_https") != JsonValue.NULL) {
            this.profile_background_image_url_https = jsonObject.getString("profile_background_image_url_https");
        }
        this.profile_background_tile = jsonObject.getBoolean("profile_background_tile");

        if (jsonObject.get("profile_image_url") != null && jsonObject.get("profile_image_url") != JsonValue.NULL) {
            this.profile_image_url = jsonObject.getString("profile_image_url");
        }
        if (jsonObject.get("profile_link_color") != null && jsonObject.get("profile_link_color") != JsonValue.NULL) {
            this.profile_link_color = jsonObject.getString("profile_link_color");
        }
        if (jsonObject.get("profile_sidebar_border_color") != null && jsonObject.get("profile_sidebar_border_color") != JsonValue.NULL) {
            this.profile_sidebar_border_color = jsonObject.getString("profile_sidebar_border_color");
        }
        if (jsonObject.get("profile_sidebar_fill_color") != null && jsonObject.get("profile_sidebar_fill_color") != JsonValue.NULL) {
            this.profile_sidebar_fill_color = jsonObject.getString("profile_sidebar_fill_color");
        }
        if (jsonObject.get("profile_text_color") != null && jsonObject.get("profile_text_color") != JsonValue.NULL) {
            this.profile_text_color = jsonObject.getString("profile_text_color");
        }
        this.profile_use_background_image = jsonObject.getBoolean("profile_use_background_image");
        this.utc_offset = jsonObject.getInt("utc_offset");

        if (jsonObject.get("time_zone") != null && jsonObject.get("time_zone") != JsonValue.NULL) {
            this.time_zone = jsonObject.getString("time_zone");
        }
        this.is_translator = jsonObject.getBoolean("is_translator");
        this.follow_request_sent = jsonObject.getBoolean("follow_request_sent");
        this.showAllInlineMedia = jsonObject.getBoolean("showAllInlineMedia");

        return this;
    }

    public byte[] bsonSerialization() {
        BasicOutputBuffer outputBuffer = new BasicOutputBuffer();
        BsonBinaryWriter writer = new BsonBinaryWriter(outputBuffer);

        writer.writeStartDocument();
        writer.writeInt64("id", this.id);
        writer.writeString("name", this.name);
        writer.writeString("screen_name", this.screen_name);

        if (this.location != null)
            writer.writeString("location", this.location);

        if (this.url != null)
            writer.writeString("url", this.url);

        if (this.description != null)
            writer.writeString("description", this.description);

        writer.writeBoolean("isProtected", this.isProtected);
        writer.writeBoolean("verified", this.verified);
        writer.writeInt32("followers_count", this.followers_count);
        writer.writeInt32("friends_count", this.friends_count);
        writer.writeInt32("listed_count", this.listed_count);
        writer.writeInt32("favourites_count", this.favourites_count);
        writer.writeInt32("statuses_count", this.statuses_count);
        writer.writeString("created_at", this.created_at);

        if (this.profile_banner_url != null)
            writer.writeString("profile_banner_url", this.profile_banner_url);

        if (this.profile_image_url_https != null)
            writer.writeString("profile_image_url_https", this.profile_image_url_https);
        writer.writeBoolean("default_profile", this.default_profile);

        writer.writeInt32("withheld_in_countries_size", this.withheld_in_countries.size());
        writer.writeName("withheld_in_countries");
        writer.writeStartArray();
        for (String s : this.withheld_in_countries) {
            writer.writeString(s);
        }
        writer.writeEndArray();

        if (this.withheld_scope != null)
            writer.writeString("withheld_scope", this.withheld_scope);

        writer.writeInt32("descriptionURLEntities_size", this.descriptionURLEntities.size());
        writer.writeName("descriptionURLEntities");
        writer.writeStartArray();
        for (URLEntity urlEntity : this.descriptionURLEntities) {
            writer.writeBinaryData(new BsonBinary(urlEntity.bsonSerialization()));
        }
        writer.writeEndArray();

        writer.writeBoolean("geo_enabled", this.geo_enabled);

        if (this.lang != null)
            writer.writeString("lang", this.lang);

        writer.writeBoolean("contributors_enabled", this.contributors_enabled);

        if (this.profile_background_color != null)
            writer.writeString("profile_background_color", this.profile_background_color);

        if (this.profile_background_image_url != null)
            writer.writeString("profile_background_image_url", this.profile_background_image_url);

        if (this.profile_background_image_url_https != null)
            writer.writeString("profile_background_image_url_https", this.profile_background_image_url_https);

        writer.writeBoolean("profile_background_tile", this.profile_background_tile);

        if (this.profile_image_url != null)
            writer.writeString("profile_image_url", this.profile_image_url);

        if (this.profile_link_color != null)
            writer.writeString("profile_link_color", this.profile_link_color);

        if (this.profile_sidebar_border_color != null)
            writer.writeString("profile_sidebar_border_color", this.profile_sidebar_border_color);

        if (this.profile_sidebar_fill_color != null)
            writer.writeString("profile_sidebar_fill_color", this.profile_sidebar_fill_color);

        if (this.profile_text_color != null)
            writer.writeString("profile_text_color", this.profile_text_color);

        writer.writeBoolean("profile_use_background_image", this.profile_use_background_image);

        writer.writeInt32("utc_offset", this.utc_offset);

        if (this.time_zone != null)
            writer.writeString("time_zone", this.time_zone);

        writer.writeBoolean("is_translator", this.is_translator);
        writer.writeBoolean("follow_request_sent", this.follow_request_sent);
        writer.writeBoolean("showAllInlineMedia", this.showAllInlineMedia);


        writer.writeEndDocument();

        return outputBuffer.toByteArray();

    }

    public RootData bsonDeSerialization(byte[] buffData) {
        ByteBuffer buf = ByteBuffer.wrap(buffData);
        BsonBinaryReader reader = new BsonBinaryReader(buf);

        reader.readStartDocument();
        this.id = reader.readInt64("id");
        this.name = reader.readString("name");
        this.screen_name = reader.readString("screen_name");

        String currentName = reader.readName();
        if (currentName.equals("location")) {
            this.location = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("url")) {
            this.url = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("description")) {
            this.description = reader.readString();
            reader.readName();
        }

        this.isProtected = reader.readBoolean();
        this.verified = reader.readBoolean("verified");
        this.followers_count = reader.readInt32("followers_count");
        this.friends_count = reader.readInt32("friends_count");
        this.listed_count = reader.readInt32("listed_count");
        this.favourites_count = reader.readInt32("favourites_count");
        this.statuses_count = reader.readInt32("statuses_count");
        this.created_at = reader.readString("created_at");

        currentName = reader.readName();
        if (currentName.equals("profile_banner_url")) {
            this.profile_banner_url = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("profile_image_url_https")) {
            this.profile_image_url_https = reader.readString();
            reader.readName();
        }
        this.default_profile = reader.readBoolean();

        int withheld_in_countries_size = reader.readInt32("withheld_in_countries_size");
        reader.readName("withheld_in_countries");
        reader.readStartArray();
        for (int i = 0; i < withheld_in_countries_size; i++) {
            this.withheld_in_countries.add(reader.readString());
        }
        reader.readEndArray();


        currentName = reader.readName();
        if (currentName.equals("withheld_scope")) {
            this.withheld_scope = reader.readString();
            reader.readName();
        }


        int descriptionURLEntities_size = reader.readInt32();
        reader.readName("descriptionURLEntities");
        reader.readStartArray();
        for (int i = 0; i < descriptionURLEntities_size; i++) {
            URLEntity urlEntity = new URLEntity();
            urlEntity.bsonDeSerialization(reader.readBinaryData().getData());
            this.descriptionURLEntities.add(urlEntity);
        }
        reader.readEndArray();

        this.geo_enabled = reader.readBoolean("geo_enabled");

        currentName = reader.readName();
        if (currentName.equals("lang")) {
            this.lang = reader.readString();
            reader.readName();
        }

        this.contributors_enabled = reader.readBoolean();

        currentName = reader.readName();
        if (currentName.equals("profile_background_color")) {
            this.profile_background_color = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("profile_background_image_url")) {
            this.profile_background_image_url = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("profile_background_image_url_https")) {
            this.profile_background_image_url_https = reader.readString();
            reader.readName();
        }
        this.profile_background_tile = reader.readBoolean();

        currentName = reader.readName();
        if (currentName.equals("profile_image_url")) {
            this.profile_image_url = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("profile_link_color")) {
            this.profile_link_color = reader.readString();
            currentName = reader.readName();
        }
        if (currentName.equals("profile_sidebar_border_color")) {
            this.profile_sidebar_border_color = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("profile_sidebar_fill_color")) {
            this.profile_sidebar_fill_color = reader.readString();
            currentName = reader.readName();
        }

        if (currentName.equals("profile_text_color")) {
            this.profile_text_color = reader.readString();
            reader.readName();
        }

        this.profile_use_background_image = reader.readBoolean();
        this.utc_offset = reader.readInt32("utc_offset");


        currentName = reader.readName();
        if (currentName.equals("time_zone")) {
            this.time_zone = reader.readString();
            reader.readName();
        }

        this.is_translator = reader.readBoolean();
        this.follow_request_sent = reader.readBoolean("follow_request_sent");
        this.showAllInlineMedia = reader.readBoolean("showAllInlineMedia");

        reader.readEndDocument();

        return this;
    }

    public int flatBuffersWriter(FlatBufferBuilder builder) {

        int nameBuilder = this.name != null ? builder.createString(this.name) : 0;
        int screen_nameBuilder = this.screen_name != null ? builder.createString(this.screen_name) : 0;
        int locationBuilder = this.location != null ? builder.createString(this.location) : 0;
        int urlBuilder = this.url != null ? builder.createString(this.url) : 0;
        int descriptionBuilder = this.description != null ? builder.createString(this.description) : 0;
        int created_atBuilder = this.created_at != null ? builder.createString(this.created_at) : 0;
        int profile_banner_urlBuilder = this.profile_banner_url != null ? builder.createString(this.profile_banner_url) : 0;
        int profile_image_url_httpsBuilder = this.profile_image_url_https != null ? builder.createString(this.profile_image_url_https) : 0;
        int withheld_scopeBuilder = this.withheld_scope != null ? builder.createString(this.withheld_scope) : 0;
        int langBuilder = this.lang != null ? builder.createString(this.lang) : 0;
        int profile_background_colorBuilder = this.profile_background_color != null ? builder.createString(this.profile_background_color) : 0;
        int profile_background_image_urlBuilder = this.profile_background_image_url != null ? builder.createString(this.profile_background_image_url) : 0;
        int profile_background_image_url_httpsBuilder = this.profile_background_image_url_https != null ? builder.createString(this.profile_background_image_url_https) : 0;
        int profile_image_urlBuilder = this.profile_image_url != null ? builder.createString(this.profile_image_url) : 0;
        int profile_link_colorBuilder = this.profile_link_color != null ? builder.createString(this.profile_link_color) : 0;
        int profile_sidebar_border_colorBuilder = this.profile_sidebar_border_color != null ? builder.createString(this.profile_sidebar_border_color) : 0;
        int profile_sidebar_fill_colorBuilder = this.profile_sidebar_fill_color != null ? builder.createString(this.profile_sidebar_fill_color) : 0;
        int profile_text_colorBuilder = this.profile_text_color != null ? builder.createString(this.profile_text_color) : 0;
        int time_zoneBuilder = this.time_zone != null ? builder.createString(this.time_zone) : 0;

        int[] withheld_in_countriesList = new int[this.withheld_in_countries.size()];
        int i = 0;
        for (String s : this.withheld_in_countries) {
            int item = builder.createString(s);
            withheld_in_countriesList[i] = item;
            i++;
        }
        int withheld_in_countriesBuilder = UserFBS.createWithheldInCountriesVector(builder, withheld_in_countriesList);

        int[] descriptionURLEntitiesList=new int[this.descriptionURLEntities.size()];
        i=0;
        for (URLEntity urlEntity : this.descriptionURLEntities) {
            descriptionURLEntitiesList[i]=urlEntity.flatBuffersWriter(builder);
            i++;
        }
        int descriptionURLEntitiesBuilder = UserFBS.createDescriptionURLEntitiesVector(builder, descriptionURLEntitiesList);


        UserFBS.startUserFBS(builder);
        UserFBS.addId(builder, this.id);
        UserFBS.addName(builder, nameBuilder);
        UserFBS.addScreenName(builder, screen_nameBuilder);
        UserFBS.addLocation(builder, locationBuilder);
        UserFBS.addUrl(builder, urlBuilder);
        UserFBS.addDescription(builder, descriptionBuilder);
        UserFBS.addIsProtected(builder, this.isProtected);
        UserFBS.addVerified(builder, this.verified);
        UserFBS.addFollowersCount(builder, this.followers_count);
        UserFBS.addFriendsCount(builder, this.friends_count);
        UserFBS.addListedCount(builder, this.listed_count);
        UserFBS.addFavouritesCount(builder, this.favourites_count);
        UserFBS.addStatusesCount(builder, this.statuses_count);

        UserFBS.addCreatedAt(builder, created_atBuilder);
        UserFBS.addProfileBannerUrl(builder, profile_banner_urlBuilder);
        UserFBS.addProfileImageUrlHttps(builder, profile_image_url_httpsBuilder);
        UserFBS.addDefaultProfile(builder, this.default_profile);
        UserFBS.addWithheldInCountries(builder, withheld_in_countriesBuilder);
        UserFBS.addWithheldScope(builder, withheld_scopeBuilder);
        UserFBS.addDescriptionURLEntities(builder,descriptionURLEntitiesBuilder);
        UserFBS.addGeoEnabled(builder,this.geo_enabled);
        UserFBS.addLang(builder,langBuilder);
        UserFBS.addContributorsEnabled(builder,contributors_enabled);
        UserFBS.addProfileBackgroundColor(builder,profile_background_colorBuilder);
        UserFBS.addProfileBackgroundImageUrl(builder,profile_background_image_urlBuilder);
        UserFBS.addProfileBackgroundImageUrlHttps(builder,profile_background_image_url_httpsBuilder);
        UserFBS.addProfileBackgroundTile(builder,this.profile_background_tile);
        UserFBS.addProfileImageUrl(builder,profile_image_urlBuilder);
        UserFBS.addProfileLinkColor(builder,profile_link_colorBuilder);
        UserFBS.addProfileSidebarBorderColor(builder,profile_sidebar_border_colorBuilder);
        UserFBS.addProfileSidebarFillColor(builder,profile_sidebar_fill_colorBuilder);
        UserFBS.addProfileTextColor(builder,profile_text_colorBuilder);
        UserFBS.addProfileUseBackgroundImage(builder,this.profile_use_background_image);
        UserFBS.addDefaultProfile(builder,this.default_profile);
        UserFBS.addUtcOffset(builder,this.utc_offset);
        UserFBS.addTimeZone(builder,time_zoneBuilder);
        UserFBS.addIsTranslator(builder,this.is_translator);
        UserFBS.addFollowRequestSent(builder,this.follow_request_sent);
        UserFBS.addShowAllInlineMedia(builder,this.showAllInlineMedia);

        int orc = UserFBS.endUserFBS(builder);
        return orc;
    }
}