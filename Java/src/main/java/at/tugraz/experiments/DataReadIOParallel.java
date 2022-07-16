package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.Const;
import at.tugraz.util.OptimizerUtils;
import at.tugraz.util.RootData;
import com.google.gson.Gson;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

public class DataReadIOParallel {

    public static void main(String[] args) throws IOException, InterruptedException, ExecutionException {

        String inDataPath = System.getProperty("inDataPath");
        String method = System.getProperty("method");
        String seqRand = System.getProperty("seqRand");
        int nrow = Integer.parseInt(System.getProperty("nrow"));

        int numThreads = OptimizerUtils.getParallelWriteParallelism();
        ExecutorService pool = CommonThreadPool.get(numThreads);
        ArrayList<Task> tasks = new ArrayList<>();
        int blklen = (int) Math.ceil((double) nrow / numThreads);

        if (seqRand.equalsIgnoreCase("sequential")) {
            for (int i = 0; i < numThreads & i * blklen < nrow; i++) {
                ObjectReader reader = new ObjectReader(inDataPath, method);
                tasks.add(new ReadIOTask(reader, i * blklen, Math.min((i + 1) * blklen, nrow)));
            }
        }
        else {
            String randomDataPath = System.getProperty("randomDataPath");
            int[] randomIDs = new int[nrow];
            try (BufferedReader br = new BufferedReader(new FileReader(randomDataPath))) {
                String line;
                int index = 0;
                while ((line = br.readLine()) != null) {
                    randomIDs[index++] = Integer.parseInt(line);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            for (int i = 0; i < numThreads & i * blklen < nrow; i++) {
                ObjectReader reader = new ObjectReader(inDataPath, method);
                tasks.add(new ReadIOTaskRandom(reader ,randomIDs,i * blklen, Math.min((i + 1) * blklen, nrow)));
            }
        }

        //wait until all tasks have been executed
        List<Future<Integer>> rt = pool.invokeAll(tasks);
        pool.shutdown();

        //check for exceptions
        for (Future<Integer> f: rt){
            f.get();
        }

    }

    private static abstract class Task implements Callable<Integer> {
        protected final ObjectReader reader;
        protected final int beginPos;
        protected final int endPos;
        public Task(ObjectReader reader, int beginPos, int endPos) {
            this.reader = reader;
            this.beginPos = beginPos;
            this.endPos = endPos;
        }
    }


    private static class ReadIOTask extends Task {
        public ReadIOTask(ObjectReader reader, int beginPos, int endPos) {
            super(reader, beginPos, endPos);
        }

        @Override
        public Integer call() {
            reader.readIO(beginPos, endPos - beginPos);
            return null;
        }
    }

    private static class ReadIOTaskRandom extends Task {
        private final int[] randomList;

        public ReadIOTaskRandom(ObjectReader reader, int[] randomList, int beginPos, int endPos) {
            super(reader, beginPos, endPos);
            this.randomList = randomList;
        }

        @Override
        public Integer call() {
            for (int i = beginPos; i < endPos; i++) {
                reader.readIO(randomList[i], 1);
            }
            return null;
        }
    }
}
