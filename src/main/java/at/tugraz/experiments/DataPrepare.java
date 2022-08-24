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
            try (Stream<String> stream = Files.lines(Paths.get(inDataPath))) {
                stream.forEach(e -> {
                    if (index.get() < nrow) {
                        Gson gson = new Gson();
                        TweetStatus tweetStatus = gson.fromJson(e, TweetStatus.class);
                        writer.writeObjectToFile(tweetStatus);
                    }
                    index.getAndIncrement();

                });
            } catch (IOException e) {
                e.printStackTrace();
            }

        writer.flush();
    }
}
