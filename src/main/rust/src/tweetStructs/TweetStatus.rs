use serde::{Serialize, Deserialize};
use crate::tweetStructs::User::User;
use crate::tweetStructs::Coordinates::Coordinates;
use crate::tweetStructs::Place::Place;
use crate::tweetStructs::Entities::Entities;
use crate::tweetStructs::ExtendedTweet::ExtendedTweet;
use std::collections::HashMap;
use crate::tweetStructs::MatchingRulesEntity::MatchingRulesEntity;
use std::cmp::Ordering;

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct TweetStatus {
	created_at: String,
	id: i64,
	id_str:String,
	text: Option<String>,
	source: Option<String>,
	truncated: bool,
	in_reply_to_status_id: Option<i64>,
	in_reply_to_user_id: Option<i64>,
	in_reply_to_screen_name: Option<String>,
	user: User,
	coordinates: Option<Coordinates>,
	place: Option<Place>,
	quoted_status_id: Option<i64>,
	is_quote_status: bool,
	quoted_status: Option<Box<TweetStatus>>,
	retweeted_status: Option<Box<TweetStatus>>,
	quote_count: Option<i32>,
	reply_count: Option<i32>,
	retweet_count: i32,
	favorite_count: Option<i32>,
	entities: Entities,
	extended_tweet:Option<ExtendedTweet>,
	favorited: Option<bool>,
	retweeted: bool,
	possibly_sensitive: Option<bool>,
	filter_level: Option<String>,
	lang: Option<String>,
	matching_rules: Option<Vec<MatchingRulesEntity>>,
	current_user_retweet: Option<i64>,
	scopes: Option<HashMap<String, bool>>,
	withheld_copyright: Option<bool>,
	withheld_in_countries: Option<Vec<String>>,
	withheld_scope: Option<String>,
	display_text_range:Option<Vec<u32>>
}

impl TweetStatus {
	pub fn getOrder(&self) -> usize {
		let mut count_level: usize = 0;

		// get text
		if self.text.is_some() {
			count_level += self.text.as_ref().unwrap().len();
		}
		// get QuoteStatus
		if self.quoted_status.is_some() {
			if self.quoted_status.as_ref().unwrap().text.as_ref().is_some() {
				count_level += self.quoted_status.as_ref().unwrap().text.as_ref().unwrap().len();
			}
		}
		// get Retweet
		if self.retweeted_status.is_some() {
			count_level += self.retweeted_status.as_ref().unwrap().retweet_count as usize;
		}
		return count_level;
	}

	pub fn getId(&self) -> i64 {
		return self.id;
	}


	pub fn set_id(&mut self, id: i64) {
		self.id = id;
	}
}

impl Ord for TweetStatus {
	fn cmp(&self, other: &Self) -> Ordering {
		self.getOrder().cmp(&other.getOrder())
	}
}

impl PartialOrd for TweetStatus {
	fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
		Some(self.cmp(other))
	}
}

impl PartialEq for TweetStatus {
	fn eq(&self, other: &Self) -> bool {
		self.getOrder() == other.getOrder()
	}
}

impl Eq for TweetStatus {}

