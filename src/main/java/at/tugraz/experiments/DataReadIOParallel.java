package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.OptimizerUtils;

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
                tasks.add(new ReadIOTask(inDataPath, method, i * blklen, Math.min((i + 1) * blklen, nrow)));
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
                tasks.add(new ReadIOTaskRandom(inDataPath, method ,randomIDs,i * blklen, Math.min((i + 1) * blklen, nrow)));
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
        public Task(String inDataPath, String method, int beginPos, int endPos) {
            this.reader = new ObjectReader(inDataPath, method);
            this.beginPos = beginPos;
            this.endPos = endPos;
        }
    }


    private static class ReadIOTask extends Task {
        public ReadIOTask(String inDataPath, String method, int beginPos, int endPos) {
            super(inDataPath, method, beginPos, endPos);
        }

        @Override
        public Integer call() {
            reader.readIO(beginPos, endPos - beginPos+1);
            return null;
        }
    }

    private static class ReadIOTaskRandom extends Task {
        private final int[] randomList;

        public ReadIOTaskRandom(String inDataPath, String method, int[] randomList, int beginPos, int endPos) {
            super(inDataPath, method, beginPos, endPos);
            this.randomList = randomList;
        }

        @Override
        public Integer call() {
            for (int i = beginPos; i < endPos; i++)
                reader.readIO(randomList[i]);
            return null;
        }
    }
}
