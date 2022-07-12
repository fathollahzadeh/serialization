package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.OptimizerUtils;
import at.tugraz.util.RootData;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

public class DataWriteParallel {

    public static void main(String[] args) throws IOException, InterruptedException, ExecutionException {

        String inDataPath = System.getProperty("inDataPath");
        String outDataPath = System.getProperty("outDataPath");
        String method = System.getProperty("method");
        int nrow = Integer.parseInt(System.getProperty("nrow"));

        int numThreads = OptimizerUtils.getParallelWriteParallelism();
        ExecutorService pool = CommonThreadPool.get(numThreads);
        ArrayList<WriterTask> tasks = new ArrayList<>();
        int blklen = (int) Math.ceil((double) nrow / numThreads);
        int batch = 256;

        String[] path = outDataPath.split("\\.");
        outDataPath = path[0];
        File f = new File(outDataPath);
        if ((f.exists() && !f.isDirectory()) || (!f.exists())) {
            f.mkdir();
        }
        f = new File(outDataPath + "/" + method);
        outDataPath = outDataPath + "/" + method;
        if ((f.exists() && !f.isDirectory()) || (!f.exists())) {
            f.mkdir();
        }

        for (int i = 0; i < numThreads & i * blklen < nrow; i++) {
            ObjectReader reader = new ObjectReader(inDataPath, "Kryo");
            int rlen = Math.min((i + 1) * blklen, nrow) - i * blklen + 1;
            ObjectWriter writer = new ObjectWriter(outDataPath + "/" + i, method, rlen);
            tasks.add(new WriterTask(reader, writer, i * blklen, Math.min((i + 1) * blklen, nrow), batch));
        }

        //wait until all tasks have been executed
        List<Future<Integer>> rt = pool.invokeAll(tasks);
        pool.shutdown();

        //check for exceptions
        for (Future<Integer> fu : rt) {
            fu.get();
        }

    }

    private static class WriterTask implements Callable<Integer> {
        private final ObjectReader reader;
        private final ObjectWriter writer;
        private final int beginPos;
        private final int endPos;
        private final int batch;

        public WriterTask(ObjectReader reader, ObjectWriter writer, int beginPos, int endPos, int batch) {
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
                writer.writeObjectToFile(rd);
                i += rd.length;
                size = Math.min(endPos - i, batch);
            }
            writer.flush();
            return null;
        }
    }
}
