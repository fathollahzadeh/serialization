package at.tugraz.experiments;

import at.tugraz.filehandler.FileHandler;
import at.tugraz.filehandler.LogFileHandler;
import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.tweet.TweetStatus;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.Const;
import at.tugraz.util.MachineInfo;
import at.tugraz.util.Network;
import at.tugraz.util.NodeType;
import at.tugraz.util.ObjectFileIndex;
import at.tugraz.util.RootData;
import org.apache.log4j.Logger;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.PriorityQueue;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

public class ExternalSortSingle {

	private static Logger logger = Logger.getLogger(ExternalSortSingle.class);

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

		for(int i = 0; i < fileCount & i * chunkSize < reader.getRlen(); i++) {
			ArrayList<RootData> list = new ArrayList<>();

			reader.readObjects((long) i * reader.getRlen(), chunkSize, list);
			Collections.sort(list);

			ObjectWriter writer = new ObjectWriter(outDataPath+"/"+method+"-sorted-"+i+".java", method, list.size());
			writer.writeObjectToFile(list);
			writer.flush();
		}

		// open all of data files and keep them open to read partially.
		List<ObjectReader> readerArray = new ArrayList<>();
		for(int i = 0; i < fileCount; ++i) {
			String sortedFileName = outDataPath+"/"+method+"-sorted-"+i+".java";
			ObjectReader tmpReader = new ObjectReader(sortedFileName, method);
			readerArray.add(tmpReader);
		}

		// reading objects from the first pages and adding them to a priority queue
		for (int i = 0; i < fileCount; i++) {
			int n = readerArray.get(i).getObjectInEachPage().get(0);
			RootData[] rd = reader.readObjects(0, n);
			pageObjectCounter[i] = n;
			readFileObject[i] = n;
			for(int j = 0; j < rd.length; ++j) {
				ObjectFileIndex objectFileIndex = new ObjectFileIndex(i, rd[j]);
				queue.add(objectFileIndex);
			}
		}
		logger.info("Single-Thread External Sort: First page reading is done! ");

		ObjectWriter writer = new ObjectWriter(outDataPath+"/"+method+"-sorted.java", method, reader.getRlen());

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

				for(int j = 0; j < rd.length; ++j) {
					ObjectFileIndex objectFileIndex = new ObjectFileIndex(fileNumber, rd[j]);
					queue.add(objectFileIndex);
				}
			}
			writer.writeObjectToFile(tmpObjectFileIndex.getValue());
		}
		writer.flush();
	}
}
