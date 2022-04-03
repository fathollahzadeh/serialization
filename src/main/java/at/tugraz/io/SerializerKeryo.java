package at.tugraz.io;

import at.tugraz.util.RootObject;
import com.esotericsoftware.kryo.io.Output;

import java.io.ByteArrayOutputStream;

public class SerializerKeryo extends Serializer {

	public SerializerKeryo(String fileName) {
		super(fileName);
	}

	@Override public void writeToFile(RootObject object) {
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		Output output = new Output(bos);
		object.getKryoInstance().getKryo().writeObject(output, object);
		output.flush();
		byte[] buf = bos.toByteArray();
		this.writeToFile(buf);
	}
}
