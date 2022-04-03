package at.tugraz.datamodel.twitter;

import at.tugraz.util.RootObject;

public class VariantEntity extends RootObject {

	private long bitrate;
	private String content_type;
	private String url;

	public long getBitrate() {
		return bitrate;
	}

	public void setBitrate(long bitrate) {
		this.bitrate = bitrate;
	}

	public String getContent_type() {
		return content_type;
	}

	public void setContent_type(String content_type) {
		this.content_type = content_type;
	}

	public String getUrl() {
		return url;
	}

	public void setUrl(String url) {
		this.url = url;
	}
}

