package at.tugraz.objects.tpch;

import at.tugraz.util.RootObject;

import java.util.List;

public class Customer extends RootObject {

	public Customer(List<Order> orders,Nation nation, int custkey, String name, String address, String phone, double accbal, String mktsegment, String comment) {
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

	private List<Order> orders;
	private int custkey;
	private String name;
	private String address;
	private Nation nation;
	private String phone;
	private double accbal;
	private String mktsegment;
	private String comment;

}
