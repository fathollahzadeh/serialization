import com.google.gson.Gson;
import edu.bu.tweet.TweetStatus;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Stream;

public class test1 {

    public static void main(String[] args) throws IOException {

        String fileName="/home/saeed/Documents/Projects/1-Research/SaeedKiaSVN/copub/2019/TwitterJava/src/data/tweets_jsonline_1M.txt";

        try (Stream<String> stream = Files.lines(Paths.get(fileName))) {

            AtomicInteger i= new AtomicInteger(0);
           stream.forEach(
                   e->{
                       //if (i.get()<1) {
                           Gson gson = new Gson();
                           TweetStatus tweetStatus = gson.fromJson(e, TweetStatus.class);
                    //   }
                    //  i.getAndIncrement();
                   }
           );
        }
    }


}
