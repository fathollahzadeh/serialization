package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.tweet.TweetStatus;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.KryoSinglton;
import at.tugraz.util.OptimizerUtils;
import at.tugraz.util.RootData;
import com.esotericsoftware.kryo.Kryo;

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

        ObjectReader reader =  new ObjectReader(inDataPath, "Kryo");
        ArrayList<byte[]> buffer = reader.readIO(0, nrow);

        int numThreads = OptimizerUtils.getParallelWriteParallelism();
        ExecutorService pool = CommonThreadPool.get(numThreads);
        ArrayList<DeSerializeTask> tasks = new ArrayList<>();
        int blklen = (int) Math.ceil((double) nrow / numThreads);

        for (int i = 0; i < numThreads & i * blklen < nrow; i++) {
            int beginPos = i * blklen;
            int endPos = Math.min((i + 1) * blklen, nrow);
            tasks.add(new DeSerializeTask(buffer.subList(beginPos, endPos)));
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
        protected final  List<byte[]> buffer;
        protected final Kryo kryo;

        public DeSerializeTask(List<byte[]> buffer) {
            this.buffer = buffer;
            this.kryo = new KryoSinglton().getKryo();
        }

        @Override
        public Integer call() {
            TweetStatus myData = new TweetStatus();
            for (byte[] b: buffer){
                RootData object = myData.kryoDeserialization(b, myData.getClass(), this.kryo);
            }
            return null;
        }
    }
}