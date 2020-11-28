import com.google.gson.Gson;
import edu.bu.tweet.TweetStatus;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;
import java.util.stream.Stream;

public class test1 {

    public static void main(String[] args) throws IOException {

       String fileName = "/home/saeed/Documents/Projects/1-Research/GitHub/serialization/data/tweets_jsonline_1M.txt";
      // String fileName="/home/saeed/Documents/Projects/1-Research/GitHub/serialization/data/tweets_1M_rows.txt";

        try (Stream<String> stream = Files.lines(Paths.get(fileName))) {

            AtomicInteger i = new AtomicInteger(0);

            AtomicLong sum= new AtomicLong();

            stream.forEach(
                    e -> {
                        Gson gson = new Gson();
                        TweetStatus tweetStatus = gson.fromJson(e, TweetStatus.class);

                        sum.addAndGet(e.length());

                       // System.out.println(gson.toJson(tweetStatus2));
                         i.getAndIncrement();
                    }
            );

            double avg;
            avg = sum.longValue() / i.intValue();
            System.out.println("avg="+avg);
        }
    }


}
