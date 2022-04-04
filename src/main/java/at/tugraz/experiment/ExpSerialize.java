package at.tugraz.experiment;

import at.tugraz.io.ReaderText;
import at.tugraz.io.ReaderTextCSVIMDB;
import at.tugraz.io.ReaderTextCSVTPCH;
import at.tugraz.io.ReaderTextJSONTweet;
import at.tugraz.io.Serializer;
import at.tugraz.io.SerializerGson;
import at.tugraz.io.SerializerJavaDefault;
import at.tugraz.io.SerializerKeryo;
import at.tugraz.util.RootObject;

import java.util.ArrayList;

public class ExpSerialize {

	public static void main(String[] args) {

		String inputFile;
		String method;
		String outputFile;
		String datasetName;

		try {
			inputFile = System.getProperty("inputFile");
			method = System.getProperty("method");
			outputFile = System.getProperty("outputFile");
			datasetName = System.getProperty("datasetName");
		}
		catch(Exception exception) {
			throw new RuntimeException("Wrong data for arguments!!!");
		}

		Serializer serializer;
		switch(method.toUpperCase()) {
			case "JAVADEFAULT":
				serializer = new SerializerJavaDefault(outputFile);
				break;
			case "KRYO":
				serializer = new SerializerKeryo(outputFile);
				break;
			case "GSON":
				serializer = new SerializerGson(outputFile);
				break;

			default:
				throw new RuntimeException("Serialization method:" + method + " doesn't support!!");
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

		for(RootObject object : objects)
			serializer.writeToFile(object);
		serializer.flush();
	}
}
