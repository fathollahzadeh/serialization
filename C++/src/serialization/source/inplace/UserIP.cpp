//
// Created by saeed on 11/29/19.
//

#include "UserIP.h"

UserIP::UserIP() {}

UserIP::~UserIP() {}

UserIP::UserIP(User *user) {

    this->serialize(user);
}

void UserIP::serialize(User *user) {
    this->id = user->id;

    this->name = malloc < char > (strlen(user->name.c_str()) + 1);
    strcpy(this->name, user->name.c_str());

    this->screenName = malloc < char > (strlen(user->screenName.c_str()) + 1);
    strcpy(this->screenName, user->screenName.c_str());

    this->location = malloc < char > (strlen(user->location.c_str()) + 1);
    strcpy(this->location, user->location.c_str());

    this->url = malloc < char > (strlen(user->url.c_str()) + 1);
    strcpy(this->url, user->url.c_str());

    this->description = malloc < char > (strlen(user->description.c_str()) + 1);
    strcpy(this->description, user->description.c_str());

    this->isProtected = user->isProtected;
    this->isVerified = user->isVerified;
    this->followersCount = user->followersCount;
    this->friendsCount = user->friendsCount;
    this->listedCount = user->listedCount;
    this->favouritesCount = user->favouritesCount;
    this->statusesCount = user->statusesCount;

    this->createdAt = malloc < char > (strlen(user->createdAt.c_str()) + 1);
    strcpy(this->createdAt, user->createdAt.c_str());

    this->profileBannerImageUrl = malloc < char > (strlen(user->profileBannerImageUrl.c_str()) + 1);
    strcpy(this->profileBannerImageUrl, user->profileBannerImageUrl.c_str());

    this->profileImageUrlHttps = malloc < char > (strlen(user->profileImageUrlHttps.c_str()) + 1);
    strcpy(this->profileImageUrlHttps, user->profileImageUrlHttps.c_str());

    this->isDefaultProfile = user->isDefaultProfile;

    //TODO: implement InPlace for vector:
    //vector<string> withheldInCountries;

    this->withheldScope = malloc < char > (strlen(user->withheldScope.c_str()) + 1);
    strcpy(this->withheldScope, user->withheldScope.c_str());

    this->numOfURLEntity = user->descriptionURLEntities.size();
    this->descriptionURLEntities = new URLEntityIP[this->numOfURLEntity];
    for (int i = 0; i < this->numOfURLEntity; ++i) {
        this->descriptionURLEntities[i].serialize(user->descriptionURLEntities.at(i));
    }
    this->withheldScope = malloc < char > (strlen(user->withheldScope.c_str()) + 1);
    strcpy(this->withheldScope, user->withheldScope.c_str());

    this->isGeoEnabled = user->isGeoEnabled;

    this->lang = malloc < char > (strlen(user->lang.c_str()) + 1);
    strcpy(this->lang, user->lang.c_str());

    this->isContributorsEnabled = user->isContributorsEnabled;

    this->profileBackgroundColor = malloc < char > (strlen(user->profileBackgroundColor.c_str()) + 1);
    strcpy(this->profileBackgroundColor, user->profileBackgroundColor.c_str());

    this->profileBackgroundImageUrl = malloc < char > (strlen(user->profileBackgroundImageUrl.c_str()) + 1);
    strcpy(this->profileBackgroundImageUrl, user->profileBackgroundImageUrl.c_str());

    this->profileBackgroundImageUrlHttps = malloc < char > (strlen(user->profileBackgroundImageUrlHttps.c_str()) + 1);
    strcpy(this->profileBackgroundImageUrlHttps, user->profileBackgroundImageUrlHttps.c_str());

    this->profileBackgroundTiled = user->profileBackgroundTiled;

    this->profileImageUrl = malloc < char > (strlen(user->profileImageUrl.c_str()) + 1);
    strcpy(this->profileImageUrl, user->profileImageUrl.c_str());

    this->profileLinkColor = malloc < char > (strlen(user->profileLinkColor.c_str()) + 1);
    strcpy(this->profileLinkColor, user->profileLinkColor.c_str());

    this->profileSidebarBorderColor = malloc < char > (strlen(user->profileSidebarBorderColor.c_str()) + 1);
    strcpy(this->profileSidebarBorderColor, user->profileSidebarBorderColor.c_str());

    this->profileSidebarFillColor = malloc < char > (strlen(user->profileSidebarFillColor.c_str()) + 1);
    strcpy(this->profileSidebarFillColor, user->profileSidebarFillColor.c_str());

    this->profileTextColor = malloc < char > (strlen(user->profileTextColor.c_str()) + 1);
    strcpy(this->profileTextColor, user->profileTextColor.c_str());

    this->profileUseBackgroundImage = user->profileUseBackgroundImage;

    this->isDefaultProfileImage = user->isDefaultProfileImage;

    this->utcOffset = user->utcOffset;

    this->timeZone = malloc < char > (strlen(user->timeZone.c_str()) + 1);
    strcpy(this->timeZone, user->timeZone.c_str());

    this->translator = user->translator;
    this->isFollowRequestSent = user->isFollowRequestSent;
    this->showAllInlineMedia = user->showAllInlineMedia;
}

