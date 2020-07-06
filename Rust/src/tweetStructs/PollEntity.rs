use serde::{Serialize, Deserialize};
use crate::tweetStructs::OptionEntity::OptionEntity;

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct PollEntity {
    options: Option<Vec<OptionEntity>>,
    end_datetime: String ,
    duration_minutes: String
}