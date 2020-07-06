use serde::{Serialize, Deserialize};
use crate::tweetStructs::User::User;
use crate::tweetStructs::Coordinates::Coordinates;
use crate::tweetStructs::Place::Place;
use crate::tweetStructs::Entities::Entities;
use crate::tweetStructs::ExtendedEntities::ExtendedEntities;


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
    user: User,
    coordinates: Option<Coordinates>,
    place: Option<Place>,
    quoted_status_id: Option<i64> ,
    is_quote_status: bool ,
    quoted_status: Option<Box<TweetStatus>>,
    retweeted_status: Option<Box<TweetStatus>>,
    quote_count: Option<i32> ,
    reply_count: Option<i32> ,
    retweet_count: i32 ,
    favorite_count: Option<i32> ,
    entities: Entities,
    extended_entities: Option<ExtendedEntities>,
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
    withheld_in_countries:Option<Vec<String>>,
    withheld_scope: Option<String>
}

