use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct OptionEntity {
    position: Option<i32> ,
    text: Option<String>
}