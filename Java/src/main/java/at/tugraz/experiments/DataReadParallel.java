package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.OptimizerUtils;
import at.tugraz.util.RootData;

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
        int nrow = Integer.parseInt(System.getProperty("nrow"));

        int numThreads = OptimizerUtils.getParallelWriteParallelism();
        ExecutorService pool = CommonThreadPool.get(numThreads);
        ArrayList<ReadIOTask> tasks = new ArrayList<>();
        int blklen = (int) Math.ceil((double) nrow / numThreads);

        RootData[] rd = new RootData[nrow];
        for (int i = 0; i < numThreads & i * blklen < nrow; i++) {
            ObjectReader reader = new ObjectReader(inDataPath, method);
            tasks.add(new ReadIOTask(reader, i * blklen, Math.min((i + 1) * blklen, nrow), rd));
        }

        //wait until all tasks have been executed
        List<Future<Integer>> rt = pool.invokeAll(tasks);
        pool.shutdown();

        //check for exceptions
        for (Future<Integer> f: rt){
            f.get();
        }

    }

    private static class ReadIOTask implements Callable<Integer> {
        private final ObjectReader reader;
        private final int beginPos;
        private final int endPos;
        private final RootData[] rd;

        public ReadIOTask(ObjectReader reader, int beginPos, int endPos, RootData[] rd) {
            this.reader = reader;
            this.beginPos = beginPos;
            this.endPos = endPos;
            this.rd = rd;
        }

        @Override
        public Integer call() {
            reader.readObjects(beginPos, endPos - beginPos +1, this.rd);
            return null;
        }
    }
}
