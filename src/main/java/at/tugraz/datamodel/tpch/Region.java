package at.tugraz.datamodel.tpch;

//create raw table region (
//    r_regionkey       integer not null ,
//    r_name            char(25) not null ,
//    r_comment         varchar(152));

public class Region {
	private Integer regionKey;
	private String name;
	private String comment;

	public Region(Integer regionKey, String name, String comment) {
		this.regionKey = regionKey;
		this.name = name;
		this.comment = comment;
	}

	public Integer getRegionKey() {
		return regionKey;
	}

	public void setRegionKey(Integer regionKey) {
		this.regionKey = regionKey;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getComment() {
		return comment;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}
}
