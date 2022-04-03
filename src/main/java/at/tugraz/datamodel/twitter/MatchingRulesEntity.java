package at.tugraz.datamodel.twitter;

import at.tugraz.util.RootObject;

public class MatchingRulesEntity extends RootObject {
	private String tag;
	private long id;
	private String id_str;

	public String getTag() {
		return tag;
	}

	public void setTag(String tag) {
		this.tag = tag;
	}

	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public String getId_str() {
		return id_str;
	}

	public void setId_str(String id_str) {
		this.id_str = id_str;
	}
}
