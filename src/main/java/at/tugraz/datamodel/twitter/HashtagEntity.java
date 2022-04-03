package at.tugraz.datamodel.twitter;

import java.util.List;
import at.tugraz.util.RootObject;

public class HashtagEntity extends RootObject {

	private List<Integer> indices;
	private String text;

	public List<Integer> getIndices() {
		return indices;
	}

	public void setIndices(List<Integer> indices) {
		this.indices = indices;
	}

	public String getText() {
		return text;
	}

	public void setText(String text) {
		this.text = text;
	}
}

