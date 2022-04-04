package at.tugraz.experiment;

import at.tugraz.io.ReaderText;
import at.tugraz.io.ReaderTextCSVIMDB;
import at.tugraz.io.ReaderTextCSVTPCH;
import at.tugraz.io.ReaderTextJSONTweet;
import at.tugraz.util.RootObject;

import java.util.ArrayList;

public class ExpSerializeLoadText {

	public static void main(String[] args) {

		String inputFile;
		String datasetName;

		try {
			inputFile = System.getProperty("inputFile");
			datasetName = System.getProperty("datasetName");
		}
		catch(Exception exception) {
			throw new RuntimeException("Wrong data for arguments!!!");
		}

		// load total dataset into memory
		ReaderText reader;
		ArrayList<RootObject> objects;
		switch(datasetName.toUpperCase()) {
			case "TWITTER":
				reader = new ReaderTextJSONTweet(inputFile);
				break;
			case "TPCH":
				reader = new ReaderTextCSVTPCH(inputFile);
				break;
			case "IMDB":
				reader = new ReaderTextCSVIMDB(inputFile);
				break;
			default:
				throw new RuntimeException("Dataset:" + datasetName + " doesn't support!!");
		}
		objects = reader.getObjects();
	}
}
