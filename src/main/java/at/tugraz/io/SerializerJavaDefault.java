package at.tugraz.io;

import at.tugraz.util.RootObject;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutput;
import java.io.ObjectOutputStream;

public  class SerializerJavaDefault extends Serializer {
	static Logger logger = LogManager.getLogger(SerializerJavaDefault.class);

	public SerializerJavaDefault(String fileName) {
		super(fileName);
	}

	@Override public void writeToFile(RootObject object) {
		// Serialize to a byte array
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		ObjectOutput out = null;
		try {
			out = new ObjectOutputStream(bos);
			// here do the serialization
			out.writeObject(object);
			out.close();
		}
		catch(IOException e) {
			logger.error("Class I/O erro", e);
		}

		// Get the bytes of the serialized object
		byte[] buf = bos.toByteArray();
		this.writeToFile(buf);
	}
}
