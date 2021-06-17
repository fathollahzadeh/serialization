use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct UserMentionEntity {
	id: Option<i64>,
	id_str: Option<String>,
	indices: Option<Vec<i64>>,
	name: Option<String>,
	screen_name: Option<String>,
}
