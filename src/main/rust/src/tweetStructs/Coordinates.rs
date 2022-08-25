use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Coordinates {
	types: Option<String>,
	coordinates: Option<Vec<f64>>,
}
