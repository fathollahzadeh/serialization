package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;

public class DataLoadToMemorySingle {

	public static void main(String[] args){

		String inDataPath = System.getProperty("inDataPath");
		int nrow = Integer.parseInt(System.getProperty("nrow"));

		ObjectReader reader = new ObjectReader(inDataPath, "Kryo");
		int batch = 100;
		for (int i=0; i<nrow;){
			reader.readObjects(i, batch);
			i += batch;
		}
	}
}
