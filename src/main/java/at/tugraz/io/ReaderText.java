package at.tugraz.io;

import at.tugraz.util.RootObject;

import java.util.ArrayList;

public abstract class ReaderText {
	protected String fileName;
	protected ArrayList<RootObject> objects;

	public ReaderText(String fileName) {
		this.fileName = fileName;
		this.objects = new ArrayList<>();
	}

	public abstract ArrayList<RootObject> getObjects();
}
