use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Coordinates {

    //TODO type is a keyboard in Rust
    types: Option<String>,
    coordinates: Option<Vec<f64>>
}