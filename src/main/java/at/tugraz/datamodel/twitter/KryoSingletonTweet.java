package at.tugraz.datamodel.twitter;

import at.tugraz.util.KryoSingleton;
import com.esotericsoftware.kryo.Kryo;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;

public class KryoSingletonTweet extends KryoSingleton {

	static class SingletonHolder {
		static final KryoSingletonTweet instance = new KryoSingletonTweet();
	}

	public static KryoSingletonTweet getInstance() {
		return SingletonHolder.instance;
	}

	private KryoSingletonTweet() {
		kryo = new Kryo();

		kryo.register(LinkedHashMap.class);

		kryo.register(ArrayList.class);
		kryo.register(HashMap.class);
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
