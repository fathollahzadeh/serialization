package at.tugraz.datamodel.twitter;

import java.util.List;
import java.util.Map;

import at.tugraz.util.KryoSingleton;
import at.tugraz.util.RootObject;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class TweetStatus extends RootObject {

	static Logger logger = LogManager.getLogger(TweetStatus.class);
	private String created_at;
	private long id;
	private String text;
	private String source;
	private boolean truncated;
	private long in_reply_to_status_id;//nullable
	private long in_reply_to_user_id;//nullable
	private String in_reply_to_screen_name;//nullable
	private User user;
	private Coordinates coordinates;//nullable
	private Place place;//nullable
	private long quoted_status_id;
	private boolean is_quote_status;
	private TweetStatus quoted_status;
	private TweetStatus retweeted_status;
	private int quote_count;//nullable
	private int reply_count;
	private int retweet_count;
	private int favorite_count;//nullable
	private Entities entities;
	private ExtendedEntities extended_entities;
	private boolean favorited;//nullable
	private boolean retweeted;
	private boolean possibly_sensitive;//nullable
	private String filter_level;
	private String lang;//nullable
	private List<MatchingRulesEntity> matching_rules;
	private long current_user_retweet;//nullable
	private Map<String, Boolean> scopes;//nullable
	private boolean withheld_copyright;//nullable
	private List<String> withheld_in_countries;//nullable
	private String withheld_scope;//nullable

	@Override public KryoSingleton getKryoInstance() {
		return KryoSingletonTweet.getInstance();
	}
}
