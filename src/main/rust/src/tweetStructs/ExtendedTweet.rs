use serde::{Serialize, Deserialize};
use crate::tweetStructs::Entities::Entities;
use crate::tweetStructs::ExtendedEntities::ExtendedEntities;

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct ExtendedTweet {
	full_text: Option<String>,
	display_text_range: Option<Vec<u32>>,
	entities: Entities,
	extended_entities: Option<ExtendedEntities>
}
