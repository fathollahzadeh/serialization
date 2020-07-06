use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct UserMentionEntity {
    id: i64 ,
    id_str: String ,
    indices: Option<Vec<i64>>,
    name: String ,
    screen_name: String
}