use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct SizeEntity {
	width: Option<i32>,
	height: Option<i32>,
	resize: Option<String>,
}
