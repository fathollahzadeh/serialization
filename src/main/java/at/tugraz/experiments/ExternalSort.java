package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.util.ObjectFileIndex;
import at.tugraz.util.RootData;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;
import java.util.concurrent.ExecutionException;

public class ExternalSort {

	private static Logger logger = Logger.getLogger(ExternalSort.class);

	public static void main(String[] args) throws IOException, InterruptedException, ExecutionException {

		String inDataPath = System.getProperty("inDataPath");
		String outDataPath = System.getProperty("outDataPath");
		String method = System.getProperty("method");
		int chunkSize = Integer.parseInt(System.getProperty("chunkSize"));

		PriorityQueue<ObjectFileIndex> queue = new PriorityQueue<ObjectFileIndex>();
		ObjectReader reader = new ObjectReader(inDataPath, method);
		int fileCount = (int) Math.ceil((double) reader.getRlen() / chunkSize);
		long[] pageObjectCounter = new long[fileCount];
		long[] readFileObject = new long[fileCount];

		int[] pageCounter = new int[fileCount];
		// set all positions to the beginning of files - zero.
		for(int i = 0; i < fileCount; i++) {
			pageCounter[i] = 0;
		}

		for(int i = 0; i < fileCount && i * chunkSize < reader.getRlen(); i++) {
			RootData[] list = reader.readObjects((long) i * chunkSize, chunkSize);
			Arrays.sort(list);

			ObjectWriter writer = new ObjectWriter(outDataPath+"/"+method+"Java-sorted-"+i+".bin", method, list.length);
			writer.writeObjectToFile(list);
			writer.flush();
		}

		// open all of data files and keep them open to read partially.
		List<ObjectReader> readerArray = new ArrayList<>();
		for(int i = 0; i < fileCount; ++i) {
			String sortedFileName = outDataPath+"/"+method+"Java-sorted-"+i+".bin";
			ObjectReader tmpReader = new ObjectReader(sortedFileName, method);
			readerArray.add(tmpReader);
		}

		// reading objects from the first pages and adding them to a priority queue
		for (int i = 0; i < fileCount; i++) {
			int n = readerArray.get(i).getObjectInEachPage().get(0);
			RootData[] rd = readerArray.get(i).readObjects(0, n);
			pageObjectCounter[i] = n;
			readFileObject[i] = n;
			for (RootData rootData : rd) {
				ObjectFileIndex objectFileIndex = new ObjectFileIndex(i, rootData);
				queue.add(objectFileIndex);
			}
		}
		logger.info("Single-Thread External Sort: First page reading is done! ");
		ObjectWriter writer = new ObjectWriter(outDataPath+"/"+method+"Java-sorted.bin", method, reader.getRlen());

		while(!queue.isEmpty()) {
			ObjectFileIndex tmpObjectFileIndex = queue.remove();
			int fileNumber = tmpObjectFileIndex.getFileIndex();

			// reduce the number of objects read from that file.
			pageObjectCounter[fileNumber] = pageObjectCounter[fileNumber] - 1;

			// If needed load more objects from files.
			// if zero load the next page from file and add objects.
			if(pageObjectCounter[fileNumber] == 0 && pageCounter[fileNumber] < readerArray.get(fileNumber).getObjectInEachPage().size() - 1) {

				// add page counter
				pageCounter[fileNumber] = pageCounter[fileNumber] + 1;
				pageObjectCounter[fileNumber] = readerArray.get(fileNumber).getObjectInEachPage().get(pageCounter[fileNumber]);

				RootData[] rd = readerArray.get(fileNumber).readObjects(readFileObject[fileNumber], (int) pageObjectCounter[fileNumber]);
				readFileObject[fileNumber] += rd.length;

				for (RootData rootData : rd) {
					ObjectFileIndex objectFileIndex = new ObjectFileIndex(fileNumber, rootData);
					queue.add(objectFileIndex);
				}
			}
			writer.writeObjectToFile(tmpObjectFileIndex.getValue());
		}
		writer.flush();
	}
}
