package at.tugraz.objects.tpch;

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

	public LineItem(int orderKey, Supplier suppliers, Part parts, int lineNumber, double quantity, double extendedPrice, double discount, double tax, String returnFlag, String lineStatus, String shipDate,
		String commitDate, String receiptDate, String shipInstruct, String shipMode, String comment) {
		super();
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
}
