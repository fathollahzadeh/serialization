package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.ObjectFileIndex;
import at.tugraz.util.OptimizerUtils;
import at.tugraz.util.RootData;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.PriorityQueue;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

public class ExternalSortParallel {

	private static Logger logger = Logger.getLogger(ExternalSortParallel.class);

	public static void main(String[] args) throws IOException, InterruptedException, ExecutionException {

		String inDataPath = "/home/saeed/Documents/Github/serialization/Experiments/data/tweets.jbin";//System.getProperty("inDataPath");
		String outDataPath = "";//System.getProperty("outDataPath");
		String method = "Kryo";//System.getProperty("method");
		int chunkSize = 100; //Integer.parseInt(System.getProperty("chunkSize"));

		ObjectReader reader = new ObjectReader(inDataPath, method);

		RootData[] rd = reader.readObjects(0, reader.getRlen());

		RootData[] rd2 = new RootData[1000000];
		int i = 0;
		do {
			for (int j=0; j< rd.length && i<1000000; j++) {
				rd2[i] = rd[j];
				i++;
			}
		}while (i<1000000);

		long startTime = System.currentTimeMillis();
		Arrays.parallelSort(rd2);
		long duration = System.currentTimeMillis() - startTime;
		System.out.println(duration);


//
//		int numThreads = OptimizerUtils.getParallelWriteParallelism();
//		ExecutorService pool = CommonThreadPool.get(numThreads);
//
//		ObjectReader reader = new ObjectReader(inDataPath, method);
//		int fileCount = (int) Math.ceil((double) reader.getRlen() / chunkSize);
//		int blklen = (int) Math.ceil((double) chunkSize / numThreads);
//
//		for (int i = 0; i < fileCount; i++) {
//			ArrayList<SortTask> sortTasks = new ArrayList<>();
//			for (int j=0; j< numThreads && (i*chunkSize+j*blklen) < reader.getRlen(); j++) {
//				ObjectReader taskReader = new ObjectReader(inDataPath, method);
//				sortTasks.add(new SortTask(taskReader, i*chunkSize+j*blklen , Math.min(i*chunkSize+(j+1)*blklen, reader.getRlen())));
//			}
//
//			//wait until all tasks have been executed
//			List<Future<ArrayList<RootData>>> rt = pool.invokeAll(sortTasks);
//			pool.shutdown();
//
//			//check for exceptions
//			for (Future<ArrayList<RootData>> f : rt) {
//				f.get();
//			}
//		}


	}

	private static class SortTask implements Callable<ArrayList<RootData>> {
		private final ObjectReader reader;
		protected final int beginPos;
		protected final int count;

		public SortTask(ObjectReader reader, int beginPos, int count) {
			this.reader = reader;
			this.beginPos = beginPos;
			this.count = count;
		}

		@Override
		public ArrayList<RootData> call() {
			ArrayList<RootData> list = new ArrayList<>();
			reader.readObjects(beginPos, count, list);
			Collections.sort(list);
			return list;
		}
	}
}
