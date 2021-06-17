use serde::{Serialize, Deserialize};
use crate::tweetStructs::SizesEntity::SizeEntity;

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct MediaSizesEntity {
	thumb: Option<SizeEntity>,
	large: Option<SizeEntity>,
	medium: Option<SizeEntity>,
	small: Option<SizeEntity>,
}
