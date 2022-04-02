package at.tugraz.util;

import java.io.Serializable;
import java.util.List;
import com.esotericsoftware.kryo.Kryo;

public interface RootData extends Serializable, Comparable<RootData> {

	List<RootData> generateObjects(int number);

	byte[] javaDefaultSerialization();

	RootData javaDefaultDeserialization(byte[] buf);

	byte[] jsonSerialization();

	RootData jsonDeserialization(byte[] buf);

	byte[] jsonSerialization_withGZIP();

	RootData jsonDeserialization_withGZIP(byte[] buf);

	byte[] protocolBufferWrite();

	RootData protocolBufferRead(byte[] buf);

	byte[] kryoSerialization(Kryo kryo);

	RootData kryoDeserialization(byte[] buf, Class<?> myclass, Kryo kryo);

	byte[] writeByteBuffer();

	RootData readByteBuffer(byte[] buffData);

	byte[] bsonSerialization();

	RootData bsonDeSerialization(byte[] buffData);

	public byte[] gsonSerialization();

	//public TweetStatus gsonDeSerialization(byte[] buff);

	String toString();

}
