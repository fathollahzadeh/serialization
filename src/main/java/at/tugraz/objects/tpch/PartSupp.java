package at.tugraz.objects.tpch;

//create table TPCH.PARTSUPP
//(
//	PS_PARTKEY int not null,
//	PS_SUPPKEY int not null,
//	PS_AVAILQTY int null,
//	PS_SUPPLYCOST decimal(15,2) null,
//	PS_COMMENT varchar(199) null,
//	primary key (PS_PARTKEY, PS_SUPPKEY)
//);

public class PartSupp{
	private Part part;
	private Supplier supplier;
	private Integer availQty;
	private Double supplyCost;
	private String comment;

	public PartSupp(Part part, Supplier supplier, Integer availQty, Double supplyCost, String comment) {
		this.part = part;
		this.supplier = supplier;
		this.availQty = availQty;
		this.supplyCost = supplyCost;
		this.comment = comment;
	}

	public Part getPart() {
		return part;
	}

	public void setPart(Part part) {
		this.part = part;
	}

	public Supplier getSupplier() {
		return supplier;
	}

	public void setSupplier(Supplier supplier) {
		this.supplier = supplier;
	}

	public Integer getAvailQty() {
		return availQty;
	}

	public void setAvailQty(Integer availQty) {
		this.availQty = availQty;
	}

	public Double getSupplyCost() {
		return supplyCost;
	}

	public void setSupplyCost(Double supplyCost) {
		this.supplyCost = supplyCost;
	}

	public String getComment() {
		return comment;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}
}
