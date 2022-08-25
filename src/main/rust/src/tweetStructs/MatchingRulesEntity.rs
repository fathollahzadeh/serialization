use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct MatchingRulesEntity {
	tag: Option<String>,
	id: i64,
	id_str: Option<String>,
}
