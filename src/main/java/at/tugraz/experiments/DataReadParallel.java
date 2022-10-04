package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.OptimizerUtils;
import at.tugraz.util.RootData;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

public class DataReadParallel {

    public static void main(String[] args) throws IOException, InterruptedException, ExecutionException {

        String inDataPath = System.getProperty("inDataPath");
        String method = System.getProperty("method");
        String seqRand = System.getProperty("seqRand");
        int nrow = Integer.parseInt(System.getProperty("nrow"));

        int numThreads = OptimizerUtils.getParallelWriteParallelism();
        ExecutorService pool = CommonThreadPool.get(numThreads);
        ArrayList<Task> tasks = new ArrayList<>();
        int blklen = (int) Math.ceil((double) nrow / numThreads);
        RootData[] rd = new RootData[nrow];

        if (seqRand.equalsIgnoreCase("sequential")) {
            for (int i = 0; i < numThreads & i * blklen < nrow; i++) {
                tasks.add(new ReadTask(inDataPath, method, i * blklen, Math.min((i + 1) * blklen, nrow), rd));
            }
        } else {
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
                tasks.add(new ReadTaskRandom(inDataPath, method, randomIDs, i * blklen, Math.min((i + 1) * blklen, nrow), rd));
            }
        }

        //wait until all tasks have been executed
        List<Future<Integer>> rt = pool.invokeAll(tasks);
        pool.shutdown();

        //check for exceptions
        for (Future<Integer> f : rt) {
            f.get();
        }

    }

    private static abstract class Task implements Callable<Integer> {
        protected final ObjectReader reader;
        protected final long beginPos;
        protected final long endPos;
        protected final RootData[] rd;

        public Task(String inDataPath, String method, long beginPos, long endPos, RootData[] rd) {
            this.reader = new ObjectReader(inDataPath, method);
            this.beginPos = beginPos;
            this.endPos = endPos;
            this.rd = rd;
        }
    }


    private static class ReadTask extends Task {

        public ReadTask(String inDataPath, String method, long beginPos, long endPos, RootData[] rd) {
            super(inDataPath, method, beginPos, endPos, rd);
        }

        @Override
        public Integer call() {
            reader.readObjects(beginPos, (int) (endPos - beginPos), this.rd);
            return null;
        }
    }

    private static class ReadTaskRandom extends Task {
        private final int[] randomList;

        public ReadTaskRandom(String inDataPath, String method, int[] randomList, int beginPos, int endPos, RootData[] rd) {
            super(inDataPath, method, beginPos, endPos, rd);
            this.randomList = randomList;
        }

        @Override
        public Integer call() {
            for (int i = (int) beginPos; i < endPos; i++)
                this.rd[i] = reader.readObject(randomList[i]);
            return null;
        }
    }
}
