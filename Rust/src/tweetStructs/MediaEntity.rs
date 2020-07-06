use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct MediaEntity {
    display_url: String ,
    expanded_url: String ,
    id: i64 ,
    indices: Option<Vec<i64>>,
    media_url: String ,
    media_url_https: String ,
    //TODO
    //sizes: MediaSizesEntity,
    types: Option<String> ,
    source_status_id: Option<i64> ,
    source_status_id_str: Option<String> ,
    url: String ,
    //TODO:
    //video_info: VideoEntity,
    //additional_media_info: AdditionalMediaInfoEntity

}