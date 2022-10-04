package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.Const;
import at.tugraz.util.OptimizerUtils;
import at.tugraz.util.RootData;

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
        int nrow = Integer.parseInt(System.getProperty("nrow"));

        int numThreads = OptimizerUtils.getParallelWriteParallelism();
        ExecutorService pool = CommonThreadPool.get(numThreads);
        ArrayList<DeSerializeTask> tasks = new ArrayList<>();
        int blklen = (int) Math.ceil((double) nrow / numThreads);

        for (int i = 0; i < numThreads & i * blklen < nrow; i++) {
            tasks.add(new DeSerializeTask(inDataPath, i * blklen, Math.min((i + 1) * blklen, nrow)));
        }

        //wait until all tasks have been executed
        List<Future<Integer>> rt = pool.invokeAll(tasks);
        pool.shutdown();

        //check for exceptions
        for (Future<Integer> f : rt) {
            f.get();
        }
    }


    static class DeSerializeTask implements Callable<Integer> {
        protected final ObjectReader reader;
        protected final int beginPos;
        protected final int endPos;

        public DeSerializeTask(String inDataPath,int beginPos, int endPos) {
            this.reader = new ObjectReader(inDataPath, "Kryo");
            this.beginPos = beginPos;
            this.endPos = endPos;
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
}
