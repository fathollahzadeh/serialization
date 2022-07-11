package at.tugraz.experiments;

import at.tugraz.filehandler.ReadTweet;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.tweet.TweetStatus;
import com.google.gson.Gson;

import java.io.IOException;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public class DataPrepare {

    public static void main(String[] args) throws IOException {

//        String inDataPath = "/home/saeed/Documents/Github/serialization/Experiments/data/tweets.txt"; //System.getProperty("inDataPath");
//        String outDataPath ="/home/saeed/Documents/Github/serialization/Experiments/data/tweets.bin"; //System.getProperty("outDataPath");
//        int nrow = 1000; //Integer.parseInt(System.getProperty("nrow"));

        String inDataPath = System.getProperty("inDataPath");
        String outDataPath =System.getProperty("outDataPath");
        int nrow = Integer.parseInt(System.getProperty("nrow"));

        BlockingQueue<String> queue = new ArrayBlockingQueue<>(1000);
        ReadTweet readTweet = new ReadTweet(queue, inDataPath);
        Thread rt = new Thread(readTweet);
        readTweet.setReadStatus(true);
        rt.start();

        ObjectWriter writer = new ObjectWriter(outDataPath, "Kryo", nrow);
        try {
            String line;
            for (long i = 0; i < nrow; i++) {
                line = queue.take();
                Gson gson = new Gson();
                TweetStatus tweetStatus = gson.fromJson(line, TweetStatus.class);
                writer.writeObjectToFile(tweetStatus);
            }
            readTweet.setReadStatus(false);
            queue.take();
            writer.flush();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
