package at.tugraz.objects.tpch;

//create raw table region (
//    r_regionkey       integer not null ,
//    r_name            char(25) not null ,
//    r_comment         varchar(152));

public class Region{
	private Integer regionKey;
	private String name;
	private String comment;

	public Region(Integer regionKey, String name, String comment) {
		this.regionKey = regionKey;
		this.name = name;
		this.comment = comment;
	}
}
