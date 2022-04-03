package at.tugraz.objects.tpch;

//create raw table nation (
//    n_nationkey   integer not null ,
//    n_name        char(25) not null ,
//    n_regionkey   integer not null ,
//    n_comment     varchar(152));
public class Nation {

	private Integer nationKey;
	private String name;
	private Region region;
	private String comment;

	public Nation(Integer nationKey, String name, Region region, String comment) {
		this.nationKey = nationKey;
		this.name = name;
		this.region = region;
		this.comment = comment;
	}

	public Integer getNationKey() {
		return nationKey;
	}

	public void setNationKey(Integer nationKey) {
		this.nationKey = nationKey;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public Region getRegion() {
		return region;
	}

	public void setRegion(Region region) {
		this.region = region;
	}

	public String getComment() {
		return comment;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}
}
