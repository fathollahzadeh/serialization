import com.google.gson.Gson;
import edu.bu.tweet.TweetStatus;
import sun.rmi.runtime.Log;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;
import java.util.stream.Stream;

public class random_data {

    public static void main(String[] args) throws IOException {

        String fileName="/home/saeed/randomdata/randomlist_1000000.txt";

        try (Stream<String> stream = Files.lines(Paths.get(fileName))) {

            AtomicInteger i = new AtomicInteger(0);

            AtomicLong sum= new AtomicLong();

            Map<Long,Long> myMap=new HashMap<>();
            stream.forEach(
                    e -> {
                        long value=Long.parseLong(e);
                        if (myMap.get(value)==null)
                            myMap.put(value,0L);
                        myMap.put(value,(myMap.get(value)+1));

                    }
            );

            for (Long l:myMap.keySet()){
                System.out.println(l+"= "+myMap.get(l));
            }

            System.out.println(myMap.size());
        }

    }
}
