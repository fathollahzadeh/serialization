package edu.rice.pdb.serialization;

import java.util.LinkedHashMap;

import com.esotericsoftware.kryo.Kryo;

import edu.bu.tweet.Coordinates;
import edu.bu.tweet.Entities;
import edu.bu.tweet.ExtendedEntities;
import edu.bu.tweet.HashtagEntity;
import edu.bu.tweet.MediaEntity;
import edu.bu.tweet.MediaSizesEntity;
import edu.bu.tweet.Place;
import edu.bu.tweet.SizeEntity;
import edu.bu.tweet.SymbolEntity;
import edu.bu.tweet.TweetStatus;
import edu.bu.tweet.URLEntity;
import edu.bu.tweet.User;
import edu.bu.tweet.UserMentionEntity;
import edu.bu.tweet.VariantEntity;

import edu.rice.dmodel.Customer;
import edu.rice.dmodel.Element;
import edu.rice.dmodel.LineItem;
import edu.rice.dmodel.Order;
import edu.rice.dmodel.Part;
import edu.rice.dmodel.Supplier;

public class KryoObject {

	public Kryo getKryo() {
		return kryo;
	}

	private Kryo kryo;

	public KryoObject() {
		kryo = new Kryo();

		kryo.register(LinkedHashMap.class);

		kryo.register(long.class);
		kryo.register(Long.class);
		kryo.register(Integer.class);

		kryo.register(Element.class);
		kryo.register(Supplier.class);
		kryo.register(Part.class);
		kryo.register(LineItem.class);
		kryo.register(Order.class);
		kryo.register(Customer.class);

		//kryo.register(BoundingBox.class);
		kryo.register(Coordinates.class);
		kryo.register(Entities.class);
		kryo.register(ExtendedEntities.class);
		//kryo.register(GenerateTweetData.class);
		kryo.register(HashtagEntity.class);
		kryo.register(MediaEntity.class);
		kryo.register(MediaSizesEntity.class);
		kryo.register(Place.class);
		//kryo.register(RateLimitStatus.class);
		kryo.register(SizeEntity.class);
		kryo.register(SymbolEntity.class);
		kryo.register(TweetStatus.class);
		kryo.register(URLEntity.class);
		kryo.register(User.class);
		kryo.register(UserMentionEntity.class);
		kryo.register(VariantEntity.class);

	}
}
