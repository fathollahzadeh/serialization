package at.tugraz.io;

import at.tugraz.objects.twitter.TweetStatus;
import at.tugraz.util.Const;
import at.tugraz.util.RootObject;
import com.google.gson.Gson;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;

public class ReaderTextJSONTweet extends ReaderText {

	@Override public ArrayList<RootObject> getObjects(String fileName) {
		Gson gson = new Gson();
		try(BufferedReader br = new BufferedReader(new FileReader(fileName, StandardCharsets.UTF_8))) {
			String line;
			while((line = br.readLine()) != null) {
				TweetStatus tweetStatus = gson.fromJson(line, TweetStatus.class);
				objects.add(tweetStatus);
			}
		}
		catch(IOException e) {
			e.printStackTrace();
		}
		return objects;
	}
}
