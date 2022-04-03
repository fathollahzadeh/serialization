package at.tugraz.datamodel.twitter;

import at.tugraz.util.RootObject;

public class SizeEntity extends RootObject {

	private int width;
	private int height;
	private String resize;

	public int getWidth() {
		return width;
	}

	public void setWidth(int width) {
		this.width = width;
	}

	public int getHeight() {
		return height;
	}

	public void setHeight(int height) {
		this.height = height;
	}

	public String getResize() {
		return resize;
	}

	public void setResize(String resize) {
		this.resize = resize;
	}
}

