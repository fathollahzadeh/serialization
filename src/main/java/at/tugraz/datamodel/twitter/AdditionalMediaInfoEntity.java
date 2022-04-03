package at.tugraz.datamodel.twitter;

import at.tugraz.util.RootObject;

public class AdditionalMediaInfoEntity extends RootObject {

	private String title;
	private String description;
	private boolean embeddable;
	private boolean monetizable;

	public AdditionalMediaInfoEntity() {
		this.embeddable = false;
		this.monetizable = false;
	}
}
