package at.tugraz.io;

import at.tugraz.util.RootObject;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.nio.charset.Charset;

public class SerializerGson extends Serializer {

	public SerializerGson(String fileName) {
		super(fileName);
	}

	@Override public void writeToFile(RootObject object) {
		Gson gson = new GsonBuilder().create();
		byte[] buf = gson.toJson(this).getBytes(Charset.forName("UTF-8"));
		this.writeToFile(buf);
	}
}
