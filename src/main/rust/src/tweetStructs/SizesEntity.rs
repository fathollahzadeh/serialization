use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct SizeEntity {
	w: Option<i32>,
	h: Option<i32>,
	resize: Option<String>,
}
