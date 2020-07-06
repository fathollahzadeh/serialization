use serde::{Serialize, Deserialize};
use crate::tweetStructs::BoundingBoxCoordinate::BoundingBoxCoordinate;

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Place {
    name: String ,
    country_code: String ,
    id: String ,
    country: String ,
    place_type: String ,
    url: String ,
    full_name: String ,
    bounding_box: Option<BoundingBoxCoordinate>
}