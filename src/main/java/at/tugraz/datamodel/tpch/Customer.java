package at.tugraz.datamodel.tpch;

import at.tugraz.util.RootObject;

import java.util.List;

public class Customer extends RootObject {
	private List<Order> orders;
	private int custkey;
	private String name;
	private String address;
	private Nation nation;
	private String phone;
	private double accbal;
	private String mktsegment;
	private String comment;
	
	public Customer(List<Order> orders, Nation nation, int custkey, String name, String address, String phone, double accbal, String mktsegment, String comment) {
		super();
		this.orders = orders;
		this.nation = nation;
		this.custkey = custkey;
		this.name = name;
		this.address = address;
		this.phone = phone;
		this.accbal = accbal;
		this.mktsegment = mktsegment;
		this.comment = comment;
	}

	public List<Order> getOrders() {
		return orders;
	}

	public void setOrders(List<Order> orders) {
		this.orders = orders;
	}

	public int getCustkey() {
		return custkey;
	}

	public void setCustkey(int custkey) {
		this.custkey = custkey;
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

	public double getAccbal() {
		return accbal;
	}

	public void setAccbal(double accbal) {
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
