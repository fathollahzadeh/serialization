package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.Const;
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

public class DataLoadToMemoryParallel {

    public static void main(String[] args) throws IOException, InterruptedException, ExecutionException {

        String inDataPath = System.getProperty("inDataPath");
        String seqRand = System.getProperty("seqRand");
        int nrow = Integer.parseInt(System.getProperty("nrow"));

        int numThreads = OptimizerUtils.getParallelWriteParallelism();
        ExecutorService pool = CommonThreadPool.get(numThreads);
        ArrayList<Task> tasks = new ArrayList<>();
        int blklen = (int) Math.ceil((double) nrow / numThreads);

        if (seqRand.equalsIgnoreCase("sequential")) {
            for (int i = 0; i < numThreads & i * blklen < nrow; i++) {
                ObjectReader reader = new ObjectReader(inDataPath, "Kryo");
                tasks.add(new SerializeTask(reader, i * blklen, Math.min((i + 1) * blklen, nrow)));
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
                ObjectReader reader = new ObjectReader(inDataPath, "Kryo");
                tasks.add(new SerializeTaskRandom(reader ,randomIDs,i * blklen, Math.min((i + 1) * blklen, nrow)));
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
        protected final int beginPos;
        protected final int endPos;

        public Task(ObjectReader reader, int beginPos, int endPos) {
            this.reader = reader;
            this.beginPos = beginPos;
            this.endPos = endPos;
        }
    }

    static class SerializeTask extends Task {

        public SerializeTask(ObjectReader reader, int beginPos, int endPos) {
            super(reader, beginPos, endPos);
        }

        @Override
        public Integer call() {
            int size = Const.BATCHSIZE;
            for (int i = beginPos; i < endPos; ) {
                RootData[] rd = reader.readObjects(i, size);
                i += rd.length;
                size = Math.min(endPos - i + 1, Const.BATCHSIZE);
            }
            return null;
        }
    }

    private static class SerializeTaskRandom extends Task {
        private final int[] randomList;

        public SerializeTaskRandom(ObjectReader reader, int[] randomList, int beginPos, int endPos) {
            super(reader, beginPos, endPos);
            this.randomList = randomList;
        }

        @Override
        public Integer call() {
            for (int i = beginPos; i < endPos; i++) {
                reader.readObjects(randomList[i], 1);
            }
            return null;
        }
    }
}
