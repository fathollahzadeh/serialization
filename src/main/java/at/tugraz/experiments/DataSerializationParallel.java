package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.tweet.TweetStatus;
import at.tugraz.util.*;
import com.esotericsoftware.kryo.Kryo;

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

        ObjectReader reader =  new ObjectReader(inDataPath, "Kryo");
        ArrayList<byte[]> buffer = reader.readIO(0, nrow);

        int numThreads = OptimizerUtils.getParallelWriteParallelism();
        ExecutorService pool = CommonThreadPool.get(numThreads);
        ArrayList<SerializeTask> tasks = new ArrayList<>();
        int blklen = (int) Math.ceil((double) nrow / numThreads);

        for (int i = 0; i < numThreads & i * blklen < nrow; i++) {
            int beginPos = i * blklen;
            int endPos = Math.min((i + 1) * blklen, nrow);
            tasks.add(new SerializeTask(buffer.subList(beginPos, endPos), method));
        }

        //wait until all tasks have been executed
        List<Future<Integer>> rt = pool.invokeAll(tasks);
        pool.shutdown();

        //check for exceptions
        for (Future<Integer> f : rt) {
            f.get();
        }
    }

    static class SerializeTask implements Callable<Integer> {
        protected final  List<byte[]> buffer;
        protected final Kryo kryo;
        private final ObjectWriter writer;

        public SerializeTask(List<byte[]> buffer, String method) {
            this.buffer = buffer;
            this.kryo = new KryoSinglton().getKryo();
            this.writer = new ObjectWriter(method, buffer.size(), Const.PAGESIZE);
        }

        @Override
        public Integer call() {
            TweetStatus myData = new TweetStatus();
            for (byte[] b: buffer){
                RootData object = myData.kryoDeserialization(b, myData.getClass(), this.kryo);
                writer.serializeObject(object);
            }
            return null;
        }
    }
}
