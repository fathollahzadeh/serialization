package at.tugraz.objects.tpch;

public class Customer{
	private Integer custKey;
	private String name;
	private String address;
	private Nation nation;
	private String phone;
	private Double accbal;
	private String mktsegment;
	private String comment;

	public Customer(Integer custKey, String name, String address, Nation nation, String phone,
		Double accbal, String mktsegment, String comment) {
		this.custKey = custKey;
		this.name = name;
		this.address = address;
		this.nation = nation;
		this.phone = phone;
		this.accbal = accbal;
		this.mktsegment = mktsegment;
		this.comment = comment;
	}

	public Integer getCustKey() {
		return custKey;
	}

	public void setCustKey(Integer custKey) {
		this.custKey = custKey;
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

	public String getMktsegment() {
		return mktsegment;
	}

	public void setMktsegment(String mktsegment) {
		this.mktsegment = mktsegment;
	}

	public String getComment() {
		return comment;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}
}
