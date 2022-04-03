package at.tugraz.datamodel.twitter;

import at.tugraz.util.RootObject;

public class Place extends RootObject {

	private String name;
	private String country_code;
	private String id;
	private String country;
	private String place_type;
	private String url;
	private String full_name;
	private BoundingBoxCoordinate bounding_box;

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getCountry_code() {
		return country_code;
	}

	public void setCountry_code(String country_code) {
		this.country_code = country_code;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getCountry() {
		return country;
	}

	public void setCountry(String country) {
		this.country = country;
	}

	public String getPlace_type() {
		return place_type;
	}

	public void setPlace_type(String place_type) {
		this.place_type = place_type;
	}

	public String getUrl() {
		return url;
	}

	public void setUrl(String url) {
		this.url = url;
	}

	public String getFull_name() {
		return full_name;
	}

	public void setFull_name(String full_name) {
		this.full_name = full_name;
	}

	public BoundingBoxCoordinate getBounding_box() {
		return bounding_box;
	}

	public void setBounding_box(BoundingBoxCoordinate bounding_box) {
		this.bounding_box = bounding_box;
	}
}
