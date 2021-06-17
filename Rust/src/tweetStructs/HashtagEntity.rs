use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct HashtagEntity {
	indices: Option<Vec<i64>>,
	text: Option<String>,
}
