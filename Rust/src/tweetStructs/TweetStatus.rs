use serde::{Serialize, Deserialize};
use crate::tweetStructs::User::User;
use crate::tweetStructs::Coordinates::Coordinates;
use crate::tweetStructs::Place::Place;
use crate::tweetStructs::Entities::Entities;
use crate::tweetStructs::ExtendedEntities::ExtendedEntities;
use std::collections::HashMap;
use crate::tweetStructs::MatchingRulesEntity::MatchingRulesEntity;


#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct TweetStatus {
    created_at: String ,
    id: i64,
    text: Option<String>,
    source: Option<String>,
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
    matching_rules: Option<Vec<MatchingRulesEntity>>,
    current_user_retweet: Option<i64> ,
    scopes: Option<HashMap<String,bool>>,
    withheld_copyright: Option<bool> ,
    withheld_in_countries:Option<Vec<String>>,
    withheld_scope: Option<String>
}

