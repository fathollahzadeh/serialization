use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct URLEntity {
    indices: Option<Vec<i64>>,
    display_url: Option<String> ,
    expanded_url: Option<String> ,
    url: Option<String>
}