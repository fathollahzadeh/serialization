import com.google.gson.Gson;
import edu.bu.tweet.TweetStatus;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Stream;

public class DataDivision {

    private static File fout_simple;
    private static File fout_complex;
    private static File fout_tweet_relation;
    private static FileOutputStream fos_simple;
    private static FileOutputStream fos_complex;
    private static FileOutputStream fos_tweet_relation;

    private static BufferedWriter bw_simple;
    private static BufferedWriter bw_complex;
    private static BufferedWriter bw_tweet_relation;


    public static void main(String[] args) throws IOException {

        fout_simple = new File("/mnt/clean_data/tweets_simple.txt");
        fout_complex = new File("/mnt/clean_data/tweets_complex.txt");
        fout_tweet_relation = new File("/mnt/clean_data/tweets_relation.txt");
        fos_simple = new FileOutputStream(fout_simple);
        fos_complex = new FileOutputStream(fout_complex);
        fos_tweet_relation = new FileOutputStream(fout_tweet_relation);

        bw_simple = new BufferedWriter(new OutputStreamWriter(fos_simple));
        bw_complex = new BufferedWriter(new OutputStreamWriter(fos_complex));
        bw_tweet_relation = new BufferedWriter(new OutputStreamWriter(fos_tweet_relation));


        //String fileName = "/home/saeed/Documents/Projects/1-Research/GitHub/serialization/data/tweets_jsonline_1M.txt";
        String fileName = "/mnt/tweets_1M_rows.txt";

        bw_tweet_relation.write("id,retweet_id,quote_id");
        bw_tweet_relation.newLine();
        AtomicInteger max_h = new AtomicInteger();

        try (Stream<String> stream = Files.lines(Paths.get(fileName))) {

            stream.forEach(
                    e -> {
                        Gson gson = new Gson();
                        TweetStatus tweetStatus = gson.fromJson(e, TweetStatus.class);


                        if (tweetStatus.getRetweeted_status() == null && tweetStatus.getQuoted_status() == null) {
                            try {
                                bw_simple.write(e);
                                bw_simple.newLine();
                                bw_tweet_relation.write(tweetStatus.getId() + ",-1,-1");
                                bw_tweet_relation.newLine();
                            } catch (IOException ex) {
                                ex.printStackTrace();
                            }

                        } else {
                            try {
                                bw_complex.write(e);
                                bw_complex.newLine();

                                long retweet_id = -1;
                                long quoto_id = -1;

                                if (tweetStatus.getRetweeted_status() != null) {
                                    retweet_id = tweetStatus.getRetweeted_status().getId();
                                }
                                if (tweetStatus.getQuoted_status() != null) {
                                    quoto_id = tweetStatus.getQuoted_status().getId();
                                }
                                bw_tweet_relation.write(tweetStatus.getId() + "," + retweet_id + "," + quoto_id);
                                bw_tweet_relation.newLine();

                            } catch (IOException ex) {
                                ex.printStackTrace();
                            }
                        }

                    }
            );
        } catch (Exception ex) {

        }

        bw_simple.close();
        bw_complex.close();
        bw_tweet_relation.close();
    }


}
