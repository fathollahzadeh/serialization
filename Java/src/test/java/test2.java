import com.google.gson.Gson;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import java.util.HashMap;
import java.util.Map;

public class test2 {

    public static void main(String[] args) {

        Map<String,Long> myMap=new HashMap<>();
        myMap.put("1",1L);
        myMap.put("2",2L);
        myMap.put("3",3L);
        myMap.put("4",4L);

        JsonObjectBuilder retVal = Json.createObjectBuilder();
        //retVal.build();
        myMap.keySet().stream().forEach((key)->retVal.add(key,myMap.get(key)));

        JsonObjectBuilder tweetStatusObjectBuilder = Json.createObjectBuilder();

        tweetStatusObjectBuilder.add("mymap",retVal);
       // tweetStatusObjectBuilder.build();



        System.out.println(tweetStatusObjectBuilder.build().toString());


    }
}
