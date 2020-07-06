use serde::{Serialize, Deserialize};
#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct TweetStatus {
    created_at: String ,
    id: i64,
    text: String,
    source: String,
    truncated: bool,
    in_reply_to_status_id: Option<i64>,
    in_reply_to_user_id: Option<i64> ,
    in_reply_to_screen_name: Option<String> ,
   // user: User,
   // coordinates: Coordinates,
   // place: Place,
    quoted_status_id: Option<i64> ,
    is_quote_status: bool ,
    //quoted_status: TweetStatus,
    //retweeted_status: weetStatus,
    quote_count: Option<i32> ,
    reply_count: Option<i32> ,
    retweet_count: i32 ,
    favorite_count: Option<i32> ,
   // entities: Entities,
    //extended_entities: ExtendedEntities,
    favorited: Option<bool> ,
    retweeted: bool ,
    possibly_sensitive: Option<bool> ,
    filter_level: Option<String> ,
    lang: Option<String> ,
    //matching_rules: List,
    current_user_retweet: Option<i64> ,
    //TODO
    //scopes: Map,
    withheld_copyright: Option<bool> ,
  //TODO
  //  withheld_in_countries: List,
    withheld_scope: Option<String>
}

