use serde::{Serialize, Deserialize};
use crate::tweetStructs::HashtagEntity::HashtagEntity;
use crate::tweetStructs::PollEntity::PollEntity;
use crate::tweetStructs::SymbolEntity::SymbolEntity;
use crate::tweetStructs::UserMentionEntity::UserMentionEntity;
use crate::tweetStructs::URLEntity::URLEntity;
use crate::tweetStructs::MediaEntity::MediaEntity;

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Entities {
    hashtags: Option<Vec<HashtagEntity>>,
    media: Option<Vec<MediaEntity>>,
    urls: Option<Vec<URLEntity>>,
    user_mentions: Option<Vec<UserMentionEntity>>,
    symbols: Option<Vec<SymbolEntity>>,
    polls: Option<Vec<PollEntity>>,
}