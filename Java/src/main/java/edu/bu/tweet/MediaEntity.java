package edu.bu.tweet;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;

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
import javax.json.JsonValue;
import javax.json.JsonReader;
import javax.json.JsonWriter;
import javax.json.JsonWriterFactory;
import javax.json.stream.JsonGenerator;

import org.apache.log4j.Logger;


public class MediaEntity extends Base implements RootData {

    private static final long serialVersionUID = 6676093799500575284L;
    static Logger logger = Logger.getLogger(MediaEntity.class);

    private String display_url;
    private String expanded_url;
    private long id;
    private List<Integer> indices;
    private String media_url;
    private String media_url_https;
    private MediaSizesEntity sizes;
    private String type;
    private long source_status_id;
    private String source_status_id_str;
    private String url;
    private VideoEntity video_info;
    private AdditionalMediaInfoEntity additional_media_info;

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

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public List<Integer> getIndices() {
        return indices;
    }

    public void setIndices(List<Integer> indices) {
        this.indices = indices;
    }

    public String getMedia_url() {
        return media_url;
    }

    public void setMedia_url(String media_url) {
        this.media_url = media_url;
    }

    public String getMedia_url_https() {
        return media_url_https;
    }

    public void setMedia_url_https(String media_url_https) {
        this.media_url_https = media_url_https;
    }

    public MediaSizesEntity getSizes() {
        return sizes;
    }

    public void setSizes(MediaSizesEntity sizes) {
        this.sizes = sizes;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public long getSource_status_id() {
        return source_status_id;
    }

    public void setSource_status_id(long source_status_id) {
        this.source_status_id = source_status_id;
    }

    public String getSource_status_id_str() {
        return source_status_id_str;
    }

    public void setSource_status_id_str(String source_status_id_str) {
        this.source_status_id_str = source_status_id_str;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public VideoEntity getVideo_info() {
        return video_info;
    }

    public void setVideo_info(VideoEntity video_info) {
        this.video_info = video_info;
    }

    public AdditionalMediaInfoEntity getAdditional_media_info() {
        return additional_media_info;
    }

    public void setAdditional_media_info(AdditionalMediaInfoEntity additional_media_info) {
        this.additional_media_info = additional_media_info;
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