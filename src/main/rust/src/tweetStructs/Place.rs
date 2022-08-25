use serde::{Serialize, Deserialize};
use crate::tweetStructs::BoundingBoxCoordinate::BoundingBoxCoordinate;

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Place {
	name: Option<String>,
	country_code: Option<String>,
	id: Option<String>,
	country: Option<String>,
	place_type: Option<String>,
	url: Option<String>,
	full_name: Option<String>,
	bounding_box: Option<BoundingBoxCoordinate>,
}
