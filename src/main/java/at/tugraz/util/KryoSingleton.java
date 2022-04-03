package at.tugraz.util;

import com.esotericsoftware.kryo.Kryo;

public abstract class KryoSingleton {

	protected Kryo kryo;
	public Kryo getKryo() {
		return kryo;
	}
}
