package at.tugraz.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;

import at.tugraz.tweet.*;
import at.tugraz.tweet.flatbuffers.*;
import at.tugraz.tweet.proto.TweetStatusProtos;
import com.esotericsoftware.kryo.Kryo;

public class KryoSinglton {

	public Kryo getKryo() {
		return kryo;
	}

	private Kryo kryo;

	public KryoSinglton() {
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
		kryo.register(ExtendedTweet.class);
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

		kryo.register(AdditionalMediaInfoEntityFBS.class);
		kryo.register(BoundingBoxCoordinateFBS.class);
		kryo.register(CoordinatesFBS.class);
		kryo.register(EntitiesFBS.class);
		kryo.register(ExtendedEntitiesFBS.class);
		kryo.register(HashtagEntityFBS.class);
		kryo.register(MatchingRulesEntityFBS.class);
		kryo.register(MediaEntityFBS.class);
		kryo.register(MediaSizesEntityFBS.class);
		kryo.register(OptionEntityFBS.class);
		kryo.register(PlaceFBS.class);
		kryo.register(PollEntityFBS.class);
		kryo.register(SizeEntityFBS.class);
		kryo.register(SymbolEntityFBS.class);
		kryo.register(TweetStatusFBS.class);
		kryo.register(URLEntityFBS.class);
		kryo.register(UserFBS.class);
		kryo.register(UserMentionEntityFBS.class);
		kryo.register(VariantEntityFBS.class);
		kryo.register(VideoEntityFBS.class);

		kryo.register(TweetStatusProtos.TweetStatusP.class);

	}
}
