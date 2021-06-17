use serde::{Serialize, Deserialize};
use crate::tweetStructs::VariantEntity::VariantEntity;

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct VideoEntity {
	aspect_ratio: Option<Vec<i64>>,
	duration_millis: Option<i32>,
	variants: Option<Vec<VariantEntity>>,
}
