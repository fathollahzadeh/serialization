package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.util.Const;
import at.tugraz.util.RootData;

import java.io.IOException;

public class DataWriteSingle {

	public static void main(String[] args) throws IOException {

		String inDataPath = System.getProperty("inDataPath");
		String outDataPath = System.getProperty("outDataPath");
		String method = System.getProperty("method");
		int nrow = Integer.parseInt(System.getProperty("nrow"));

		ObjectReader reader = new ObjectReader(inDataPath, "Kryo");
		ObjectWriter writer = new ObjectWriter(outDataPath, method, nrow);

		int size = Const.BATCHSIZE;
		for (int i=0; i<nrow;){
			RootData[] rd = reader.readObjects(i, size);
			writer.writeObjectToFile(rd);
			i += rd.length;
			size = Math.min(nrow - i +1 , Const.BATCHSIZE);
		}
		writer.flush();

	}
}
