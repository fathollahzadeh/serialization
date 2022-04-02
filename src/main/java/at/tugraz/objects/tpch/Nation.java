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

}
