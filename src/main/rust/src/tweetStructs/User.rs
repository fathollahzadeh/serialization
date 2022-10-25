use serde::{Serialize, Deserialize};
use crate::tweetStructs::URLEntity::URLEntity;

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct User {
	id: i64,
	id_str:String,
	name: String,
	screen_name: Option<String>,
	location: Option<String>,
	url: Option<String>,
	description: Option<String>,
	protected: bool,
	verified: bool,
	followers_count: i32,
	friends_count: i32,
	listed_count: i32,
	favourites_count: i32,
	statuses_count: i32,
	created_at: Option<String>,
	profile_banner_url: Option<String>,
	profile_image_url_https: String,
	default_profile: bool,
	withheld_in_countries: Option<Vec<String>>,
	withheld_scope: Option<String>,
	descriptionURLEntities: Option<URLEntity>,
	geo_enabled: Option<bool>,
	lang: Option<String>,
	contributors_enabled: Option<bool>,
	profile_background_color: Option<String>,
	profile_background_image_url: Option<String>,
	profile_background_image_url_https: Option<String>,
	profile_background_tile: Option<bool>,
	profile_image_url: Option<String>,
	profile_link_color: Option<String>,
	profile_sidebar_border_color: Option<String>,
	profile_sidebar_fill_color: Option<String>,
	profile_text_color: Option<String>,
	profile_use_background_image: Option<bool>,
	utc_offset: Option<i32>,
	time_zone: Option<String>,
	is_translator: Option<bool>,
	follow_request_sent: Option<bool>,
	showAllInlineMedia: Option<bool>,
}
