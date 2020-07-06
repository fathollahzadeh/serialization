use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Place {
    name: String ,
    country_code: String ,
    id: String ,
    country: String ,
    place_type: String ,
    url: String ,
    full_name: String ,

   //TODO
   // bounding_box: BoundingBoxCoordinate,
}