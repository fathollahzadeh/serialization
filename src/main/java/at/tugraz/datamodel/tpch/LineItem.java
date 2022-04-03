package at.tugraz.datamodel.tpch;

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

public class LineItem {

	private int orderKey;
	private Supplier supplier;
	private Part part;
	private int lineNumber;
	private double quantity;
	private double extendedPrice;
	private double discount;
	private double tax;
	private String returnFlag;
	private String lineStatus;
	private String shipDate;
	private String commitDate;
	private String receiptDate;
	private String shipInstruct;
	private String shipMode;
	private String comment;

	public LineItem(int orderKey, Supplier suppliers, Part parts, int lineNumber, double quantity, double extendedPrice, double discount, double tax, String returnFlag, String lineStatus,
		String shipDate, String commitDate, String receiptDate, String shipInstruct, String shipMode, String comment) {
		this.orderKey = orderKey;
		this.supplier = suppliers;
		this.part = parts;
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

	public int getOrderKey() {
		return orderKey;
	}

	public void setOrderKey(int orderKey) {
		this.orderKey = orderKey;
	}

	public Supplier getSupplier() {
		return supplier;
	}

	public void setSupplier(Supplier supplier) {
		this.supplier = supplier;
	}

	public Part getPart() {
		return part;
	}

	public void setPart(Part part) {
		this.part = part;
	}

	public int getLineNumber() {
		return lineNumber;
	}

	public void setLineNumber(int lineNumber) {
		this.lineNumber = lineNumber;
	}

	public double getQuantity() {
		return quantity;
	}

	public void setQuantity(double quantity) {
		this.quantity = quantity;
	}

	public double getExtendedPrice() {
		return extendedPrice;
	}

	public void setExtendedPrice(double extendedPrice) {
		this.extendedPrice = extendedPrice;
	}

	public double getDiscount() {
		return discount;
	}

	public void setDiscount(double discount) {
		this.discount = discount;
	}

	public double getTax() {
		return tax;
	}

	public void setTax(double tax) {
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
}
