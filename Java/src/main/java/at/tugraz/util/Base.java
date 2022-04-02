package at.tugraz.util;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectOutput;
import java.io.ObjectOutputStream;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

import org.apache.log4j.Logger;

import com.esotericsoftware.kryo.Kryo;
import com.esotericsoftware.kryo.io.Input;
import com.esotericsoftware.kryo.io.Output;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import at.tugraz.tweet.TweetStatus;

public class Base {

	static Logger logger = Logger.getLogger(Base.class);

	public byte[] javaDefaultSerialization() {
		// Serialize to a byte array
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		ObjectOutput out = null;
		try {
			out = new ObjectOutputStream(bos);
			// here do the serialization
			out.writeObject(this);
			out.close();
		}
		catch(IOException e) {
			logger.error("Class I/O erro", e);
		}

		// Get the bytes of the serialized object
		byte[] buf = bos.toByteArray();
		return buf;
	}

	public byte[] kryoSerialization(Kryo kryo) {

		ByteArrayOutputStream bos = new ByteArrayOutputStream();

		Output output = new Output(bos);

		kryo.writeObject(output, this);

		output.flush();

		byte[] buf = bos.toByteArray();

		return buf;
	}

	public RootData kryoDeserialization(byte[] buf, Class<?> myclass, Kryo kryo) {

		ByteArrayInputStream byteInputStream = new ByteArrayInputStream(buf);

		Input input = new Input(byteInputStream);

		return (RootData) kryo.readObject(input, myclass);

	}

	public String extractString(ByteBuffer byteBuffer, int stringSize) {
		byte[] stringBytes = new byte[stringSize];
		byteBuffer.get(stringBytes, 0, stringSize);

		String mystring = new String(stringBytes, Charset.forName("UTF-8"));
		return mystring;
	}
	public byte[] gZIPCompression(byte[] dataToCompress) {

		ByteArrayOutputStream byteStream = new ByteArrayOutputStream(dataToCompress.length);

		try {
			GZIPOutputStream zipStream = new GZIPOutputStream(byteStream);

			try {
				zipStream.write(dataToCompress);
			}
			finally {
				zipStream.close();
			}

		}
		catch(IOException e) {
			logger.error("gZIPCompression: ", e);
		}

		return byteStream.toByteArray();
	}

	public byte[] gZIP_DE_Compression(byte[] dataToDECompress) {
		ByteArrayOutputStream out = null;
		InputStream in = null;
		ByteArrayInputStream zipStream = new ByteArrayInputStream(dataToDECompress);

		try {
			out = new ByteArrayOutputStream();
			in = new GZIPInputStream(zipStream);
			byte[] buffer = new byte[4096];
			int c = 0;

			while((c = in.read(buffer, 0, 4096)) > 0) {
				out.write(buffer, 0, c);
			}

		}
		catch(IOException e) {
			e.printStackTrace();
		}
		finally {
			if(in != null) {
				try {
					in.close();
				}
				catch(IOException e) {
					e.printStackTrace();
				}
			}
			if(out != null) {
				try {
					out.close();
				}
				catch(IOException e) {
					e.printStackTrace();
				}
			}
		}

		return out.toByteArray();
	}

	/**
	 * Convert this object to JSON object using Google gson
	 * We convert the text to byte array and return.
	 *
	 * @return
	 */
	public byte[] gsonSerialization() {
		Gson gson = new GsonBuilder().create();

		return gson.toJson(this).getBytes(Charset.forName("UTF-8"));
	}

	/**
	 * Deserialize a buffer to a TweetStatus Object
	 *
	 * @param buff byte array as buffer .
	 * @return a TweetStatus object.
	 */
	public TweetStatus gsonDeSerialization(byte[] buff) {
		Gson gson = new GsonBuilder().create();

		String jsonString = new String(buff);

		return gson.fromJson(jsonString, TweetStatus.class);
	}

	public static byte convertToByte(boolean value) {
		return (byte) (value ? 1 : 0);
	}

	public static byte convertToByte(Boolean value) {
		return (byte) (value == null ? 2 : (value ? 1 : 0));
	}

	public static boolean convertToBoolean(byte value) {
		return value > 0;
	}

	public static Boolean convertToBoolean1(byte value) {
		return value == 2 ? null : value > 0;
	}

}
