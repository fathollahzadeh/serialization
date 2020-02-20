package edu.bu.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;

import com.esotericsoftware.kryo.Kryo;
import edu.bu.tweet.*;


public class KryoSinglton {
	
    static class SingletonHolder {
    	static 	final KryoSinglton instance = new KryoSinglton();
    }
    
    
    public static KryoSinglton getInstance() {
		return SingletonHolder.instance;

    }
    
    public  Kryo getKryo() {
		return kryo;
	}


	private Kryo kryo;

    private KryoSinglton() {
    	kryo = new Kryo();
    	
    	kryo.register(LinkedHashMap.class);
    	
    	kryo.register(long.class);
    	kryo.register(Long.class);
    	kryo.register(Integer.class);
    	kryo.register(ArrayList.class);
		kryo.register(HashMap.class);
		kryo.register(double.class);
		kryo.register(double[].class);
		kryo.register(com.google.gson.internal.LinkedTreeMap.class);

		kryo.register(AdditionalMediaInfoEntity.class);
		kryo.register(BoundingBoxCoordinate.class);
		kryo.register(Coordinates.class);
		kryo.register(Entities.class);
		kryo.register(ExtendedEntities.class);
		kryo.register(HashtagEntity.class);
		kryo.register(MatchingRulesEntity.class);
		kryo.register(MediaEntity.class);
		kryo.register(MediaSizesEntity.class);
		kryo.register(OptionEntity.class);
		kryo.register(Place.class);
		kryo.register(PollEntity.class);
		kryo.register(SizeEntity.class);
		kryo.register(SymbolEntity.class);
		kryo.register(TweetStatus.class);
		kryo.register(URLEntity.class);
		kryo.register(User.class);
		kryo.register(UserMentionEntity.class);
		kryo.register(VariantEntity.class);
		kryo.register(VideoEntity.class);
		
	}
}
