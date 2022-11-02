package at.tugraz.experiments;

import at.tugraz.runtime.ObjectWriter;
import at.tugraz.tweet.TweetStatus;
import com.google.gson.Gson;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Stream;

public class frequency {

    public static void main(String[] args) throws IOException {

        String inDataPath = "/home/saeed/Documents/GitHub/serialization/Experiments/data/tweets.txt";

        AtomicInteger extended_tweet = new AtomicInteger();
        AtomicInteger entities = new AtomicInteger();
        AtomicInteger extended_tweet_entities = new AtomicInteger();
        AtomicInteger extended_tweet_extended_entities = new AtomicInteger();

        AtomicInteger hashtags = new AtomicInteger();
        AtomicInteger polls = new AtomicInteger();
        AtomicInteger media = new AtomicInteger();
        AtomicInteger urls = new AtomicInteger();
        AtomicInteger user_mention = new AtomicInteger();
        AtomicInteger symbol = new AtomicInteger();
        AtomicInteger sizes = new AtomicInteger();
        AtomicInteger media_sizes = new AtomicInteger();
        AtomicInteger thumb = new AtomicInteger();
        AtomicInteger large = new AtomicInteger();
        AtomicInteger medium = new AtomicInteger();
        AtomicInteger small = new AtomicInteger();


        try (Stream<String> stream = Files.lines(Paths.get(inDataPath))) {
            stream.forEach(e -> {
                Gson gson = new Gson();
                TweetStatus tweetStatus = gson.fromJson(e, TweetStatus.class);
                if (tweetStatus.getExtended_tweet() != null) {
                    extended_tweet.getAndIncrement();
                    if (tweetStatus.getExtended_tweet().getEntities() != null) {
                        extended_tweet_entities.getAndIncrement();

                        if (tweetStatus.getExtended_tweet().getEntities().getMedia() !=null)
                            for (int i=0; i< tweetStatus.getExtended_tweet().getEntities().getMedia().size(); i++) {
                                media.getAndIncrement();
                                if( tweetStatus.getExtended_tweet().getEntities().getMedia().get(i).getSizes() !=null) {
                                    sizes.getAndIncrement();
                                    media_sizes.getAndIncrement();
                                    if(tweetStatus.getExtended_tweet().getEntities().getMedia().get(i).getSizes().getThumb()!=null){
                                        thumb.getAndIncrement();
                                    }

                                    if(tweetStatus.getExtended_tweet().getEntities().getMedia().get(i).getSizes().getLarge()!=null){
                                        large.getAndIncrement();
                                    }

                                    if(tweetStatus.getExtended_tweet().getEntities().getMedia().get(i).getSizes().getMedium()!=null){
                                        medium.getAndIncrement();
                                    }

                                    if(tweetStatus.getExtended_tweet().getEntities().getMedia().get(i).getSizes().getSmall()!=null){
                                        small.getAndIncrement();
                                    }
                                }

                            }

                        if (tweetStatus.getExtended_tweet().getEntities().getUrls() !=null) {
                            for (int i = 0; i < tweetStatus.getExtended_tweet().getEntities().getUrls().size(); i++) {
                                urls.getAndIncrement();
                            }
                        }

                        if (tweetStatus.getExtended_tweet().getEntities().getUser_mentions() !=null)
                            for (int i=0; i< tweetStatus.getExtended_tweet().getEntities().getUser_mentions().size(); i++)
                                user_mention.getAndIncrement();

                        if (tweetStatus.getExtended_tweet().getEntities().getSymbols() !=null)
                            for (int i=0; i< tweetStatus.getExtended_tweet().getEntities().getSymbols().size(); i++)
                                symbol.getAndIncrement();

                        if (tweetStatus.getExtended_tweet().getEntities().getPolls() !=null)
                            for (int i=0; i< tweetStatus.getExtended_tweet().getEntities().getPolls().size(); i++)
                                polls.getAndIncrement();

                        if (tweetStatus.getExtended_tweet().getEntities().getHashtags() !=null)
                            for (int i=0; i< tweetStatus.getExtended_tweet().getEntities().getHashtags().size(); i++)
                                hashtags.getAndIncrement();

                    }
                    if (tweetStatus.getExtended_tweet().getExtended_entities() != null) {
                        extended_tweet_extended_entities.getAndIncrement();
                        if (tweetStatus.getExtended_tweet().getExtended_entities().getMedia() !=null)
                            for (int i=0; i< tweetStatus.getExtended_tweet().getExtended_entities().getMedia().size(); i++) {
                                media.getAndIncrement();
                                if( tweetStatus.getExtended_tweet().getExtended_entities().getMedia().get(i).getSizes() !=null) {
                                    sizes.getAndIncrement();
                                    media_sizes.getAndIncrement();
                                    if(tweetStatus.getExtended_tweet().getExtended_entities().getMedia().get(i).getSizes().getThumb()!=null){
                                        thumb.getAndIncrement();
                                    }

                                    if(tweetStatus.getExtended_tweet().getExtended_entities().getMedia().get(i).getSizes().getLarge()!=null){
                                        large.getAndIncrement();
                                    }

                                    if(tweetStatus.getExtended_tweet().getExtended_entities().getMedia().get(i).getSizes().getMedium()!=null){
                                        medium.getAndIncrement();
                                    }

                                    if(tweetStatus.getExtended_tweet().getExtended_entities().getMedia().get(i).getSizes().getSmall()!=null){
                                        small.getAndIncrement();
                                    }
                                }

                            }

                    }
                }

                if (tweetStatus.getEntities() != null) {
                    entities.getAndIncrement();

                    if (tweetStatus.getEntities().getMedia() !=null)
                        for (int i=0; i< tweetStatus.getEntities().getMedia().size(); i++) {
                            media.getAndIncrement();
                            if( tweetStatus.getEntities().getMedia().get(i).getSizes() !=null) {
                                sizes.getAndIncrement();
                                media_sizes.getAndIncrement();
                                if(tweetStatus.getEntities().getMedia().get(i).getSizes().getThumb()!=null){
                                    thumb.getAndIncrement();
                                }

                                if(tweetStatus.getEntities().getMedia().get(i).getSizes().getLarge()!=null){
                                    large.getAndIncrement();
                                }

                                if(tweetStatus.getEntities().getMedia().get(i).getSizes().getMedium()!=null){
                                    medium.getAndIncrement();
                                }

                                if(tweetStatus.getEntities().getMedia().get(i).getSizes().getSmall()!=null){
                                    small.getAndIncrement();
                                }
                            }

                        }

                    if (tweetStatus.getEntities().getUrls() !=null) {
                        for (int i = 0; i < tweetStatus.getEntities().getUrls().size(); i++) {
                            urls.getAndIncrement();
                        }
                    }

                    if (tweetStatus.getEntities().getUser_mentions() !=null)
                        for (int i=0; i< tweetStatus.getEntities().getUser_mentions().size(); i++)
                            user_mention.getAndIncrement();

                    if (tweetStatus.getEntities().getSymbols() !=null)
                        for (int i=0; i< tweetStatus.getEntities().getSymbols().size(); i++)
                            symbol.getAndIncrement();

                    if (tweetStatus.getEntities().getPolls() !=null)
                        for (int i=0; i< tweetStatus.getEntities().getPolls().size(); i++)
                            polls.getAndIncrement();

                    if (tweetStatus.getEntities().getHashtags() !=null)
                        for (int i=0; i< tweetStatus.getEntities().getHashtags().size(); i++)
                            hashtags.getAndIncrement();
                }

            });
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("extended_tweet = "+ extended_tweet);
        System.out.println("entities = "+ entities);
        System.out.println("extended_tweet_entities = "+ extended_tweet_entities);
        System.out.println("extended_tweet_extended_entities = "+ extended_tweet_extended_entities);

        System.out.println("hashtags = "+ hashtags);
        System.out.println("polls = "+ polls);
        System.out.println("media = "+ media);
        System.out.println("urls = "+ urls);
        System.out.println("user_mention = "+ user_mention);
        System.out.println("symbol = "+ symbol);
        System.out.println("sizes = "+ sizes);
        System.out.println("media_sizes = "+ media_sizes);
        System.out.println("thumb = "+ thumb);
        System.out.println("large = "+ large);
        System.out.println("medium = "+ medium);
        System.out.println("small = "+ small);


    }
}
