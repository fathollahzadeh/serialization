package at.tugraz.objects.tpch;

//CREATE TABLE PART  (
//        P_PARTKEY     INTEGER NOT NULL,
//        P_NAME        VARCHAR(55) NOT NULL,
//        P_MFGR        CHAR(25) NOT NULL,
//        P_BRAND       CHAR(10) NOT NULL,
//        P_TYPE        VARCHAR(25) NOT NULL,
//        P_SIZE        INTEGER NOT NULL,
//        P_CONTAINER   CHAR(10) NOT NULL,
//        P_RETAILPRICE DECIMAL(15,2) NOT NULL,
//        P_COMMENT     VARCHAR(23) NOT NULL );

public class Part{

	private Integer partKey;
	private String name;
	private String mfgr;
	private String brand;
	private String type;
	private Integer size;
	private String container;
	private Double retailPrice;
	private String comment;

	public Part(Integer partKey, String name, String mfgr, String brand, String type, Integer size, String container,
		Double retailPrice, String comment) {
		this.partKey = partKey;
		this.name = name;
		this.mfgr = mfgr;
		this.brand = brand;
		this.type = type;
		this.size = size;
		this.container = container;
		this.retailPrice = retailPrice;
		this.comment = comment;
	}

	public Integer getPartKey() {
		return partKey;
	}

	public void setPartKey(Integer partKey) {
		this.partKey = partKey;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getMfgr() {
		return mfgr;
	}

	public void setMfgr(String mfgr) {
		this.mfgr = mfgr;
	}

	public String getBrand() {
		return brand;
	}

	public void setBrand(String brand) {
		this.brand = brand;
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public Integer getSize() {
		return size;
	}

	public void setSize(Integer size) {
		this.size = size;
	}

	public String getContainer() {
		return container;
	}

	public void setContainer(String container) {
		this.container = container;
	}

	public Double getRetailPrice() {
		return retailPrice;
	}

	public void setRetailPrice(Double retailPrice) {
		this.retailPrice = retailPrice;
	}

	public String getComment() {
		return comment;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}
}
