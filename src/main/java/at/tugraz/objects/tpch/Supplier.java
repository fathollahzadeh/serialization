package at.tugraz.objects.tpch;

// CREATE TABLE SUPPLIER(
//      S_SUPPKEY       int NOT NULL,
//      S_NAME          char(25) NOT NULL,
//      S_ADDRESS       varchar(40) NOT NULL,
//      S_NATIONKEY     int NOT NULL,
//      S_PHONE         char(15) NOT NULL,
//      S_ACCTBAL       decimal(15, 2) NOT NULL,
//      S_COMMENT       varchar(101) NOT NULL );

import at.tugraz.util.RootData;

public class Supplier{
	private Integer supplierKey;
	private String name;
	private String address;
	private Nation nation;
	private String phone;
	private Double accbal;
	private String comment;

	public Supplier(Integer supplierKey, String name, String address, Nation nation, String phone, Double accbal,
		String comment) {
		this.supplierKey = supplierKey;
		this.name = name;
		this.address = address;
		this.nation = nation;
		this.phone = phone;
		this.accbal = accbal;
		this.comment = comment;
	}

	public Integer getSupplierKey() {
		return supplierKey;
	}

	public void setSupplierKey(Integer supplierKey) {
		this.supplierKey = supplierKey;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getAddress() {
		return address;
	}

	public void setAddress(String address) {
		this.address = address;
	}

	public Nation getNation() {
		return nation;
	}

	public void setNation(Nation nation) {
		this.nation = nation;
	}

	public String getPhone() {
		return phone;
	}

	public void setPhone(String phone) {
		this.phone = phone;
	}

	public Double getAccbal() {
		return accbal;
	}

	public void setAccbal(Double accbal) {
		this.accbal = accbal;
	}

	public String getComment() {
		return comment;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}
}
