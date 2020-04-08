import com.google.gson.Gson;
import edu.bu.tweet.TweetStatus;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Stream;

public class test4 {

    public static void main(String[] args) throws IOException {

         String fileName = "/home/saeed/Documents/Projects/1-Research/SaeedKiaSVN/copub/2019/TwitterJava/src/data/tweets_jsonline_1M.txt";
        //String fileName = "/home/saeed/Documents/Projects/1-Research/SaeedKiaSVN/copub/2019/Twitter/data/tweets_1M_rows.txt";

        try (Stream<String> stream = Files.lines(Paths.get(fileName))) {

            AtomicInteger i = new AtomicInteger(0);
            stream.forEach(
                    e -> {
                        if (i.get() <4) {
                            // System.out.println(e);
                            Gson gson = new Gson();
                            TweetStatus tweetStatus = gson.fromJson(e, TweetStatus.class);

                            String str1=gson.toJson(tweetStatus).toString();
                            byte[] b=tweetStatus.protocolBufferWrite();

                            TweetStatus tweetStatus1=new TweetStatus();
                            tweetStatus1.protocolBufferRead(b);
                            String str2=gson.toJson(tweetStatus1);
                            if (tweetStatus1.getRetweeted_status()!=null)
                            System.out.println(str2);


                           // System.out.println("1--- "+gson.toJson(tweetStatus));
                           // System.out.println(">>> "+.length);

                        }

                    }
            );
        }
    }


}
