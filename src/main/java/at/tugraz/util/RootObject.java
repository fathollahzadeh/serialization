package at.tugraz.util;

import java.io.Serializable;

public abstract class RootObject {

	public KryoSingleton getKryoInstance(){
		return null;
	}

	//byte[] javaDefaultSerialization(); T
	//RootObject javaDefaultDeserialization(byte[] buf);

	//	byte[] jsonSerialization();
	//	RootData jsonDeserialization(byte[] buf);
	//----------------------------------------------
//	List<RootData> generateObjects(int number);
//

//
//	byte[] jsonSerialization_withGZIP();
//
//	RootData jsonDeserialization_withGZIP(byte[] buf);
//
//	byte[] protocolBufferWrite();
//
//	RootData protocolBufferRead(byte[] buf);
//
//	byte[] kryoSerialization(Kryo kryo);
//
//	RootData kryoDeserialization(byte[] buf, Class<?> myclass, Kryo kryo);
//
//	byte[] writeByteBuffer();
//
//	RootData readByteBuffer(byte[] buffData);
//
//	byte[] bsonSerialization();
//
//	RootData bsonDeSerialization(byte[] buffData);
//
//	public byte[] gsonSerialization();
//
//	//public TweetStatus gsonDeSerialization(byte[] buff);
//
//	String toString();
}
