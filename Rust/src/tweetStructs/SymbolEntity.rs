use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct SymbolEntity {
    indices: Option<Vec<i64>>,
    text: String
}