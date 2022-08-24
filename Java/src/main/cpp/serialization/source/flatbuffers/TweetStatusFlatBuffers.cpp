#include "TweetStatusFlatBuffers.h"

TweetStatusFlatBuffers::TweetStatusFlatBuffers() {
	this->tweetStatus = nullptr;
}

TweetStatusFlatBuffers::~TweetStatusFlatBuffers() {

	if (this->tweetStatusFbs != nullptr) {
		delete this->tweetStatusFbs;
	}
}

TweetStatusFlatBuffers::TweetStatusFlatBuffers(TweetStatus *tweetStatus) {
	this->tweetStatus = tweetStatus;
	//this->tweetStatusFbs = nullptr;
}

void TweetStatusFlatBuffers::serializeFlatBuffers(char *buffer, int &objectSize) {

	uint8_t *bp;
	if (this->tweetStatus != nullptr) {
		flatbuffers::FlatBufferBuilder builder(4096);
		auto orc = this->addTOFlatBuffers(this->tweetStatus, builder);
		builder.Finish(orc);
		bp = builder.GetBufferPointer();
		objectSize = builder.GetSize();


	} else {
		flatbuffers::FlatBufferBuilder builder;
		builder.Finish(tweetstatusflatbuffers::TweetStatusFBS::Pack(builder, this->tweetStatusFbs));
		bp = builder.GetBufferPointer();
		objectSize = builder.GetSize();
	}
	objectSize += sizeof(objectSize);
}

void TweetStatusFlatBuffers::serializeFlatBuffersIO(char *buffer, int &objectSize) {
    uint8_t *bp;
    if (this->tweetStatus != nullptr) {
        flatbuffers::FlatBufferBuilder builder(4096);
        auto orc = this->addTOFlatBuffers(this->tweetStatus, builder);
        builder.Finish(orc);
        bp = builder.GetBufferPointer();
        objectSize = builder.GetSize();


    } else {
        flatbuffers::FlatBufferBuilder builder;
        builder.Finish(tweetstatusflatbuffers::TweetStatusFBS::Pack(builder, this->tweetStatusFbs));
        bp = builder.GetBufferPointer();
        objectSize = builder.GetSize();
    }

    // insert json size to the first 4 byte of buffer
    memcpy(buffer, &objectSize, sizeof(int));

    //copy serialized to the page buffer:
    memmove(buffer + sizeof(int), (char *) bp, objectSize);

    objectSize += sizeof(objectSize);
}

flatbuffers::Offset <TweetStatusFBS>
TweetStatusFlatBuffers::addTOFlatBuffers(TweetStatus *tweetStatus, flatbuffers::FlatBufferBuilder &builder) {

	auto created_atBuilder = builder.CreateString(tweetStatus->createdAt);
	auto textBuilder = builder.CreateString(tweetStatus->text);
	auto sourceBuilder = builder.CreateString(tweetStatus->source);
	auto in_reply_to_screen_nameBuilder = builder.CreateString(tweetStatus->inReplyToScreenName);
	auto filter_levelBuilder = builder.CreateString(tweetStatus->filterLevel);
	auto langBuilder = builder.CreateString(tweetStatus->lang);
	auto withheld_scopeBuilder = builder.CreateString(tweetStatus->withheldScope);
	auto quoted_statusBuilder =
			tweetStatus->quotedStatus != nullptr ? addTOFlatBuffers(tweetStatus->quotedStatus, builder) : 0;
	auto retweeted_statusBuilder =
			tweetStatus->retweetedStatus != nullptr ? addTOFlatBuffers(tweetStatus->retweetedStatus, builder) : 0;

	std::vector <flatbuffers::Offset<MapStringBool>> scopesList;
	for (auto it = tweetStatus->scopes.begin(); it != tweetStatus->scopes.end(); ++it) {
		auto keyBuilder = builder.CreateString(it->first);
		bool valueBuilder = it->second;
		auto mapitem = CreateMapStringBool(builder, keyBuilder, valueBuilder);
		scopesList.push_back(mapitem);
	}
	auto scopesBuilder = builder.CreateVector(scopesList);
	auto withheld_in_countriesBuilder = builder.CreateVectorOfStrings(tweetStatus->withheldInCountries);

	std::vector <flatbuffers::Offset<MatchingRulesEntityFBS>> matching_rulesList;
	for (int i = 0; i < tweetStatus->matchingRules.size(); i++) {
		auto tagBuilder = builder.CreateString(tweetStatus->matchingRules.at(i)->tag);
		auto idStrBuilder = builder.CreateString(tweetStatus->matchingRules.at(i)->idStr);
		auto item = CreateMatchingRulesEntityFBS(builder, tagBuilder, tweetStatus->matchingRules.at(i)->id,
												 idStrBuilder);
		matching_rulesList.push_back(item);
	}
	auto matching_rulesBuilder = builder.CreateVector(matching_rulesList);

	auto userBuilder = this->getUserBuilder(tweetStatus->user, builder);

	auto coordinatesBuilder =
			tweetStatus->coordinates != nullptr ? this->getCoordinatesBuilder(tweetStatus->coordinates, builder) : 0;
	auto placeBuilder = tweetStatus->place != nullptr ? this->getPlaceBuilder(tweetStatus->place, builder) : 0;
	auto entitiesBuilder =
			tweetStatus->entities != nullptr ? this->getEntitiesBuilder(tweetStatus->entities, builder) : 0;
	auto extended_entitiesBuilder =
			tweetStatus->extendedEntities != nullptr ? this->getExtendedEntitiesBuilder(tweetStatus->extendedEntities,
																						builder) : 0;

	TweetStatusFBSBuilder tweetStatusFbsBuilder(builder);
	tweetStatusFbsBuilder.add_created_at(created_atBuilder);
	tweetStatusFbsBuilder.add_id(tweetStatus->id);
	tweetStatusFbsBuilder.add_text(textBuilder);
	tweetStatusFbsBuilder.add_source(sourceBuilder);
	tweetStatusFbsBuilder.add_truncated(tweetStatus->isTruncated);
	tweetStatusFbsBuilder.add_in_reply_to_status_id(tweetStatus->inReplyToStatusId);
	tweetStatusFbsBuilder.add_in_reply_to_screen_name(in_reply_to_screen_nameBuilder);
	tweetStatusFbsBuilder.add_user(userBuilder);
	tweetStatusFbsBuilder.add_coordinates(coordinatesBuilder);
	tweetStatusFbsBuilder.add_place(placeBuilder);
	tweetStatusFbsBuilder.add_quoted_status_id(tweetStatus->quotedStatusId);
	tweetStatusFbsBuilder.add_is_quote_status(tweetStatus->isQuoteStatus);
	tweetStatusFbsBuilder.add_quoted_status(quoted_statusBuilder);
	tweetStatusFbsBuilder.add_retweeted_status(retweeted_statusBuilder);
	tweetStatusFbsBuilder.add_quote_count(tweetStatus->quoteCount);
	tweetStatusFbsBuilder.add_reply_count(tweetStatus->replyCount);
	tweetStatusFbsBuilder.add_retweet_count(tweetStatus->retweetCount);
	tweetStatusFbsBuilder.add_favorite_count(tweetStatus->favoriteCount);
	tweetStatusFbsBuilder.add_entities(entitiesBuilder);
	tweetStatusFbsBuilder.add_extended_entities(extended_entitiesBuilder);
	tweetStatusFbsBuilder.add_favorited(tweetStatus->isFavorited);
	tweetStatusFbsBuilder.add_retweeted(tweetStatus->isRetweeted);
	tweetStatusFbsBuilder.add_possibly_sensitive(tweetStatus->isPossiblySensitive);
	tweetStatusFbsBuilder.add_filter_level(filter_levelBuilder);
	tweetStatusFbsBuilder.add_lang(langBuilder);
	tweetStatusFbsBuilder.add_matching_rules(matching_rulesBuilder);
	tweetStatusFbsBuilder.add_current_user_retweet(tweetStatus->currentUserRetweetedId);
	tweetStatusFbsBuilder.add_scopes(scopesBuilder);
	tweetStatusFbsBuilder.add_withheld_copyright(tweetStatus->withheldCopyright);
	tweetStatusFbsBuilder.add_withheld_in_countries(withheld_in_countriesBuilder);
	tweetStatusFbsBuilder.add_withheld_scope(withheld_scopeBuilder);

	auto orc = tweetStatusFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <UserFBS>
TweetStatusFlatBuffers::getUserBuilder(User *user, flatbuffers::FlatBufferBuilder &builder) {

	auto nameBuilder = builder.CreateString(user->name);
	auto screen_nameBuilder = builder.CreateString(user->screenName);
	auto locationBuilder = builder.CreateString(user->location);
	auto urlBuilder = builder.CreateString(user->url);
	auto descriptionBuilder = builder.CreateString(user->description);
	auto created_atBuilder = builder.CreateString(user->createdAt);
	auto profile_banner_urlBuilder = builder.CreateString(user->profileBannerImageUrl);
	auto profile_image_url_httpsBuilder = builder.CreateString(user->profileImageUrlHttps);
	auto withheld_scopeBuilder = builder.CreateString(user->withheldScope);
	auto langBuilder = builder.CreateString(user->lang);
	auto profile_background_colorBuilder = builder.CreateString(user->profileBackgroundColor);
	auto profile_background_image_urlBuilder = builder.CreateString(user->profileBackgroundImageUrl);
	auto profile_background_image_url_httpsBuilder = builder.CreateString(user->profileBackgroundImageUrlHttps);
	auto profile_image_urlBuilder = builder.CreateString(user->profileImageUrl);
	auto profile_link_colorBuilder = builder.CreateString(user->profileLinkColor);
	auto profile_sidebar_border_colorBuilder = builder.CreateString(user->profileSidebarBorderColor);
	auto profile_sidebar_fill_colorBuilder = builder.CreateString(user->profileSidebarFillColor);
	auto profile_text_colorBuilder = builder.CreateString(user->profileTextColor);
	auto time_zoneBuilder = builder.CreateString(user->timeZone);

	auto withheld_in_countriesBuilder = builder.CreateVectorOfStrings(user->withheldInCountries);

	std::vector <flatbuffers::Offset<URLEntityFBS>> descriptionURLEntitiesList;
	for (int i = 0; i < user->descriptionURLEntities.size(); i++) {
		auto item = this->getURLEntityBuilder(user->descriptionURLEntities[i], builder);
		descriptionURLEntitiesList.push_back(item);
	}
	auto descriptionURLEntitiesBuilder = builder.CreateVector(descriptionURLEntitiesList);

	UserFBSBuilder userFbsBuilder(builder);
	userFbsBuilder.add_id(user->id);
	userFbsBuilder.add_name(nameBuilder);
	userFbsBuilder.add_screen_name(screen_nameBuilder);
	userFbsBuilder.add_location(locationBuilder);
	userFbsBuilder.add_url(urlBuilder);
	userFbsBuilder.add_description(descriptionBuilder);
	userFbsBuilder.add_isProtected(user->isProtected);
	userFbsBuilder.add_verified(user->isVerified);
	userFbsBuilder.add_followers_count(user->followersCount);
	userFbsBuilder.add_friends_count(user->friendsCount);
	userFbsBuilder.add_listed_count(user->listedCount);
	userFbsBuilder.add_favourites_count(user->favouritesCount);
	userFbsBuilder.add_statuses_count(user->statusesCount);
	userFbsBuilder.add_created_at(created_atBuilder);
	userFbsBuilder.add_profile_banner_url(profile_banner_urlBuilder);
	userFbsBuilder.add_profile_image_url_https(profile_image_url_httpsBuilder);
	userFbsBuilder.add_default_profile(user->isDefaultProfile);
	userFbsBuilder.add_withheld_in_countries(withheld_in_countriesBuilder);
	userFbsBuilder.add_withheld_scope(withheld_scopeBuilder);
	userFbsBuilder.add_descriptionURLEntities(descriptionURLEntitiesBuilder);
	userFbsBuilder.add_geo_enabled(user->isGeoEnabled);
	userFbsBuilder.add_lang(langBuilder);
	userFbsBuilder.add_contributors_enabled(user->isContributorsEnabled);
	userFbsBuilder.add_profile_background_color(profile_background_colorBuilder);
	userFbsBuilder.add_profile_background_image_url(profile_background_image_urlBuilder);
	userFbsBuilder.add_profile_background_image_url_https(profile_background_image_url_httpsBuilder);
	userFbsBuilder.add_profile_background_tile(user->profileBackgroundTiled);
	userFbsBuilder.add_profile_image_url(profile_image_urlBuilder);
	userFbsBuilder.add_profile_link_color(profile_link_colorBuilder);
	userFbsBuilder.add_profile_sidebar_border_color(profile_sidebar_border_colorBuilder);
	userFbsBuilder.add_profile_sidebar_fill_color(profile_sidebar_fill_colorBuilder);
	userFbsBuilder.add_profile_text_color(profile_text_colorBuilder);
	userFbsBuilder.add_profile_use_background_image(user->profileUseBackgroundImage);
	userFbsBuilder.add_utc_offset(user->utcOffset);
	userFbsBuilder.add_time_zone(time_zoneBuilder);
	userFbsBuilder.add_is_translator(user->translator);
	userFbsBuilder.add_follow_request_sent(user->isFollowRequestSent);
	userFbsBuilder.add_showAllInlineMedia(user->showAllInlineMedia);
	auto orc = userFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <AdditionalMediaInfoEntityFBS>
TweetStatusFlatBuffers::getAdditionalMediaInfoEntityBuilder(AdditionalMediaInfoEntity *additionalMediaInfoEntity,
															flatbuffers::FlatBufferBuilder &builder) {

	auto titleBuilder = builder.CreateString(additionalMediaInfoEntity->title);
	auto descriptionBuilder = builder.CreateString(additionalMediaInfoEntity->description);

	AdditionalMediaInfoEntityFBSBuilder additionalMediaInfoEntityFbs(builder);
	additionalMediaInfoEntityFbs.add_title(titleBuilder);
	additionalMediaInfoEntityFbs.add_description(descriptionBuilder);
	additionalMediaInfoEntityFbs.add_embeddable(additionalMediaInfoEntity->embeddable);
	additionalMediaInfoEntityFbs.add_monetizable(additionalMediaInfoEntity->monetizable);

	auto orc = additionalMediaInfoEntityFbs.Finish();
	return orc;
}

flatbuffers::Offset <BoundingBoxCoordinateFBS>
TweetStatusFlatBuffers::getBoundingBoxCoordinateBuilder(BoundingBoxCoordinate *boundingBoxCoordinate,
														flatbuffers::FlatBufferBuilder &builder) {

	auto typeBuilder = builder.CreateString(boundingBoxCoordinate->type);

	std::vector <flatbuffers::Offset<DoubleList1>> coordinatesList;

	for (int i = 0; i < boundingBoxCoordinate->coordinates.size(); ++i) {

		std::vector <flatbuffers::Offset<DoubleList2>> list1;

		for (int j = 0; j < boundingBoxCoordinate->coordinates.at(i).size(); ++j) {
			auto tl = builder.CreateVector(boundingBoxCoordinate->coordinates.at(i).at(j));
			auto item = CreateDoubleList2(builder, tl);
			list1.push_back(item);
		}

		auto tl = builder.CreateVector(list1);
		auto item = CreateDoubleList1(builder, tl);
		coordinatesList.push_back(item);
	}
	auto coordinateBuilder = builder.CreateVector(coordinatesList);

	BoundingBoxCoordinateFBSBuilder boundingBoxCoordinateFbsBuilder(builder);
	boundingBoxCoordinateFbsBuilder.add_type(typeBuilder);
	boundingBoxCoordinateFbsBuilder.add_coordinates(coordinateBuilder);
	auto orc = boundingBoxCoordinateFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <CoordinatesFBS>
TweetStatusFlatBuffers::getCoordinatesBuilder(Coordinates *coordinates, flatbuffers::FlatBufferBuilder &builder) {

	auto typeBuilder = builder.CreateString(coordinates->type);
	auto coordinatesBuilder = builder.CreateVector(coordinates->coordinates, 2);

	CoordinatesFBSBuilder coordinatesFbsBuilder(builder);
	coordinatesFbsBuilder.add_type(typeBuilder);
	coordinatesFbsBuilder.add_coordinates(coordinatesBuilder);
	auto orc = coordinatesFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <EntitiesFBS>
TweetStatusFlatBuffers::getEntitiesBuilder(Entities *entities, flatbuffers::FlatBufferBuilder &builder) {

	std::vector <flatbuffers::Offset<HashtagEntityFBS>> hashtagEntityList;
	for (int i = 0; i < entities->hashtags.size(); i++) {
		auto item = this->getHashtagEntityBuilder(entities->hashtags[i], builder);
		hashtagEntityList.push_back(item);
	}
	auto hashtagBuilder = builder.CreateVector(hashtagEntityList);

	std::vector <flatbuffers::Offset<MediaEntityFBS>> mediaEntityList;
	for (int i = 0; i < entities->media.size(); i++) {
		auto item = this->getMediaEntityBuilder(entities->media[i], builder);
		mediaEntityList.push_back(item);
	}
	auto mediaBuilder = builder.CreateVector(mediaEntityList);

	std::vector <flatbuffers::Offset<URLEntityFBS>> urlEntityList;
	for (int i = 0; i < entities->urls.size(); i++) {
		auto item = this->getURLEntityBuilder(entities->urls[i], builder);
		urlEntityList.push_back(item);
	}
	auto urlBuilder = builder.CreateVector(urlEntityList);

	std::vector <flatbuffers::Offset<UserMentionEntityFBS>> userMentionEntityList;
	for (int i = 0; i < entities->userMentions.size(); i++) {
		auto item = this->getUserMentionEntityBuilder(entities->userMentions[i], builder);
		userMentionEntityList.push_back(item);
	}
	auto userMentionBuilder = builder.CreateVector(userMentionEntityList);

	std::vector <flatbuffers::Offset<SymbolEntityFBS>> symbolEntityList;
	for (int i = 0; i < entities->symbols.size(); i++) {
		auto item = this->getSymbolEntityBuilder(entities->symbols[i], builder);
		symbolEntityList.push_back(item);
	}
	auto symbolBuilder = builder.CreateVector(symbolEntityList);

	std::vector <flatbuffers::Offset<PollEntityFBS>> pollEntityList;
	for (int i = 0; i < entities->polls.size(); i++) {
		auto item = this->getPollEntityBuilder(entities->polls[i], builder);
		pollEntityList.push_back(item);
	}
	auto pollBuilder = builder.CreateVector(pollEntityList);

	EntitiesFBSBuilder entitiesFbsBuilder(builder);
	entitiesFbsBuilder.add_hashtags(hashtagBuilder);
	entitiesFbsBuilder.add_media(mediaBuilder);
	entitiesFbsBuilder.add_urls(urlBuilder);
	entitiesFbsBuilder.add_user_mentions(userMentionBuilder);
	entitiesFbsBuilder.add_symbols(symbolBuilder);
	entitiesFbsBuilder.add_polls(pollBuilder);
	auto orc = entitiesFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <ExtendedEntitiesFBS>
TweetStatusFlatBuffers::getExtendedEntitiesBuilder(ExtendedEntities *extendedEntities,
												   flatbuffers::FlatBufferBuilder &builder) {

	std::vector <flatbuffers::Offset<MediaEntityFBS>> mediaEntityList;
	for (int i = 0; i < extendedEntities->media.size(); i++) {
		auto item = this->getMediaEntityBuilder(extendedEntities->media[i], builder);
		mediaEntityList.push_back(item);
	}
	auto mediaBuilder = builder.CreateVector(mediaEntityList);

	ExtendedEntitiesFBSBuilder extendedEntitiesFbsBuilder(builder);
	extendedEntitiesFbsBuilder.add_media(mediaBuilder);
	auto orc = extendedEntitiesFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <HashtagEntityFBS>
TweetStatusFlatBuffers::getHashtagEntityBuilder(HashtagEntity *hashtagEntity, flatbuffers::FlatBufferBuilder &builder) {
	auto textBuilder = builder.CreateString(hashtagEntity->text);
	auto indicesBuilder = builder.CreateVector(hashtagEntity->indices);

	HashtagEntityFBSBuilder hashtagEntityFbsBuilder(builder);
	hashtagEntityFbsBuilder.add_text(textBuilder);
	hashtagEntityFbsBuilder.add_indices(indicesBuilder);
	auto orc = hashtagEntityFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <MediaEntityFBS>
TweetStatusFlatBuffers::getMediaEntityBuilder(MediaEntity *mediaEntity, flatbuffers::FlatBufferBuilder &builder) {

	auto display_urlBuilder = builder.CreateString(mediaEntity->displayURL);
	auto expanded_urlBuilder = builder.CreateString(mediaEntity->expandedURL);
	auto media_urlBuilder = builder.CreateString(mediaEntity->mediaURL);
	auto media_url_httpsBuilder = builder.CreateString(mediaEntity->mediaURLHttps);
	auto typeBuilder = builder.CreateString(mediaEntity->type);
	auto source_status_id_strBuilder = builder.CreateString(mediaEntity->sourceStatusIdStr);
	auto urlBuilder = builder.CreateString(mediaEntity->url);
	auto indicesBuilder = builder.CreateVector(mediaEntity->indices);
	auto sizesBuilder =
			mediaEntity->sizes != nullptr ? this->getMediaSizesEntityBuilder(mediaEntity->sizes, builder) : 0;
	auto video_infoBuilder =
			mediaEntity->videoInfo != nullptr ? this->getVideoEntityBuilder(mediaEntity->videoInfo, builder) : 0;
	auto additional_media_infoBuilder =
			mediaEntity->additionalMediaInfo != nullptr ? this->getAdditionalMediaInfoEntityBuilder(
					mediaEntity->additionalMediaInfo, builder) : 0;

	MediaEntityFBSBuilder mediaEntityFbsBuilder(builder);
	mediaEntityFbsBuilder.add_display_url(display_urlBuilder);
	mediaEntityFbsBuilder.add_expanded_url(expanded_urlBuilder);
	mediaEntityFbsBuilder.add_id(mediaEntity->id);
	mediaEntityFbsBuilder.add_indices(indicesBuilder);
	mediaEntityFbsBuilder.add_media_url(media_urlBuilder);
	mediaEntityFbsBuilder.add_media_url_https(media_url_httpsBuilder);
	mediaEntityFbsBuilder.add_sizes(sizesBuilder);
	mediaEntityFbsBuilder.add_type(typeBuilder);
	mediaEntityFbsBuilder.add_source_status_id(mediaEntity->sourceStatusId);
	mediaEntityFbsBuilder.add_source_status_id_str(source_status_id_strBuilder);
	mediaEntityFbsBuilder.add_url(urlBuilder);
	mediaEntityFbsBuilder.add_video_info(video_infoBuilder);
	mediaEntityFbsBuilder.add_additional_media_info(additional_media_infoBuilder);
	auto orc = mediaEntityFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <MediaSizesEntityFBS>
TweetStatusFlatBuffers::getMediaSizesEntityBuilder(MediaSizesEntity *mediaSizesEntity,
												   flatbuffers::FlatBufferBuilder &builder) {

	auto thumbBuilder =
			mediaSizesEntity->thumb != nullptr ? this->getSizeEntityBuilder(mediaSizesEntity->thumb, builder) : 0;
	auto largeBuilder =
			mediaSizesEntity->large != nullptr ? this->getSizeEntityBuilder(mediaSizesEntity->large, builder) : 0;
	auto mediumBuilder =
			mediaSizesEntity->medium != nullptr ? this->getSizeEntityBuilder(mediaSizesEntity->medium, builder) : 0;
	auto smallBuilder =
			mediaSizesEntity->small != nullptr ? this->getSizeEntityBuilder(mediaSizesEntity->small, builder) : 0;

	MediaSizesEntityFBSBuilder mediaSizesEntityFbsBuilder(builder);
	mediaSizesEntityFbsBuilder.add_thumb(thumbBuilder);
	mediaSizesEntityFbsBuilder.add_large(largeBuilder);
	mediaSizesEntityFbsBuilder.add_medium(mediumBuilder);
	mediaSizesEntityFbsBuilder.add_small(smallBuilder);
	auto orc = mediaSizesEntityFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <OptionEntityFBS>
TweetStatusFlatBuffers::getOptionEntityBuilder(OptionEntity *optionEntity, flatbuffers::FlatBufferBuilder &builder) {

	auto textBuilder = builder.CreateString(optionEntity->text);
	OptionEntityFBSBuilder optionEntityFbsBuilder(builder);
	optionEntityFbsBuilder.add_text(textBuilder);
	optionEntityFbsBuilder.add_position(optionEntity->position);
	auto orc = optionEntityFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <PlaceFBS>
TweetStatusFlatBuffers::getPlaceBuilder(Place *place, flatbuffers::FlatBufferBuilder &builder) {

	auto nameBuilder = builder.CreateString(place->name);
	auto country_codeBuilder = builder.CreateString(place->countryCode);
	auto idBuilder = builder.CreateString(place->id);
	auto countryBuilder = builder.CreateString(place->country);
	auto place_typeBuilder = builder.CreateString(place->placeType);
	auto urlBuilder = builder.CreateString(place->url);
	auto full_nameBuilder = builder.CreateString(place->fullName);
	auto bounding_boxBuilder = place->boundingBoxCoordinates != nullptr ? this->getBoundingBoxCoordinateBuilder(
			place->boundingBoxCoordinates, builder) : 0;

	PlaceFBSBuilder placeFbsBuilder(builder);
	placeFbsBuilder.add_name(nameBuilder);
	placeFbsBuilder.add_country_code(country_codeBuilder);
	placeFbsBuilder.add_id(idBuilder);
	placeFbsBuilder.add_country(countryBuilder);
	placeFbsBuilder.add_place_type(place_typeBuilder);
	placeFbsBuilder.add_url(urlBuilder);
	placeFbsBuilder.add_full_name(full_nameBuilder);
	placeFbsBuilder.add_bounding_box(bounding_boxBuilder);
	auto orc = placeFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <PollEntityFBS>
TweetStatusFlatBuffers::getPollEntityBuilder(PollEntity *pollEntity, flatbuffers::FlatBufferBuilder &builder) {

	auto end_datetimeBuilder = builder.CreateString(pollEntity->endDatetime);
	auto duration_minutesBuilder = builder.CreateString(pollEntity->durationMinutes);

	std::vector <flatbuffers::Offset<OptionEntityFBS>> optionEntityList;
	for (int i = 0; i < pollEntity->options.size(); i++) {
		auto item = this->getOptionEntityBuilder(pollEntity->options[i], builder);
		optionEntityList.push_back(item);
	}
	auto optionsBuilder = builder.CreateVector(optionEntityList);

	PollEntityFBSBuilder pollEntityFbsBuilder(builder);
	pollEntityFbsBuilder.add_options(optionsBuilder);
	pollEntityFbsBuilder.add_end_datetime(end_datetimeBuilder);
	pollEntityFbsBuilder.add_duration_minutes(duration_minutesBuilder);
	auto orc = pollEntityFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <SizeEntityFBS>
TweetStatusFlatBuffers::getSizeEntityBuilder(SizeEntity *sizeEntity, flatbuffers::FlatBufferBuilder &builder) {

	auto resizeBuilder = builder.CreateString(sizeEntity->resize);

	SizeEntityFBSBuilder sizeEntityFbsBuilder(builder);
	sizeEntityFbsBuilder.add_width(sizeEntity->width);
	sizeEntityFbsBuilder.add_height(sizeEntity->height);
	sizeEntityFbsBuilder.add_resize(resizeBuilder);
	auto orc = sizeEntityFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <SymbolEntityFBS>
TweetStatusFlatBuffers::getSymbolEntityBuilder(SymbolEntity *symbolEntity, flatbuffers::FlatBufferBuilder &builder) {

	auto textBuilder = builder.CreateString(symbolEntity->text);
	auto indicesBuilder = builder.CreateVector(symbolEntity->indices);

	SymbolEntityFBSBuilder symbolEntityFbsBuilder(builder);
	symbolEntityFbsBuilder.add_text(textBuilder);
	symbolEntityFbsBuilder.add_indices(indicesBuilder);
	auto orc = symbolEntityFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <URLEntityFBS>
TweetStatusFlatBuffers::getURLEntityBuilder(URLEntity *urlEntity, flatbuffers::FlatBufferBuilder &builder) {

	auto display_urlBuilder = builder.CreateString(urlEntity->displayURL);
	auto expanded_urlBuilder = builder.CreateString(urlEntity->expandedURL);
	auto urlBuilder = builder.CreateString(urlEntity->url);
	auto indicesBuilder = builder.CreateVector(urlEntity->indices);

	URLEntityFBSBuilder urlEntityFbsBuilder(builder);
	urlEntityFbsBuilder.add_display_url(display_urlBuilder);
	urlEntityFbsBuilder.add_expanded_url(expanded_urlBuilder);
	urlEntityFbsBuilder.add_url(urlBuilder);
	urlEntityFbsBuilder.add_indices(indicesBuilder);
	auto orc = urlEntityFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <UserMentionEntityFBS>
TweetStatusFlatBuffers::getUserMentionEntityBuilder(UserMentionEntity *userMentionEntity,
													flatbuffers::FlatBufferBuilder &builder) {
	auto id_strBuilder = builder.CreateString(userMentionEntity->idStr);
	auto nameBuilder = builder.CreateString(userMentionEntity->name);
	auto screen_nameBuilder = builder.CreateString(userMentionEntity->screenName);
	auto indicesBuilder = builder.CreateVector(userMentionEntity->indices);

	UserMentionEntityFBSBuilder userMentionEntityFbsBuilder(builder);
	userMentionEntityFbsBuilder.add_id(userMentionEntity->id);
	userMentionEntityFbsBuilder.add_id_str(id_strBuilder);
	userMentionEntityFbsBuilder.add_indices(indicesBuilder);
	userMentionEntityFbsBuilder.add_name(nameBuilder);
	userMentionEntityFbsBuilder.add_screen_name(screen_nameBuilder);
	auto orc = userMentionEntityFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <VariantEntityFBS>
TweetStatusFlatBuffers::getVariantEntityBuilder(VariantEntity *variantEntity, flatbuffers::FlatBufferBuilder &builder) {

	auto content_typeBuilder = builder.CreateString(variantEntity->contentType);
	auto urlBuilder = builder.CreateString(variantEntity->url);

	VariantEntityFBSBuilder variantEntityFbsBuilder(builder);
	variantEntityFbsBuilder.add_bitrate(variantEntity->bitrate);
	variantEntityFbsBuilder.add_content_type(content_typeBuilder);
	variantEntityFbsBuilder.add_url(urlBuilder);
	auto orc = variantEntityFbsBuilder.Finish();
	return orc;
}

flatbuffers::Offset <VideoEntityFBS>
TweetStatusFlatBuffers::getVideoEntityBuilder(VideoEntity *videoEntity, flatbuffers::FlatBufferBuilder &builder) {


	auto aspect_ratioBuilder = builder.CreateVector(videoEntity->aspectRatio);

	std::vector <flatbuffers::Offset<VariantEntityFBS>> variantEntityList;
	for (int i = 0; i < videoEntity->variants.size(); i++) {
		auto item = this->getVariantEntityBuilder(videoEntity->variants[i], builder);
		variantEntityList.push_back(item);
	}
	auto variantBuilder = builder.CreateVector(variantEntityList);


	VideoEntityFBSBuilder videoEntityFbsBuilder(builder);
	videoEntityFbsBuilder.add_aspect_ratio(aspect_ratioBuilder);
	videoEntityFbsBuilder.add_duration_millis(videoEntity->durationMillis);
	videoEntityFbsBuilder.add_variants(variantBuilder);
	auto orc = videoEntityFbsBuilder.Finish();
	return orc;
}


TweetStatusFlatBuffers *TweetStatusFlatBuffers::deserializeFlatBuffers(char *buffer, int &bytesRead) {

	this->tweetStatusFbs = new TweetStatusFBST();
	GetTweetStatusFBS(buffer)->UnPackTo(this->tweetStatusFbs);
	return this;
}


//Implement your own custom comparator:
bool TweetStatusFlatBuffers::operator<(TweetStatusFlatBuffers &other) {

	int countLevel = 0;
	int countLevelOtherTweet = 0;

	// get text
	countLevel += this->tweetStatusFbs->text.size();
	countLevelOtherTweet += other.tweetStatusFbs->text.size();

	// get QuoteStatus
	if (this->tweetStatusFbs->quoted_status != nullptr)
		countLevel += this->tweetStatusFbs->quoted_status->text.size();

	if (other.tweetStatusFbs->quoted_status != nullptr)
		countLevelOtherTweet += other.tweetStatusFbs->quoted_status->text.size();

	// get Retweet
	if (this->tweetStatusFbs->retweeted_status != nullptr)
		countLevel += this->tweetStatusFbs->retweeted_status->retweet_count;

	if (other.tweetStatusFbs->retweeted_status != nullptr)
		countLevelOtherTweet += other.tweetStatusFbs->retweeted_status->retweet_count;

	return countLevel < countLevelOtherTweet;
}