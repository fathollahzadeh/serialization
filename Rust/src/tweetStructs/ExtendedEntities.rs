use serde::{Serialize, Deserialize};
use crate::tweetStructs::MediaEntity::MediaEntity;

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct ExtendedEntities {
	media: Option<Vec<MediaEntity>>,
}
