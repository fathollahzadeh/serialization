use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct URLEntity {
    indices: Option<Vec<i64>>,
    display_url: String ,
    expanded_url: String ,
    url: String
}