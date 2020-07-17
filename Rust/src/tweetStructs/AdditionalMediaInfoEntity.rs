use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct AdditionalMediaInfoEntity {
    title: Option<String> ,
    description: Option<String> ,
    embeddable: Option<bool> ,
    monetizable: Option<bool>
}