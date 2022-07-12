package at.tugraz.experiments;

import at.tugraz.runtime.ObjectWriter;
import at.tugraz.tweet.TweetStatus;
import com.google.gson.Gson;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Stream;

public class DataPrepare {

    public static void main(String[] args) throws IOException {

        String inDataPath = System.getProperty("inDataPath");
        String outDataPath =System.getProperty("outDataPath");
        int nrow = Integer.parseInt(System.getProperty("nrow"));

        ObjectWriter writer = new ObjectWriter(outDataPath, "Kryo", nrow);
        AtomicInteger index = new AtomicInteger();
        try(Stream<String> stream = Files.lines(Paths.get(inDataPath))) {
            stream.forEach(e -> {
                if (index.get()<nrow) {
                    Gson gson = new Gson();
                    TweetStatus tweetStatus = gson.fromJson(e, TweetStatus.class);
                    writer.writeObjectToFile(tweetStatus);
                }
                index.getAndIncrement();

            });
        }
        catch(IOException e) {
            e.printStackTrace();
        }

        writer.flush();



//        BlockingQueue<String> queue = new ArrayBlockingQueue<>(1000);
//        ReadTweet readTweet = new ReadTweet(queue, inDataPath);
//        Thread rt = new Thread(readTweet);
//        readTweet.setReadStatus(true);
//        rt.start();
//
//        ObjectWriter writer = new ObjectWriter(outDataPath, "ProtoBuf", nrow);
//        try {
//            String line;
//            for (long i = 0; i < nrow; i++) {
//                line = queue.take();
//                Gson gson = new Gson();
//                TweetStatus tweetStatus = gson.fromJson(line, TweetStatus.class);
//                writer.writeObjectToFile(tweetStatus);
//            }
//            readTweet.setReadStatus(false);
//            queue.take();
//            writer.flush();
//        } catch (Exception e) {
//            e.printStackTrace();
//        }
    }
}
