package at.tugraz.objects.tpch;

import at.tugraz.util.RootData;

// CREATE TABLE LINEITEM(
//      L_ORDERKEY          int NOT NULL,
//      L_PARTKEY           int NOT NULL,
//      L_SUPPKEY           int NOT NULL,
//      L_LINENUMBER        int NOT NULL,
//      L_QUANTITY          decimal(15, 2) NOT NULL,
//      L_EXTENDEDPRICE     decimal(15, 2) NOT NULL,
//      L_DISCOUNT          decimal(15, 2) NOT NULL,
//      L_TAX               decimal(15, 2) NOT NULL,
//      L_RETURNFLAG        char(1) NOT NULL,
//      L_LINESTATUS        char(1) NOT NULL,
//      L_SHIPDATE          date NOT NULL,
//      L_COMMITDATE        date NOT NULL,
//      L_RECEIPTDATE       date NOT NULL,
//      L_SHIPINSTRUCT      char(25) NOT NULL,
//      L_SHIPMODE          char(10) NOT NULL,
//      L_COMMENT           varchar(44) NOT NULL );

public class LineItem{

//	private Supplier supplier;
//	private Part part;
	private PartSupp partSupp;
	private Integer lineNumber;
	private Double quantity;
	private Double extendedPrice;
	private Double discount;
	private Double tax;
	private String returnFlag;
	private String lineStatus;
	private String shipDate;
	private String commitDate;
	private String receiptDate;
	private String shipInstruct;
	private String shipMode;
	private String comment;
	private Order order;

	public LineItem(Order order, PartSupp partSupp, Integer lineNumber, Double quantity,
		Double extendedPrice, Double discount, Double tax, String returnFlag, String lineStatus, String shipDate,
		String commitDate, String receiptDate, String shipInstruct, String shipMode, String comment) {
		this.order = order;
		this.partSupp = partSupp;
		this.lineNumber = lineNumber;
		this.quantity = quantity;
		this.extendedPrice = extendedPrice;
		this.discount = discount;
		this.tax = tax;
		this.returnFlag = returnFlag;
		this.lineStatus = lineStatus;
		this.shipDate = shipDate;
		this.commitDate = commitDate;
		this.receiptDate = receiptDate;
		this.shipInstruct = shipInstruct;
		this.shipMode = shipMode;
		this.comment = comment;
	}

	public PartSupp getPartSupp() {
		return partSupp;
	}

	public void setPartSupp(PartSupp partSupp) {
		this.partSupp = partSupp;
	}

	public Integer getLineNumber() {
		return lineNumber;
	}

	public void setLineNumber(Integer lineNumber) {
		this.lineNumber = lineNumber;
	}

	public Double getQuantity() {
		return quantity;
	}

	public void setQuantity(Double quantity) {
		this.quantity = quantity;
	}

	public Double getExtendedPrice() {
		return extendedPrice;
	}

	public void setExtendedPrice(Double extendedPrice) {
		this.extendedPrice = extendedPrice;
	}

	public Double getDiscount() {
		return discount;
	}

	public void setDiscount(Double discount) {
		this.discount = discount;
	}

	public Double getTax() {
		return tax;
	}

	public void setTax(Double tax) {
		this.tax = tax;
	}

	public String getReturnFlag() {
		return returnFlag;
	}

	public void setReturnFlag(String returnFlag) {
		this.returnFlag = returnFlag;
	}

	public String getLineStatus() {
		return lineStatus;
	}

	public void setLineStatus(String lineStatus) {
		this.lineStatus = lineStatus;
	}

	public String getShipDate() {
		return shipDate;
	}

	public void setShipDate(String shipDate) {
		this.shipDate = shipDate;
	}

	public String getCommitDate() {
		return commitDate;
	}

	public void setCommitDate(String commitDate) {
		this.commitDate = commitDate;
	}

	public String getReceiptDate() {
		return receiptDate;
	}

	public void setReceiptDate(String receiptDate) {
		this.receiptDate = receiptDate;
	}

	public String getShipInstruct() {
		return shipInstruct;
	}

	public void setShipInstruct(String shipInstruct) {
		this.shipInstruct = shipInstruct;
	}

	public String getShipMode() {
		return shipMode;
	}

	public void setShipMode(String shipMode) {
		this.shipMode = shipMode;
	}

	public String getComment() {
		return comment;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}

	public Order getOrder() {
		return order;
	}

	public void setOrder(Order order) {
		this.order = order;
	}
}
