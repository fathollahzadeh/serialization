package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.util.Const;
import at.tugraz.util.RootData;

import java.io.IOException;

public class DataSerializationSingle {

	public static void main(String[] args) throws IOException {

		String inDataPath = System.getProperty("inDataPath");
		String method = System.getProperty("method");
		int nrow = Integer.parseInt(System.getProperty("nrow"));

		ObjectReader reader = new ObjectReader(inDataPath, "Kryo");
		ObjectWriter writer = new ObjectWriter(method, nrow, Const.PAGESIZE);
		int size = Const.BATCHSIZE;
		for (long i=0; i<nrow;){
			RootData[] rd = reader.readObjects(i, size);
			writer.serializeObjects(rd);
			i += rd.length;
			size = (int) Math.min(nrow - i, Const.BATCHSIZE);
		}
	}
}
