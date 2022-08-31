package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;

public class ExternalSortIO {

	private static Logger logger = Logger.getLogger(ExternalSortIO.class);

	public static void main(String[] args) throws IOException, InterruptedException, ExecutionException {

		String inDataPath = System.getProperty("inDataPath");
		String outDataPath = System.getProperty("outDataPath");
		String method = System.getProperty("method");
		int chunkSize = Integer.parseInt(System.getProperty("chunkSize"));

		ObjectReader reader = new ObjectReader(inDataPath, method);
		int fileCount = (int) Math.ceil((double) reader.getRlen() / chunkSize);

		for(int i = 0; i < fileCount & i * chunkSize < reader.getRlen(); i++) {
			ArrayList<byte[]> listBytes = reader.readIO((long) i * chunkSize, chunkSize);
			ObjectWriter writer = new ObjectWriter(outDataPath+"/"+method+"Java-sorted-"+i+".bin", method, listBytes.size());
			writer.writeBufferToFile(listBytes);
			writer.flush();
		}

		// open all of data files and keep them open to read partially.
		List<ObjectReader> readerArray = new ArrayList<>();
		for(int i = 0; i < fileCount; ++i) {
			String sortedFileName = outDataPath+"/"+method+"Java-sorted-"+i+".bin";
			ObjectReader tmpReader = new ObjectReader(sortedFileName, method);
			readerArray.add(tmpReader);
		}

		ObjectWriter writer = new ObjectWriter(outDataPath+"/"+method+"Java-sorted.bin", method, reader.getRlen());
		// reading objects from the first pages and adding them to a priority queue
		for (int i = 0; i < fileCount; i++) {
			int n = readerArray.get(i).getRlen();
			ArrayList<byte[]> listBytes = readerArray.get(i).readIO(0, n);
			writer.writeBufferToFile(listBytes);
		}
		writer.flush();
		logger.info("Single-Thread External Sort: IO done! ");
	}
}
