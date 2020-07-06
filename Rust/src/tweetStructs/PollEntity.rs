use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct PollEntity {
    //TODO
    //options: List,
    end_datetime: String ,
    duration_minutes: String
}