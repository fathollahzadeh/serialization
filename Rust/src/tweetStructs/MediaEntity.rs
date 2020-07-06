use serde::{Serialize, Deserialize};
use crate::tweetStructs::MediaSizesEntity::MediaSizesEntity;
use crate::tweetStructs::VideoEntity::VideoEntity;
use crate::tweetStructs::AdditionalMediaInfoEntity::AdditionalMediaInfoEntity;

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct MediaEntity {
    display_url: String ,
    expanded_url: String ,
    id: i64 ,
    indices: Option<Vec<i64>>,
    media_url: String ,
    media_url_https: String ,
    sizes: Option<MediaSizesEntity>,
    types: Option<String> ,
    source_status_id: Option<i64> ,
    source_status_id_str: Option<String> ,
    url: String ,
    video_info: Option<VideoEntity>,
    additional_media_info: Option<AdditionalMediaInfoEntity>
}