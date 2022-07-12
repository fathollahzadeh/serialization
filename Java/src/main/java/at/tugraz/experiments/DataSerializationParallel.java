package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
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

public class DataSerializationParallel {

    public static void main(String[] args) throws IOException, InterruptedException, ExecutionException {

        String inDataPath = System.getProperty("inDataPath");
        String method = System.getProperty("method");
        int nrow = Integer.parseInt(System.getProperty("nrow"));

        int numThreads = OptimizerUtils.getParallelWriteParallelism();
        ExecutorService pool = CommonThreadPool.get(numThreads);
        ArrayList<SerializeTask> tasks = new ArrayList<>();
        int blklen = (int) Math.ceil((double) nrow / numThreads);
        int batch = 256;
        for (int i = 0; i < numThreads & i * blklen < nrow; i++) {
            ObjectReader reader = new ObjectReader(inDataPath, "Kryo");
            int rlen = Math.min((i + 1) * blklen, nrow) - i * blklen + 1;
            ObjectWriter writer = new ObjectWriter(method, rlen);
            tasks.add(new SerializeTask(reader, writer, i * blklen, Math.min((i + 1) * blklen, nrow), batch));
        }

        //wait until all tasks have been executed
        List<Future<Integer>> rt = pool.invokeAll(tasks);
        pool.shutdown();

        //check for exceptions
        for (Future<Integer> f: rt){
            f.get();
        }

    }

    private static class SerializeTask implements Callable<Integer> {
        private final ObjectReader reader;
        private final ObjectWriter writer;
        private final int beginPos;
        private final int endPos;
        private final int batch;

        public SerializeTask(ObjectReader reader, ObjectWriter writer, int beginPos, int endPos, int batch) {
            this.reader = reader;
            this.writer = writer;
            this.beginPos = beginPos;
            this.endPos = endPos;
            this.batch = batch;
        }

        @Override
        public Integer call() {
            int size = batch;
            for (int i = beginPos; i < endPos; ) {
                RootData[] rd = reader.readObjects(i, size);
                writer.serializeObjects(rd);
                i += rd.length;
                size = Math.min(endPos - i, batch);
            }
            return null;
        }
    }
}
