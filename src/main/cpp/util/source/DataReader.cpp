#include "DataReader.h"

DataReader::DataReader() {}


DataReader::~DataReader() {}


TweetStatus *DataReader::generateTweetObject(Document &d) {

    string createdAt = d["created_at"].GetString();
    long id = d["id"].GetInt64();
    string idStr = d["id_str"].GetString();
    string text = d["text"].GetString();
    string source = d["source"].GetString();
    bool isTruncated = d["truncated"].GetBool();
    long inReplyToStatusId = d.HasMember("in_reply_to_status_id") && d["in_reply_to_status_id"].IsInt64()
                             ? d["in_reply_to_status_id"].GetInt64() : -1;
    long inReplyToUserId = d.HasMember("in_reply_to_user_id") && d["in_reply_to_user_id"].IsInt64()
                           ? d["in_reply_to_user_id"].GetInt64() : -1;
    string inReplyToScreenName = d.HasMember("in_reply_to_screen_name") && !d["in_reply_to_screen_name"].IsNull()
                                 ? d["in_reply_to_screen_name"].GetString() : "";
    long quotedStatusId =
            d.HasMember("quoted_status_id") && d["quoted_status_id"].IsInt64() ? d["quoted_status_id"].GetInt64() : -1;
    bool isQuoteStatus = d["is_quote_status"].GetBool();
    int quoteCount = d.HasMember("quote_count") && d["quote_count"].IsInt() ? d["quote_count"].GetInt() : -1;
    int replyCount = d.HasMember("reply_count") && d["reply_count"].IsInt() ? d["reply_count"].GetInt() : -1;
    int retweetCount = d["retweet_count"].GetInt();
    int favoriteCount =
            d.HasMember("favorite_count") && d["favorite_count"].IsInt() ? d["favorite_count"].GetInt() : -1;
    bool isFavorited = d.HasMember("favorited") && d["favorited"].IsBool() ? d["favorited"].GetBool() : false;
    bool isRetweeted = d["retweeted"].GetBool();
    bool isPossiblySensitive =
            d.HasMember("possibly_sensitive") && d["possibly_sensitive"].IsBool() ? d["possibly_sensitive"].GetBool()
                                                                                  : false;


    string filterLevel =
            d.HasMember("filter_level") && !d["filter_level"].IsNull() ? d["filter_level"].GetString() : "";
    string lang = d.HasMember("lang") && !d["lang"].IsNull() ? d["lang"].GetString() : "";

    vector<MatchingRulesEntity *> matchingRules;
    if (d.HasMember("matching_rules") && d["matching_rules"].IsNull()) {
        matchingRules = getMatchingRulesEntity(d["matching_rules"]);
    }

    long currentUserRetweetId = -1;
    if (d.HasMember("current_user_retweet")) {
        currentUserRetweetId = d["current_user_retweet"]["id"].GetInt64();
    }
    map<string, bool> scopes;
    if (d.HasMember("scopes")) {
        rapidjson::Value &membersObject = d["scopes"];
        for (rapidjson::Value::ConstMemberIterator it = membersObject.MemberBegin();
             it != membersObject.MemberEnd(); it++) {
            scopes[it->name.GetString()] = it->value.GetBool();
        }
    }


    bool withheldCopyright =
            d.HasMember("withheld_copyright") && d["withheld_copyright"].IsBool() ? d["withheld_copyright"].GetBool()
                                                                                  : false;
    string withheldScope =
            d.HasMember("withheld_scope") && !d["withheld_scope"].IsNull() ? d["withheld_scope"].GetString() : "";

    vector<string> withheldInCountries;
    if (d.HasMember("withheld_in_countries")) {
        for (SizeType i = 0; i < d["withheld_in_countries"].Size(); i++) {
            withheldInCountries.push_back(d["withheld_in_countries"][i].GetString());
        }
    }

    Entities *entities = nullptr;
    if (d.HasMember("entities") && !d["entities"].IsNull()) {
        entities = getEntities(d["entities"]);
    }

    ExtendedTweet *extendedTweet = nullptr;
    if (d.HasMember("extended_tweet") && !d["extended_tweet"].IsNull()) {
        extendedTweet = getExtendedTweet(d["extended_tweet"]);
    }

    Coordinates *coordinates = nullptr;
    if (d.HasMember("coordinates") && !d["coordinates"].IsNull()) {
        coordinates = getCoordinates(d["coordinates"]);
    }

    Place *place = nullptr;
    if (d.HasMember("place") && !d["place"].IsNull()) {
        place = getPlace(d["place"]);
    }


    TweetStatus *quotedStatus = nullptr;
    if (d.HasMember("quoted_status") && !d["quoted_status"].IsNull()) {
        Document dd;
        dd.CopyFrom(d["quoted_status"], dd.GetAllocator());
        quotedStatus = generateTweetObject(dd);
    }

    TweetStatus *retweetedStatus = nullptr;
    if (d.HasMember("retweeted_status") && !d["retweeted_status"].IsNull()) {
        Document dd;
        dd.CopyFrom(d["retweeted_status"], dd.GetAllocator());
        quotedStatus = generateTweetObject(dd);

    }
    User *user = getUser(d["user"]);

    vector<int> displayTextRange;
    if (d.HasMember("display_text_range")) {
        for (int i = 0; i < d["display_text_range"].Size(); ++i) {
            displayTextRange.push_back(d["display_text_range"][i].GetInt());
        }
    }
    return new TweetStatus(createdAt, id, idStr, text, source, isTruncated, inReplyToStatusId, inReplyToUserId,
                           inReplyToScreenName, user, coordinates, place, quotedStatusId, isQuoteStatus, quotedStatus,
                           retweetedStatus, quoteCount, replyCount, retweetCount, favoriteCount, entities,
                           extendedTweet, isFavorited, isRetweeted, isPossiblySensitive, filterLevel,
                           lang, matchingRules, currentUserRetweetId, scopes, withheldCopyright,
                           withheldInCountries, withheldScope, displayTextRange);
}


//Get entities from json string:

Entities *
DataReader::getEntities(Value &d) {
    vector<HashtagEntity *> hashtags;
    if (d.HasMember("hashtags") && !d["hashtags"].IsNull()) {

        for (SizeType i = 0; i < d["hashtags"].Size(); i++) {
            vector<int> indices;
            for (int j = 0; j < d["hashtags"][i]["indices"].Size(); ++j) {
                indices.push_back(d["hashtags"][i]["indices"][j].GetInt());
            }
            string text = d["hashtags"][i]["text"].GetString();
            HashtagEntity *hashtag = new HashtagEntity(indices, text);
            hashtags.push_back(hashtag);
        }
    }

    vector<MediaEntity *> media;
    if (d.HasMember("media") && !d["media"].IsNull()) {
        media = getMedia(d["media"]);
    }

    vector<URLEntity *> urls;
    if (d.HasMember("urls") && !d["urls"].IsNull()) {
        for (SizeType i = 0; i < d["urls"].Size(); i++) {

            vector<int> indices;
            for (int j = 0; j < d["urls"][i]["indices"].Size(); ++j) {
                indices.push_back(d["urls"][i]["indices"][j].GetInt());
            }
            string displayURL = d["urls"][i]["display_url"].GetString();
            string expandedURL = d["urls"][i]["expanded_url"].GetString();
            string url = d["urls"][i]["url"].GetString();
            URLEntity *urlEntity = new URLEntity(indices, displayURL, expandedURL, url);
            urls.push_back(urlEntity);
        }
    }

    vector<UserMentionEntity *> userMentions;
    if (d.HasMember("user_mentions") && !d["user_mentions"].IsNull()) {
        for (SizeType i = 0; i < d["user_mentions"].Size(); i++) {
            long id = -d["user_mentions"][i]["id"].IsInt64() ? d["user_mentions"][i]["id"].GetInt64() : -1;
            string idStr = d["user_mentions"][i].HasMember("id_str") && !d["user_mentions"][i]["id_str"].IsNull()
                           ? d["user_mentions"][i]["id_str"].GetString() : "";
            string name = !d["user_mentions"][i]["name"].IsNull() ? d["user_mentions"][i]["name"].GetString() : "";
            string screenName = d["user_mentions"][i]["screen_name"].GetString();

            vector<int> indices;
            for (int j = 0; j < d["user_mentions"][i]["indices"].Size(); ++j) {
                indices.push_back(d["user_mentions"][i]["indices"][j].GetInt());
            }
            UserMentionEntity *userMention = new UserMentionEntity(id, idStr, indices, name, screenName);
            userMentions.push_back(userMention);
        }
    }

    vector<SymbolEntity *> symbols;
    if (d.HasMember("symbols") && !d["symbols"].IsNull()) {
        for (SizeType i = 0; i < d["symbols"].Size(); i++) {

            vector<int> indices;
            for (int j = 0; j < d["symbols"][i]["indices"].Size(); ++j) {
                indices.push_back(d["symbols"][i]["indices"][j].GetInt());
            }
            string text = d["symbols"][i]["text"].GetString();
            SymbolEntity *symbol = new SymbolEntity(indices, text);
            symbols.push_back(symbol);
        }
    }

    vector<PollEntity *> polls;
    if (d.HasMember("polls") && !d["polls"].IsNull()) {
        for (SizeType i = 0; i < d["polls"].Size(); i++) {

            string endDatetime = d["polls"][i]["end_datetime"].GetString();
            string durationMinutes = d["polls"][i]["duration_minutes"].GetString();

            vector<OptionEntity *> options;
            for (SizeType j = 0; j < d["polls"][i]["options"].Size(); ++j) {
                int position = d["polls"][i]["options"][j]["position"].GetInt();
                string text = d["polls"][i]["options"][j]["text"].GetString();
                OptionEntity *option = new OptionEntity(position, text);
                options.push_back(option);
            }
            PollEntity *poll = new PollEntity(options, endDatetime, durationMinutes);
            polls.push_back(poll);
        }
    }

    Entities *entities = new Entities(hashtags, media, urls, userMentions, symbols, polls);
    return entities;

}

ExtendedTweet *DataReader::getExtendedTweet(Value &d) {
    string fullText = d.HasMember("full_text") && !d["full_text"].IsNull() ? d["full_text"].GetString() : "";
    vector<int> displayTextRange;
    if (d.HasMember("display_text_range")) {
        for (int i = 0; i < d["display_text_range"].Size(); ++i) {
            displayTextRange.push_back(d["display_text_range"][i].GetInt());
        }
    }
    ExtendedEntities *extendedEntities = nullptr;
    if (d.HasMember("extended_entities") && !d["extended_entities"].IsNull()) {
        if (d["extended_entities"].HasMember("media") && !d["media"]["extended_entities"].IsNull()) {
            extendedEntities = new ExtendedEntities(getMedia(d["extended_entities"]["media"]));
        }
    }

    Entities *entities = nullptr;
    if (d.HasMember("entities") && !d["entities"].IsNull()) {
        entities = getEntities(d["entities"]);
    }
    ExtendedTweet *extendedTweet = new ExtendedTweet(fullText, displayTextRange, entities, extendedEntities);
    return extendedTweet;
}

//Get user object from json string:
User *DataReader::getUser(Value &d) {
    long id = d["id"].GetInt64();
    string idStr = d["id_str"].GetString();
    string name = d["name"].GetString();
    string screenName = d.HasMember("screen_name") && !d["screen_name"].IsNull() ? d["screen_name"].GetString() : "";
    string location = d.HasMember("location") && !d["location"].IsNull() ? d["location"].GetString() : "";
    string url = d.HasMember("url") && !d["url"].IsNull() ? d["url"].GetString() : "";
    string description = d.HasMember("description") && !d["description"].IsNull() ? d["description"].GetString() : "";
    bool isProtected = d.HasMember("protected") ? d["protected"].GetBool() : false;
    bool isVerified = d.HasMember("verified") ? d["verified"].GetBool() : false;
    int followersCount = d.HasMember("followers_count") ? d["followers_count"].GetInt() : -1;
    int friendsCount = d.HasMember("friends_count") ? d["friends_count"].GetInt() : -1;
    int listedCount = d.HasMember("listed_count") ? d["listed_count"].GetInt() : -1;
    int favouritesCount = d.HasMember("favourites_count") ? d["favourites_count"].GetInt() : -1;
    int statusesCount = d.HasMember("statuses_count") ? d["statuses_count"].GetInt() : -1;
    string createdAt = d["created_at"].GetString();
    string profileBannerImageUrl = d.HasMember("profile_banner_url")
                                   ? d["profile_banner_url"].GetString() : "";
    string profileImageUrlHttps = d.HasMember("profile_image_url_https")
                                  ? d["profile_image_url_https"].GetString() : "";
    bool isDefaultProfile = d.HasMember("default_profile") ? d["default_profile"].GetBool() : false;


    //Null values:
    string lang = d.HasMember("lang") && !d["lang"].IsNull() ? d["lang"].GetString() : "";
    bool isGeoEnabled = d.HasMember("geo_enabled") && !d["geo_enabled"].IsNull() ? d["geo_enabled"].GetBool() : false;

    bool isContributorsEnabled = d.HasMember("contributors_enabled") && !d["contributors_enabled"].IsNull()
                                 ? d["contributors_enabled"].GetBool() : false;

    string profileBackgroundColor = d.HasMember("profile_background_color") && !d["profile_background_color"].IsNull()
                                    ? d["profile_background_color"].GetString() : "";

    string profileBackgroundImageUrl =
            d.HasMember("profile_background_image_url") && !d["profile_background_image_url"].IsNull()
            ? d["profile_background_image_url"].GetString() : "";

    string profileBackgroundImageUrlHttps =
            d.HasMember("profile_background_image_url_https") && !d["profile_background_image_url_https"].IsNull()
            ? d["profile_background_image_url_https"].GetString() : "";

    bool profileBackgroundTiled = d.HasMember("profile_background_tile") && !d["profile_background_tile"].IsNull()
                                  ? d["profile_background_tile"].GetBool() : false;

    string profileImageUrl =
            d.HasMember("profile_image_url") && !d["profile_image_url"].IsNull() ? d["profile_image_url"].GetString()
                                                                                 : "";

    string profileLinkColor =
            d.HasMember("profile_link_color") && !d["profile_link_color"].IsNull() ? d["profile_link_color"].GetString()
                                                                                   : "";

    string profileSidebarBorderColor =
            d.HasMember("profile_sidebar_border_color") && !d["profile_sidebar_border_color"].IsNull()
            ? d["profile_sidebar_border_color"].GetString() : "";

    string profileSidebarFillColor =
            d.HasMember("profile_sidebar_fill_color") && !d["profile_sidebar_fill_color"].IsNull()
            ? d["profile_sidebar_fill_color"].GetString() : "";

    string profileTextColor =
            d.HasMember("profile_text_color") && !d["profile_text_color"].IsNull() ? d["profile_text_color"].GetString()
                                                                                   : "";

    bool profileUseBackgroundImage =
            d.HasMember("profile_use_background_image") && !d["profile_use_background_image"].IsNull()
            ? d["profile_use_background_image"].GetBool() : false;

    bool isDefaultProfileImage = d.HasMember("default_profile") && !d["default_profile"].IsNull()
                                 ? d["default_profile"].GetBool() : false;


    int utcOffset = d.HasMember("utc_offset") && !d["utc_offset"].IsNull() ? d["utc_offset"].GetInt() : -1;
    string timeZone = d.HasMember("time_zone") && !d["time_zone"].IsNull() ? d["time_zone"].GetString() : "";
    bool translator =
            d.HasMember("is_translator") && !d["is_translator"].IsNull() ? d["is_translator"].GetBool() : false;
    bool isFollowRequestSent = d.HasMember("follow_request_sent") && !d["follow_request_sent"].IsNull()
                               ? d["follow_request_sent"].GetBool()
                               : false;
    bool showAllInlineMedia = false; //d.HasMember("showAllInlineMedia") ? d["showAllInlineMedia"].GetBool() : false;

    vector<URLEntity *> urls;
    string withheldScope = d.HasMember("withheld_scope") && !d["withheld_scope"].IsNull()
                           ? d["withheld_scope"].GetString() : "";

    vector<string> withheldInCountries;
    if (d.HasMember("withheld_in_countries")) {
        for (SizeType i = 0; i < d["withheld_in_countries"].Size(); i++) {
            withheldInCountries.push_back(d["withheld_in_countries"][i].GetString());
        }
    }

    return new User(id, idStr, name, screenName, location, url,
                    description, isProtected, isVerified, followersCount, friendsCount,
                    listedCount, favouritesCount, statusesCount, createdAt,
                    profileBannerImageUrl, profileImageUrlHttps, isDefaultProfile,
                    withheldInCountries, withheldScope,
                    urls, isGeoEnabled, lang, isContributorsEnabled, profileBackgroundColor,
                    profileBackgroundImageUrl,
                    profileBackgroundImageUrlHttps, profileBackgroundTiled, profileImageUrl,
                    profileLinkColor, profileSidebarBorderColor,
                    profileSidebarFillColor, profileTextColor, profileUseBackgroundImage,
                    isDefaultProfileImage, utcOffset, timeZone, translator, isFollowRequestSent,
                    showAllInlineMedia);

}

//Get coordinate object from json string:
Coordinates *DataReader::getCoordinates(Value &d) {
    double *longitude_latitude = new double[2];
    longitude_latitude[0] = d["coordinates"][0].GetDouble();
    longitude_latitude[1] = d["coordinates"][1].GetDouble();
    string type = d["type"].GetString();
    Coordinates *coordinates = new Coordinates(type, longitude_latitude);
    delete[] longitude_latitude;
    return coordinates;
}

//Get place object from json string
Place *
DataReader::getPlace(Value &d) {
    Place *place = nullptr;
    string name = d.HasMember("name") ? d["name"].GetString() : "";;
    string countryCode = d.HasMember("country_code") ? d["country_code"].GetString() : "";;
    string id = d.HasMember("id") ? d["id"].GetString() : "";;
    string country = d.HasMember("country") ? d["country"].GetString() : "";;
    string placeType = d.HasMember("place_type") ? d["place_type"].GetString() : "";;
    string url = d.HasMember("url") ? d["url"].GetString() : "";;
    string fullName = d.HasMember("full_name") ? d["full_name"].GetString() : "";

    BoundingBoxCoordinate *boundingBoxCoordinates = nullptr;
    vector<vector<vector<double>>> tempcoordiantes;
    if (d.HasMember("bounding_box") && !d["bounding_box"].IsNull()) {
        if (d["bounding_box"].HasMember("coordinates")) {
            for (SizeType i = 0; i < d["bounding_box"]["coordinates"].Size(); ++i) {
                vector<vector<double >> tempoptions;
                for (SizeType j = 0; j < d["bounding_box"]["coordinates"][i].Size(); ++j) {
                    vector<double> tempcoordinate;
                    tempcoordinate.push_back(d["bounding_box"]["coordinates"][i][j][0].GetDouble());
                    tempcoordinate.push_back(d["bounding_box"]["coordinates"][i][j][1].GetDouble());
                    tempoptions.push_back(tempcoordinate);
                }
                tempcoordiantes.push_back(tempoptions);
            }
        }
        string type = d["bounding_box"]["type"].GetString();
        boundingBoxCoordinates = new BoundingBoxCoordinate(type, tempcoordiantes);
    }
    place = new Place(name, countryCode, id, country, placeType, url, fullName, boundingBoxCoordinates);
    return place;
}

//Get media object form json string:
vector<MediaEntity *>
DataReader::getMedia(Value &d) {

    vector<MediaEntity *> media;

    for (SizeType i = 0; i < d.Size(); i++) {

        string displayURL = d[i]["display_url"].GetString();
        string expandedURL = d[i]["expanded_url"].GetString();
        long id = d[i]["id"].GetInt64();
        string idStr = d[i]["id_str"].GetString();
        string mediaURL = d[i]["media_url"].GetString();
        string mediaURLHttps = d[i]["media_url_https"].GetString();

        vector<int> indices;
        for (int j = 0; j < d[i]["indices"].Size(); ++j) {
            indices.push_back(d[i]["indices"][j].GetInt());
        }

        int thumbWidth = d[i]["sizes"]["thumb"]["w"].GetInt();
        int thumbHeight = d[i]["sizes"]["thumb"]["h"].GetInt();
        string thumbResize = d[i]["sizes"]["thumb"]["resize"].GetString();
        SizeEntity *thumb = new SizeEntity(thumbWidth, thumbHeight, thumbResize);

        int largeWidth = d[i]["sizes"]["large"]["w"].GetInt();
        int largeHeight = d[i]["sizes"]["large"]["h"].GetInt();
        string largeResize = d[i]["sizes"]["large"]["resize"].GetString();
        SizeEntity *large = new SizeEntity(largeWidth, largeHeight, largeResize);

        int mediumWidth = d[i]["sizes"]["medium"]["w"].GetInt();
        int mediumHeight = d[i]["sizes"]["medium"]["h"].GetInt();
        string mediumResize = d[i]["sizes"]["medium"]["resize"].GetString();
        SizeEntity *medium = new SizeEntity(mediumWidth, mediumHeight, mediumResize);

        int smallWidth = d[i]["sizes"]["small"]["w"].GetInt();
        int smallHeight = d[i]["sizes"]["small"]["h"].GetInt();
        string smallResize = d[i]["sizes"]["small"]["resize"].GetString();
        SizeEntity *small = new SizeEntity(smallWidth, smallHeight, smallResize);

        MediaSizesEntity *sizes = new MediaSizesEntity(thumb, large, medium, small);

        long sourceStatusId = d[i].HasMember("source_status_id") && !d[i]["source_status_id"].IsInt64()
                              ? d[i]["source_status_id"].GetInt64() : -1;
        string sourceStatusIdStr = d[i].HasMember("source_status_id_str") && !d[i]["source_status_id_str"].GetString()
                                   ? d[i]["source_status_id_str"].GetString() : "";
        string type = d[i]["type"].GetString();
        string url = d[i]["url"].GetString();

        VideoEntity *videoEntity = nullptr;
        //video_info
        if (d[i].HasMember("video_info") && !d[i]["video_info"].IsNull()) {

            //Get aspect ratio:
            vector<int> aspectRatio;
            for (SizeType j = 0; j < d[i]["video_info"]["aspect_ratio"].Size(); j++) {
                aspectRatio.push_back(d[i]["video_info"]["aspect_ratio"][j].GetInt());
            }

            //get duration millis
            int durationMillis = d[i]["video_info"].HasMember("duration_millis") ?
                                 d[i]["video_info"]["duration_millis"].GetInt() : 0;
            //variants
            vector<VariantEntity *> variants;
            for (SizeType j = 0; j < d[i]["video_info"]["variants"].Size(); j++) {
                long bitrate = d[i]["video_info"]["variants"][j].HasMember("bitrate") &&
                               d[i]["video_info"]["variants"][j]["bitrate"].IsInt64()
                               ? d[i]["video_info"]["variants"][j]["bitrate"].GetInt64() : 0;
                string contentType = d[i]["video_info"]["variants"][j].HasMember("content_type")
                                     && !d[i]["video_info"]["variants"][j]["content_type"].IsNull()
                                     ? d[i]["video_info"]["variants"][j]["content_type"].GetString() : "";
                string url = d[i]["video_info"]["variants"][j].HasMember("url") &&
                             !d[i]["video_info"]["variants"][j]["url"].IsNull()
                             ? d[i]["video_info"]["variants"][j]["url"].GetString() : "";

                VariantEntity *variantEntity = new VariantEntity(bitrate, contentType, url);

                variants.push_back(variantEntity);
            }
            videoEntity = new VideoEntity(aspectRatio, durationMillis, variants);
        }

        AdditionalMediaInfoEntity *additionalMediaInfoEntity = nullptr;
        if (d[i].HasMember("additional_media_info") && !d[i]["additional_media_info"].IsNull()) {
            string title =
                    d[i]["additional_media_info"].HasMember("title") && !d[i]["additional_media_info"]["title"].IsNull()
                    ?
                    d[i]["additional_media_info"]["title"].GetString() : "";
            string description = d[i]["additional_media_info"].HasMember("description") &&
                                 !d[i]["additional_media_info"]["description"].IsNull() ?
                                 d[i]["additional_media_info"]["description"].GetString() : "";
            bool embeddable = d[i]["additional_media_info"].HasMember("embeddable") &&
                              d[i]["additional_media_info"]["embeddable"].IsBool() ?
                              d[i]["additional_media_info"]["embeddable"].GetBool() : false;
            bool monetizable = d[i]["additional_media_info"].HasMember("monetizable") &&
                               d[i]["additional_media_info"]["monetizable"].IsBool() ?
                               d[i]["additional_media_info"]["monetizable"].GetBool() : false;

            additionalMediaInfoEntity = new AdditionalMediaInfoEntity(title, description, embeddable, monetizable);
        }

        MediaEntity *mediaEntity = new MediaEntity(displayURL, expandedURL, id, idStr, indices, mediaURL, mediaURLHttps,
                                                   sizes, sourceStatusId, sourceStatusIdStr, type, url, videoEntity,
                                                   additionalMediaInfoEntity);

        media.push_back(mediaEntity);
    }

    return media;
}

//Get Matching Rule Objects form json string:
vector<MatchingRulesEntity *>
DataReader::getMatchingRulesEntity(Value &d) {
    vector<MatchingRulesEntity *> matchingRules;
    for (SizeType i = 0; i < d.Size(); i++) {
        string tag = d[i]["tag"].GetString();
        string idStr = d[i]["id_str"].GetString();
        long id = d[i]["id"].GetInt64();
        MatchingRulesEntity *matchingrule = new MatchingRulesEntity(tag, id, idStr);
        matchingRules.push_back(matchingrule);
    }

    return matchingRules;
}
