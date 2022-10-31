package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.tweet.TweetStatus;
import at.tugraz.util.*;
import com.esotericsoftware.kryo.Kryo;

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

        ObjectReader reader = new ObjectReader(inDataPath, "Kryo");
        ArrayList<byte[]> buffer = reader.readIO(0, nrow);

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
            String fname = outDataPath + "/" + i;
            int beginPos = i * blklen;
            int endPos = Math.min((i + 1) * blklen, nrow);
            tasks.add(new WriterTask(buffer.subList(beginPos, endPos), fname, method));
        }

        //wait until all tasks have been executed
        List<Future<Integer>> rt = pool.invokeAll(tasks);
        pool.shutdown();

        //check for exceptions
        for (Future<Integer> fu : rt) {
            fu.get();
        }
    }

    static class WriterTask implements Callable<Integer> {
        protected final List<byte[]> buffer;
        protected final Kryo kryo;
        private final ObjectWriter writer;

        public WriterTask(List<byte[]> buffer, String outDataPath, String method) throws FileNotFoundException {
            this.buffer = buffer;
            this.kryo = new KryoSinglton().getKryo();
            this.writer = new ObjectWriter(outDataPath, method, buffer.size());
        }

        @Override
        public Integer call() {
            TweetStatus myData = new TweetStatus();
            for (byte[] b : buffer) {
                RootData object = myData.kryoDeserialization(b, myData.getClass(), this.kryo);
                writer.writeObjectToFile(object);
            }
            writer.flush();
            return null;
        }
    }
}
