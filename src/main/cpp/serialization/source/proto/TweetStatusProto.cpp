#include "TweetStatusProto.h"

TweetStatusProto::TweetStatusProto() {}

TweetStatusProto::~TweetStatusProto() {
    if (this->proto != nullptr && !this->isPointer) {
        delete this->proto;
    }
}

TweetStatusProto::TweetStatusProto(TweetStatus *tweetStatus) {

    this->proto = new proto::TweetStatusP();
    this->proto->set_createdat(tweetStatus->createdAt);
    this->proto->set_id(tweetStatus->id);
    this->proto->set_idstr(tweetStatus->idStr);
    this->proto->set_text(tweetStatus->text);
    this->proto->set_source(tweetStatus->source);
    this->proto->set_istruncated(tweetStatus->isTruncated);
    this->proto->set_inreplytostatusid(tweetStatus->inReplyToStatusId);
    this->proto->set_inreplytouserid(tweetStatus->inReplyToUserId);
    this->proto->set_inreplytoscreenname(tweetStatus->inReplyToScreenName);

    // set user:
    proto::UserP *user = proto->mutable_userp();
    user->set_id(tweetStatus->user->id);
    user->set_idstr(tweetStatus->user->idStr);
    user->set_name(tweetStatus->user->name);
    user->set_screenname(tweetStatus->user->screenName);
    user->set_location(tweetStatus->user->location);
    user->set_url(tweetStatus->user->url);
    user->set_description(tweetStatus->user->description);
    user->set_isprotected(tweetStatus->user->isProtected);
    user->set_isverified(tweetStatus->user->isVerified);
    user->set_followerscount(tweetStatus->user->followersCount);
    user->set_friendscount(tweetStatus->user->friendsCount);
    user->set_listedcount(tweetStatus->user->listedCount);
    user->set_favouritescount(tweetStatus->user->favouritesCount);
    user->set_statusescount(tweetStatus->user->statusesCount);
    user->set_createdat(tweetStatus->user->createdAt);
    user->set_profilebannerimageurl(tweetStatus->user->profileBannerImageUrl);
    user->set_profileimageurlhttps(tweetStatus->user->profileImageUrlHttps);
    user->set_isdefaultprofile(tweetStatus->user->isDefaultProfile);
    for (int i = 0; i < tweetStatus->user->withheldInCountries.size(); ++i) {
        user->add_withheldincountries(tweetStatus->user->withheldInCountries.at(i));
    }

    user->set_withheldscope(tweetStatus->user->withheldScope);

    for (int i = 0; i < tweetStatus->user->descriptionURLEntities.size(); ++i) {
        proto::URLEntityP *urlEntityP = user->mutable_descriptionurlentities();
        urlEntityP->set_displayurl(tweetStatus->user->descriptionURLEntities.at(i)->displayURL);
        urlEntityP->set_url(tweetStatus->user->descriptionURLEntities.at(i)->url);
        urlEntityP->set_expandedurl(tweetStatus->user->descriptionURLEntities.at(i)->expandedURL);

        for (int j = 0; j < tweetStatus->user->descriptionURLEntities.at(i)->indices.size(); ++j) {
            urlEntityP->add_indices(tweetStatus->user->descriptionURLEntities.at(i)->indices.at(j));
        }
    }
    user->set_isgeoenabled(tweetStatus->user->isGeoEnabled);
    user->set_lang(tweetStatus->user->lang);
    user->set_iscontributorsenabled(tweetStatus->user->isContributorsEnabled);
    user->set_profilebackgroundcolor(tweetStatus->user->profileBackgroundColor);
    user->set_profilebackgroundimageurl(tweetStatus->user->profileBackgroundImageUrl);
    user->set_profilebackgroundimageurlhttps(tweetStatus->user->profileBackgroundImageUrlHttps);
    user->set_profilebackgroundtiled(tweetStatus->user->profileBackgroundTiled);
    user->set_profileimageurl(tweetStatus->user->profileImageUrl);
    user->set_profilelinkcolor(tweetStatus->user->profileLinkColor);
    user->set_profilesidebarbordercolor(tweetStatus->user->profileSidebarBorderColor);
    user->set_profilesidebarfillcolor(tweetStatus->user->profileSidebarFillColor);
    user->set_profiletextcolor(tweetStatus->user->profileTextColor);
    user->set_profileusebackgroundimage(tweetStatus->user->profileUseBackgroundImage);
    user->set_isdefaultprofileimage(tweetStatus->user->isDefaultProfileImage);
    user->set_utcoffset(tweetStatus->user->utcOffset);
    user->set_timezone(tweetStatus->user->timeZone);
    user->set_translator(tweetStatus->user->translator);
    user->set_isfollowrequestsent(tweetStatus->user->isFollowRequestSent);
    user->set_showallinlinemedia(tweetStatus->user->showAllInlineMedia);
    // end set user

    //set coordinates:
    if (tweetStatus->coordinates != nullptr) {
        proto::CoordinatesP *coordinatesP = proto->mutable_coordinates();
        coordinatesP->set_type(tweetStatus->coordinates->type);

        for (int i = 0; i < 2; ++i) {
            coordinatesP->add_coordinates(tweetStatus->coordinates->coordinates[i]);
        }
    }

    // set place:

    if (tweetStatus->place != nullptr) {
        proto::PlaceP *placeP = proto->mutable_place();
        placeP->set_name(tweetStatus->place->name);
        placeP->set_id(tweetStatus->place->id);
        placeP->set_country(tweetStatus->place->country);
        placeP->set_placetype(tweetStatus->place->placeType);
        placeP->set_url(tweetStatus->place->url);
        placeP->set_fullname(tweetStatus->place->fullName);

        if (tweetStatus->place->boundingBoxCoordinates != nullptr) {
            proto::PlaceP_BoundingBoxCoordinateP *boundingBoxCoordinateP = placeP->mutable_boundingboxcoordinatep();

            boundingBoxCoordinateP->set_type(tweetStatus->place->boundingBoxCoordinates->type);

            for (int i = 0; i < tweetStatus->place->boundingBoxCoordinates->coordinates.size(); ++i) {
                proto::PlaceP_BoundingBoxCoordinateP_RowsOneP *rowsOneP = boundingBoxCoordinateP->add_threedimarray();
                for (int j = 0; j < tweetStatus->place->boundingBoxCoordinates->coordinates.at(i).size(); ++j) {
                    proto::PlaceP_BoundingBoxCoordinateP_RowsOneP_RowsTwoP *rowsTwoP = rowsOneP->add_rowstwop();

                    for (int k = 0;
                         k < tweetStatus->place->boundingBoxCoordinates->coordinates.at(i).at(j).size(); ++k) {
                        rowsTwoP->add_coordinate(
                                tweetStatus->place->boundingBoxCoordinates->coordinates.at(i).at(j).at(k));
                    }
                }
            }
        }

    }
    // end set place

    this->proto->set_quotedstatusid(tweetStatus->quotedStatusId);
    this->proto->set_isquotestatus(tweetStatus->isQuoteStatus);

    if (tweetStatus->quotedStatus != nullptr) {
        TweetStatusProto *tweetStatusProto = new TweetStatusProto(tweetStatus->quotedStatus);
        tweetStatusProto->isPointer = true;
        this->proto->set_allocated_quotedstatus(tweetStatusProto->getProto());
        delete tweetStatusProto;
    }

    if (tweetStatus->retweetedStatus != nullptr) {
        TweetStatusProto *tweetStatusProto = new TweetStatusProto(tweetStatus->retweetedStatus);
        tweetStatusProto->isPointer = true;
        this->proto->set_allocated_retweetedstatus(tweetStatusProto->getProto());
        delete tweetStatusProto;
    }

    this->proto->set_quotecount(tweetStatus->quoteCount);
    this->proto->set_replycount(tweetStatus->replyCount);
    this->proto->set_retweetcount(tweetStatus->retweetCount);
    this->proto->set_favoritecount(tweetStatus->favoriteCount);

    //Entities
    if (tweetStatus->entities != nullptr) {
        proto::EntitiesP *entitiesP = this->proto->mutable_entitiesp();
        this->setEntities(tweetStatus->entities, entitiesP);
    }
    if (tweetStatus->extendedTweet != nullptr) {
        proto::ExtendedTweetEntityP *extendedTweetEntityP = this->proto->mutable_extendedtweet();
        extendedTweetEntityP->set_fulltext(tweetStatus->extendedTweet->fullText);
        for (int i = 0; i < tweetStatus->extendedTweet->displayTextRange.size(); ++i) {
            this->proto->add_displaytextrange(tweetStatus->extendedTweet->displayTextRange.at(i));
        }
        if(tweetStatus->extendedTweet->entities!= nullptr) {
            proto::EntitiesP *entitiesP = extendedTweetEntityP->mutable_entities();
            this->setEntities(tweetStatus->extendedTweet->entities, entitiesP);
        }

        if(tweetStatus->extendedTweet->extendedEntities!= nullptr) {
            proto::ExtendedEntitiesP *extendedEntitiesP = extendedTweetEntityP->mutable_extendedentities();
            for (int i = 0; i < tweetStatus->extendedTweet->extendedEntities->media.size(); ++i) {
                proto::MediaEntityP *mediaEntityP = extendedEntitiesP->add_media();
                this->setMediaEntityP(mediaEntityP, tweetStatus->extendedTweet->extendedEntities->media.at(i));
            }
        }
    }

    this->proto->set_isfavorited(tweetStatus->isFavorited);
    this->proto->set_isretweeted(tweetStatus->isRetweeted);
    this->proto->set_ispossiblysensitive(tweetStatus->isPossiblySensitive);
    this->proto->set_filterlevel(tweetStatus->filterLevel);
    this->proto->set_lang(tweetStatus->lang);

    for (int i = 0; i < tweetStatus->matchingRules.size(); ++i) {
        proto::MatchingRulesEntityP *matchingRulesEntityP = this->proto->add_matchingrules();
        matchingRulesEntityP->set_tag(tweetStatus->matchingRules.at(i)->tag);
        matchingRulesEntityP->set_id(tweetStatus->matchingRules.at(i)->id);
        matchingRulesEntityP->set_idstr(tweetStatus->matchingRules.at(i)->idStr);
    }

    this->proto->set_currentuserretweetedid(tweetStatus->currentUserRetweetedId);

    for (auto it = tweetStatus->scopes.begin(); it != tweetStatus->scopes.end(); ++it) {
        proto::MapFieldEntry *mapFieldEntry = this->proto->add_scopes();
        mapFieldEntry->set_key(it->first);
        mapFieldEntry->set_value(it->second);
    }

    this->proto->set_withheldcopyright(tweetStatus->withheldCopyright);

    for (int i = 0; i < tweetStatus->withheldInCountries.size(); ++i) {
        this->proto->add_withheldincountries(tweetStatus->withheldInCountries.at(i));
    }
    this->proto->set_withheldscope(tweetStatus->withheldScope);

    for (int i = 0; i < tweetStatus->displayTextRange.size(); ++i) {
        this->proto->add_displaytextrange(tweetStatus->displayTextRange.at(i));
    }
}

void TweetStatusProto::setMediaEntityP(proto::MediaEntityP *mediaEntityP, MediaEntity *mediaEntity) {

    mediaEntityP->set_displayurl(mediaEntity->displayURL);
    mediaEntityP->set_expandedurl(mediaEntity->expandedURL);
    mediaEntityP->set_id(mediaEntity->id);
    for (int i = 0; i < mediaEntity->indices.size(); ++i) {
        mediaEntityP->add_indices(mediaEntity->indices.at(i));
    }
    mediaEntityP->set_mediaurl(mediaEntity->mediaURL);
    mediaEntityP->set_mediaurlhttps(mediaEntity->mediaURLHttps);


    if (mediaEntity->sizes != nullptr) {
        proto::MediaSizesEntityP *mediaSizesEntityP = mediaEntityP->mutable_sizes();

        if (mediaEntity->sizes->thumb != nullptr) {
            proto::SizeEntityP *thumb = mediaSizesEntityP->mutable_thumb();
            this->setSizeEntityP(thumb, mediaEntity->sizes->thumb);
        }
        if (mediaEntity->sizes->large != nullptr) {
            proto::SizeEntityP *large = mediaSizesEntityP->mutable_large();
            this->setSizeEntityP(large, mediaEntity->sizes->large);
        }

        if (mediaEntity->sizes->medium != nullptr) {
            proto::SizeEntityP *medium = mediaSizesEntityP->mutable_medium();
            this->setSizeEntityP(medium, mediaEntity->sizes->medium);
        }
        if (mediaEntity->sizes->small != nullptr) {
            proto::SizeEntityP *small = mediaSizesEntityP->mutable_small();
            this->setSizeEntityP(small, mediaEntity->sizes->small);
        }
    }

    mediaEntityP->set_type(mediaEntity->type);
    mediaEntityP->set_sourcestatusid(mediaEntity->sourceStatusId);
    mediaEntityP->set_sourcestatusidstr(mediaEntity->sourceStatusIdStr);
    mediaEntityP->set_url(mediaEntity->url);

    //VideoEntity
    if (mediaEntity->videoInfo != nullptr) {
        proto::VideoEntityP *videoEntityP = mediaEntityP->mutable_videoinfo();

        for (int i = 0; i < mediaEntity->videoInfo->aspectRatio.size(); ++i) {
            videoEntityP->add_aspectratio(mediaEntity->videoInfo->aspectRatio.at(i));
        }
        videoEntityP->set_durationmillis(mediaEntity->videoInfo->durationMillis);

        for (int i = 0; i < mediaEntity->videoInfo->variants.size(); ++i) {
            proto::VariantEntityP *variantEntityP = videoEntityP->add_variants();
            variantEntityP->set_bitrate(mediaEntity->videoInfo->variants.at(i)->bitrate);
            variantEntityP->set_contenttype(mediaEntity->videoInfo->variants.at(i)->contentType);
            variantEntityP->set_url(mediaEntity->videoInfo->variants.at(i)->url);
        }
    }

    //AdditionalMediaInfoEntity
    if (mediaEntity->additionalMediaInfo != nullptr) {
        proto::AdditionalMediaInfoEntityP *additionalMediaInfoEntityP = mediaEntityP->mutable_additionalmediainfo();
        additionalMediaInfoEntityP->set_title(mediaEntity->additionalMediaInfo->title);
        additionalMediaInfoEntityP->set_description(mediaEntity->additionalMediaInfo->description);
        additionalMediaInfoEntityP->set_embeddable(mediaEntity->additionalMediaInfo->embeddable);
        additionalMediaInfoEntityP->set_monetizable(mediaEntity->additionalMediaInfo->monetizable);
    }
}

void TweetStatusProto::setSizeEntityP(proto::SizeEntityP *sizeEntityP, SizeEntity *sizeEntity) {
    sizeEntityP->set_width(sizeEntity->width);
    sizeEntityP->set_height(sizeEntity->height);
    sizeEntityP->set_resize(sizeEntity->resize);
}

char *TweetStatusProto::serializeProto(char *buffer, int &objectSize) {

    //First determine the size of protobuf object:
    objectSize = sizeof(int) + this->proto->ByteSize();

    //Now, serialize the object.
    char *tempBuffer = buffer;

    //Copy total size.
    //This is weird. Protobuf doesn't understand end of an object in a buffer!
    int tempSize = 0;
    tempBuffer = copyInt(tempBuffer, objectSize, tempSize);

    //Standard protobuf serialization:
    this->proto->SerializeToArray(tempBuffer, objectSize - sizeof(int));

    return buffer;
}

TweetStatusProto *TweetStatusProto::deserializeProto(char *buffer, int &bytesRead) {

    int sizeofObject = 0;

    //Size of protobuf object:
    sizeofObject = parseInt(buffer + bytesRead);
    bytesRead += sizeof(sizeofObject);

    //Standard protobuf serialization:
    this->proto = new proto::TweetStatusP;
    this->proto->ParseFromArray(buffer + bytesRead, sizeofObject - sizeof(int));

    //Memory Leak:
    //isProtoSerialized = true;
    bytesRead = sizeofObject;

    return this;
}

proto::TweetStatusP *TweetStatusProto::getProto() const {
    return proto;
}

//Implement your own custom comparator:
bool TweetStatusProto::operator<(TweetStatusProto &other) {

    int countLevel = 0;
    int countLevelOtherTweet = 0;

    // get text
    countLevel += this->getProto()->text().length();

    countLevelOtherTweet += other.getProto()->text().length();

    // get QuoteStatus
    countLevel += this->getProto()->quotedstatus().text().length();

    countLevelOtherTweet += other.getProto()->quotedstatus().text().length();

    // get Retweet
    countLevel += this->getProto()->retweetcount();

    countLevelOtherTweet += other.getProto()->retweetcount();

    return countLevel < countLevelOtherTweet;
}

TweetStatusProto::TweetStatusProto(bool isPointer) : isPointer(isPointer) {}

void TweetStatusProto::TweetStatusProto::setEntities(Entities *entities, proto::EntitiesP *entitiesP ) {
    //HashtagEntity
    for (int i = 0; i < entities->hashtags.size(); ++i) {
        proto::HashtagEntityP *hashtagEntityP = entitiesP->add_hashtagentityp();
        hashtagEntityP->set_text(entities->hashtags.at(i)->text);

        for (int j = 0; j < entities->hashtags.at(i)->indices.size(); ++j) {
            hashtagEntityP->add_indices(entities->hashtags.at(i)->indices.at(j));
        }
    }

    //MediaEntity
    for (int i = 0; i < entities->media.size(); ++i) {
        proto::MediaEntityP *mediaEntityP = entitiesP->add_mediaentityp();
        this->setMediaEntityP(mediaEntityP, entities->media.at(i));
    }

    //URLEntity
    for (int i = 0; i < entities->urls.size(); ++i) {
        proto::URLEntityP *urlEntityP = entitiesP->add_urlentityp();
        urlEntityP->set_displayurl(entities->urls.at(i)->displayURL);
        urlEntityP->set_url(entities->urls.at(i)->url);
        urlEntityP->set_expandedurl(entities->urls.at(i)->expandedURL);

        for (int j = 0; j < entities->urls.at(i)->indices.size(); ++j) {
            urlEntityP->add_indices(entities->urls.at(i)->indices.at(j));
        }
    }
    //UserMentionEntity
    for (int i = 0; i < entities->userMentions.size(); ++i) {
        proto::UserMentionEntityP *userMentionEntityP = entitiesP->add_usermentionentityp();
        userMentionEntityP->set_id(entities->userMentions.at(i)->id);
        userMentionEntityP->set_idstr(entities->userMentions.at(i)->idStr);

        for (int j = 0; j < entities->userMentions.at(i)->indices.size(); ++j) {
            userMentionEntityP->add_indices(entities->userMentions.at(i)->indices.at(j));
        }
        userMentionEntityP->set_name(entities->userMentions.at(i)->name);
        userMentionEntityP->set_screenname(entities->userMentions.at(i)->screenName);

    }

    //SymbolEntity
    for (int i = 0; i < entities->symbols.size(); ++i) {
        proto::SymbolEntityP *symbolEntityP = entitiesP->add_symbolentityp();
        symbolEntityP->set_text(entities->symbols.at(i)->text);

        for (int j = 0; j < entities->symbols.at(i)->indices.size(); ++j) {
            symbolEntityP->add_indices(entities->symbols.at(i)->indices.at(j));
        }
    }

    //PollEntity
    for (int i = 0; i < entities->polls.size(); ++i) {
        proto::PollEntityP *pollEntityP = entitiesP->add_pollentityp();
        pollEntityP->set_enddatetime(entities->polls.at(i)->endDatetime);
        pollEntityP->set_durationminutes(entities->polls.at(i)->durationMinutes);

        for (int j = 0; j < entities->polls.at(i)->options.size(); ++j) {
            proto::OptionEntityP *optionEntityP = pollEntityP->add_options();
            optionEntityP->set_position(entities->polls.at(i)->options.at(j)->position);
            optionEntityP->set_text(entities->polls.at(i)->options.at(j)->text);
        }
    }

}
