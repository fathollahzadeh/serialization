package at.tugraz.datamodel.twitter;

import at.tugraz.util.RootObject;

public class OptionEntity extends RootObject {

	private int position;
	private String text;

	public int getPosition() {
		return position;
	}

	public void setPosition(int position) {
		this.position = position;
	}

	public String getText() {
		return text;
	}

	public void setText(String text) {
		this.text = text;
	}
}
