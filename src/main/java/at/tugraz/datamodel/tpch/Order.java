package at.tugraz.datamodel.tpch;

// CREATE TABLE ORDERS ( O_ORDERKEY INTEGER NOT NULL,
//      O_CUSTKEY           INTEGER NOT NULL,
//      O_ORDERSTATUS       CHAR(1) NOT NULL,
//      O_TOTALPRICE        DECIMAL(15,2) NOT NULL,
//      O_ORDERDATE         DATE NOT NULL,
//      O_ORDERPRIORITY     CHAR(15) NOT NULL,
//      O_CLERK             CHAR(15) NOT NULL,
//      O_SHIPPRIORITY      INTEGER NOT NULL,
//      O_COMMENT           VARCHAR(79) NOT NULL);

import java.util.List;

public class Order {

	private List<LineItem> lineItems;
	private Integer orderKey;
	private Integer custKey;
	private String orderStatus;
	private Double totalPrice;
	private String orderDate;
	private String orderPriority;
	private String clerk;
	private Integer shipPriority;
	private String comment;

	public Order(Integer orderKey, List<LineItem> lineItems, Integer custKey, String orderStatus, Double totalPrice, String orderDate, String orderPriority, String clerk, Integer shipPriority,
		String comment) {
		this.orderKey = orderKey;
		this.lineItems = lineItems;
		this.custKey = custKey;
		this.orderStatus = orderStatus;
		this.totalPrice = totalPrice;
		this.orderDate = orderDate;
		this.orderPriority = orderPriority;
		this.clerk = clerk;
		this.shipPriority = shipPriority;
		this.comment = comment;
	}

	public List<LineItem> getLineItems() {
		return lineItems;
	}

	public void setLineItems(List<LineItem> lineItems) {
		this.lineItems = lineItems;
	}

	public Integer getOrderKey() {
		return orderKey;
	}

	public void setOrderKey(Integer orderKey) {
		this.orderKey = orderKey;
	}

	public Integer getCustKey() {
		return custKey;
	}

	public void setCustKey(Integer custKey) {
		this.custKey = custKey;
	}

	public String getOrderStatus() {
		return orderStatus;
	}

	public void setOrderStatus(String orderStatus) {
		this.orderStatus = orderStatus;
	}

	public Double getTotalPrice() {
		return totalPrice;
	}

	public void setTotalPrice(Double totalPrice) {
		this.totalPrice = totalPrice;
	}

	public String getOrderDate() {
		return orderDate;
	}

	public void setOrderDate(String orderDate) {
		this.orderDate = orderDate;
	}

	public String getOrderPriority() {
		return orderPriority;
	}

	public void setOrderPriority(String orderPriority) {
		this.orderPriority = orderPriority;
	}

	public String getClerk() {
		return clerk;
	}

	public void setClerk(String clerk) {
		this.clerk = clerk;
	}

	public Integer getShipPriority() {
		return shipPriority;
	}

	public void setShipPriority(Integer shipPriority) {
		this.shipPriority = shipPriority;
	}

	public String getComment() {
		return comment;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}


}
