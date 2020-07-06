use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct VariantEntity {
    bitrate: Option<i64> ,
    content_type: Option<String> ,
    url: Option<String>
}