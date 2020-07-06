use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct BoundingBoxCoordinate {
    types:  Option<String> ,
    coordinates: Option<Vec<Vec<Vec<f64>>>>
}