package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.Const;
import at.tugraz.util.OptimizerUtils;
import at.tugraz.util.RootData;

import java.io.File;
import java.io.FileNotFoundException;
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
            int rlen = Math.min((i + 1) * blklen, nrow) - i * blklen + 1;
            String fname = outDataPath + "/" + i;
            tasks.add(new WriterTask(inDataPath, fname, method, rlen, i * blklen, Math.min((i + 1) * blklen, nrow)));
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

        public WriterTask(String inDataPath, String outDataPath, String method, int rlen, int beginPos, int endPos) throws FileNotFoundException {
            this.reader = new ObjectReader(inDataPath, "Kryo");;
            this.writer = new ObjectWriter(outDataPath, method, rlen);;
            this.beginPos = beginPos;
            this.endPos = endPos;
        }

        @Override
        public Integer call() {
            int size = Const.BATCHSIZE;
            for (int i = beginPos; i < endPos; ) {
                RootData[] rd = reader.readObjects(i, size);
                writer.writeObjectToFile(rd);
                i += rd.length;
                size = Math.min(endPos - i , Const.BATCHSIZE);
            }
            writer.flush();
            return null;
        }
    }
}
