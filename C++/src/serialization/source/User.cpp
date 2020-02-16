
#include "User.h"

using namespace std;


User::~User() {
    //free memory:
    withheldInCountries.shrink_to_fit();
     for (int i = 0; i <descriptionURLEntities.size() ; ++i) {
        delete descriptionURLEntities.at(i);
    }

}

//Default constructor:
User::User() {}

string User::toJSON() {
    string stringS = "{" + getLongKeyValue("Id", this->id) + " , " +
                     getStringKeyValue("Name", this->name) + " , " +
                     getStringKeyValue("ScreenName", this->screenName) + " , ";

    //All descriptionURLEntities:
    stringS += "\"DescriptionURLEntities\":[";
    if (descriptionURLEntities.size() > 0) {
        for (int i = 0; i < descriptionURLEntities.size() - 1; i++) {
            stringS += descriptionURLEntities[i]->toJSON() + " , ";
        }
        stringS += descriptionURLEntities[descriptionURLEntities.size() - 1]->toJSON();
    }
    stringS += "],";

    stringS += getStringKeyValue("url", this->url) + "," +
               getStringKeyValue("WithheldScope", withheldScope) + ",";


    stringS += "\"withheldInCountries\":[";
    if (withheldInCountries.size() > 0) {
        for (int j = 0; j < withheldInCountries.size() - 1; ++j) {
            stringS += withheldInCountries.at(j) + ",";
        }
        stringS += withheldInCountries.at(withheldInCountries.size() - 1);
    }
    stringS += "],";

    stringS += getBoolKeyValue("isProtected", this->isProtected) + " , " +
               getBoolKeyValue("isVerified", this->isVerified) + " , " +
               getIntKeyValue("followersCount", this->followersCount) + " , " +
               getIntKeyValue("friendsCount", this->friendsCount) + " , " +
               getIntKeyValue("listedCount", this->listedCount) + " , " +
               getIntKeyValue("favouritesCount", this->favouritesCount) + " , " +
               getIntKeyValue("statusesCount", this->statusesCount) + " , " +
               getStringKeyValue("createdAt", this->createdAt) + " , " +
               getBoolKeyValue("isGeoEnabled", this->isGeoEnabled) + " , " +
               getStringKeyValue("lang", this->lang) + " , " +
               getBoolKeyValue("isContributorsEnabled", this->isContributorsEnabled) + " , " +
               getStringKeyValue("profileBackgroundColor", this->profileBackgroundColor) + " , " +
               getStringKeyValue("profileBackgroundImageUrl", this->profileBannerImageUrl) + " , " +
               getStringKeyValue("profileBackgroundImageUrlHttps", this->profileBackgroundImageUrlHttps) + " , " +
               getBoolKeyValue("profileBackgroundTiled ", this->profileBackgroundTiled) + " , " +
               getStringKeyValue("profileBannerImageUrl", this->profileBannerImageUrl) + " , " +
               getStringKeyValue("profileImageUrl", this->profileImageUrl) + " , " +
               getStringKeyValue("profileImageUrlHttps ", this->profileImageUrlHttps) + " , " +
               getStringKeyValue("profileLinkColor", this->profileLinkColor) + " , " +
               getStringKeyValue("profileSidebarBorderColor", this->profileSidebarBorderColor) + " , " +
               getStringKeyValue("profileSidebarFillColor ", this->profileSidebarFillColor) + " , " +
               getStringKeyValue("profileTextColor", this->profileTextColor) + " , " +
               getBoolKeyValue("profileUseBackgroundImage ", this->profileUseBackgroundImage) + " , " +
               getBoolKeyValue("isDefaultProfile", this->isDefaultProfile) + " , " +
               getBoolKeyValue("isDefaultProfileImage", this->isDefaultProfileImage) + " , " +
               getStringKeyValue("location", this->location) + " , " +
               getStringKeyValue("description", this->description) + " , " +
               getIntKeyValue("utcOffset", this->utcOffset) + " , " +
               getStringKeyValue("timeZone", this->timeZone) + " , " +
               getBoolKeyValue("translator ", this->translator) + " , " +
               getBoolKeyValue("isFollowRequestSent", this->isFollowRequestSent) + " , " +
               getBoolKeyValue("showAllInlineMedia", this->showAllInlineMedia) + "}";

    return stringS;
}


//Hand Coded C++ serialization:
char *User::serializeHandcoded(char *buffer, int &objectSize) {
    //Serialize the object.
    //Copy Integers:
    buffer = copyInt(buffer, this->followersCount, objectSize);
    buffer = copyInt(buffer, this->friendsCount, objectSize);
    buffer = copyInt(buffer, this->listedCount, objectSize);
    buffer = copyInt(buffer, this->favouritesCount, objectSize);
    buffer = copyInt(buffer, this->statusesCount, objectSize);
    buffer = copyInt(buffer, this->utcOffset, objectSize);
    //Copy Longs:
    buffer = copyLong(buffer, this->id, objectSize);
    //Copy Booleans:
    buffer = copyBool(buffer, this->isProtected, objectSize);
    buffer = copyBool(buffer, this->isVerified, objectSize);
    buffer = copyBool(buffer, this->isGeoEnabled, objectSize);
    buffer = copyBool(buffer, this->isContributorsEnabled, objectSize);
    buffer = copyBool(buffer, this->profileBackgroundTiled, objectSize);
    buffer = copyBool(buffer, this->profileUseBackgroundImage, objectSize);
    buffer = copyBool(buffer, this->isDefaultProfile, objectSize);
    buffer = copyBool(buffer, this->isDefaultProfileImage, objectSize);
    buffer = copyBool(buffer, this->translator, objectSize);
    buffer = copyBool(buffer, this->isFollowRequestSent, objectSize);
    buffer = copyBool(buffer, this->showAllInlineMedia, objectSize);
    //Copy Strings:
    buffer = copyString(buffer, this->name, objectSize);
    buffer = copyString(buffer, this->screenName, objectSize);
    buffer = copyString(buffer, this->createdAt, objectSize);
    buffer = copyString(buffer, this->lang, objectSize);
    buffer = copyString(buffer, this->profileBackgroundColor, objectSize);
    buffer = copyString(buffer, this->profileBackgroundImageUrl, objectSize);
    buffer = copyString(buffer, this->profileBackgroundImageUrlHttps, objectSize);
    buffer = copyString(buffer, this->profileBannerImageUrl, objectSize);
    buffer = copyString(buffer, this->profileImageUrl, objectSize);
    buffer = copyString(buffer, this->profileImageUrlHttps, objectSize);
    buffer = copyString(buffer, this->profileLinkColor, objectSize);
    buffer = copyString(buffer, this->profileSidebarBorderColor, objectSize);
    buffer = copyString(buffer, this->profileSidebarFillColor, objectSize);
    buffer = copyString(buffer, this->profileTextColor, objectSize);
    buffer = copyString(buffer, this->location, objectSize);
    buffer = copyString(buffer, this->description, objectSize);
    buffer = copyString(buffer, this->timeZone, objectSize);
    buffer = copyString(buffer, this->url, objectSize);

    int numOfWithheldInCountries = this->withheldInCountries.size();
    buffer = copyInt(buffer, numOfWithheldInCountries, objectSize);
    for (int i = 0; i < numOfWithheldInCountries; i++) {
        buffer = copyString(buffer, this->withheldInCountries.at(i), objectSize);
    }

    buffer = copyString(buffer, this->withheldScope, objectSize);

    //Copy DescriptionURLEntities object:
    int numOfUrlEntities = this->descriptionURLEntities.size();
    buffer = copyInt(buffer, numOfUrlEntities, objectSize);
    for (int i = 0; i < numOfUrlEntities; i++) {
        this->descriptionURLEntities[i]->serializeHandcoded(buffer, objectSize);
    }

    return buffer;
}


User *User::deserializeHandcoded(char *buffer, int &bytesRead) {

    // Integer elements
    this->followersCount = parseInt(buffer + bytesRead);
    bytesRead += sizeof(this->followersCount);
    this->friendsCount = parseInt(buffer + bytesRead);
    bytesRead += sizeof(this->friendsCount);
    this->listedCount = parseInt(buffer + bytesRead);
    bytesRead += sizeof(this->listedCount);
    this->favouritesCount = parseInt(buffer + bytesRead);
    bytesRead += sizeof(this->favouritesCount);
    this->statusesCount = parseInt(buffer + bytesRead);
    bytesRead += sizeof(this->statusesCount);
    this->utcOffset = parseInt(buffer + bytesRead);
    bytesRead += sizeof(this->utcOffset);

    // Long elements
    this->id = parseLong(buffer + bytesRead);
    bytesRead += sizeof(this->id);

    // Boolean elements
    this->isProtected = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->isProtected);
    this->isVerified = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->isVerified);
    this->isGeoEnabled = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->isGeoEnabled);
    this->isContributorsEnabled = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->isContributorsEnabled);
    this->profileBackgroundTiled = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->profileBackgroundTiled);
    this->profileUseBackgroundImage = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->profileUseBackgroundImage);
    this->isDefaultProfile = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->isDefaultProfile);
    this->isDefaultProfileImage = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->isDefaultProfileImage);
    this->translator = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->translator);
    this->isFollowRequestSent = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->isFollowRequestSent);
    this->showAllInlineMedia = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->showAllInlineMedia);

    //Parse Strings:
    parseString(buffer + bytesRead, this->name);
    bytesRead += (sizeof(int) + this->name.length());
    parseString(buffer + bytesRead, this->screenName);
    bytesRead += (sizeof(int) + this->screenName.length());
    parseString(buffer + bytesRead, this->createdAt);
    bytesRead += (sizeof(int) + this->createdAt.length());
    parseString(buffer + bytesRead, this->lang);
    bytesRead += (sizeof(int) + this->lang.length());
    parseString(buffer + bytesRead, this->profileBackgroundColor);
    bytesRead += (sizeof(int) + this->profileBackgroundColor.length());
    parseString(buffer + bytesRead, this->profileBackgroundImageUrl);
    bytesRead += (sizeof(int) + this->profileBackgroundImageUrl.length());
    parseString(buffer + bytesRead, this->profileBackgroundImageUrlHttps);
    bytesRead += (sizeof(int) + this->profileBackgroundImageUrlHttps.length());
    parseString(buffer + bytesRead, this->profileBannerImageUrl);
    bytesRead += (sizeof(int) + this->profileBannerImageUrl.length());
    parseString(buffer + bytesRead, this->profileImageUrl);
    bytesRead += (sizeof(int) + this->profileImageUrl.length());
    parseString(buffer + bytesRead, this->profileImageUrlHttps);
    bytesRead += (sizeof(int) + this->profileImageUrlHttps.length());
    parseString(buffer + bytesRead, this->profileLinkColor);
    bytesRead += (sizeof(int) + this->profileLinkColor.length());
    parseString(buffer + bytesRead, this->profileSidebarBorderColor);
    bytesRead += (sizeof(int) + this->profileSidebarBorderColor.length());
    parseString(buffer + bytesRead, this->profileSidebarFillColor);
    bytesRead += (sizeof(int) + this->profileSidebarFillColor.length());
    parseString(buffer + bytesRead, this->profileTextColor);
    bytesRead += (sizeof(int) + this->profileTextColor.length());
    parseString(buffer + bytesRead, this->location);
    bytesRead += (sizeof(int) + this->location.length());
    parseString(buffer + bytesRead, this->description);
    bytesRead += (sizeof(int) + this->description.length());
    parseString(buffer + bytesRead, this->timeZone);
    bytesRead += (sizeof(int) + this->timeZone.length());

    parseString(buffer + bytesRead, this->url);
    bytesRead += (sizeof(int) + this->url.length());


    int numOfWithheldInCountries = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfWithheldInCountries);
    for (int i = 0; i < numOfWithheldInCountries; i++) {
        string item;
        parseString(buffer + bytesRead, item);
        bytesRead += (sizeof(int) + item.length());
        this->withheldInCountries.push_back(item);

    }
    parseString(buffer + bytesRead, this->withheldScope);
    bytesRead += (sizeof(int) + this->withheldScope.length());

    //Encapsulated objects:
    int numOfUrlEntities = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfUrlEntities);
    for (int i = 0; i < numOfUrlEntities; i++) {
        this->descriptionURLEntities.push_back(new URLEntity());
        this->descriptionURLEntities.at(i)->deserializeHandcoded(buffer, bytesRead);
    }
    return this;
}


User::User(long id, string name, string screenName, string location, string url,
               string description, bool isProtected, bool isVerified, int followersCount, int friendsCount,
               int listedCount, int favouritesCount, int statusesCount, string createdAt,
               string profileBannerImageUrl, string profileImageUrlHttps, bool isDefaultProfile,
               vector<string> withheldInCountries, string withheldScope,
               vector<URLEntity *> descriptionURLEntities, bool isGeoEnabled, string lang,
               bool isContributorsEnabled, string profileBackgroundColor, string profileBackgroundImageUrl,
               string profileBackgroundImageUrlHttps, bool profileBackgroundTiled, string profileImageUrl,
               string profileLinkColor, string profileSidebarBorderColor,
               string profileSidebarFillColor, string profileTextColor, bool profileUseBackgroundImage,
               bool isDefaultProfileImage, int utcOffset, string timeZone, bool translator, bool isFollowRequestSent,
               bool showAllInlineMedia) {

    this->id = id;
    this->name = name;
    this->screenName = screenName;
    this->location = location;
    this->url = url;
    this->description = description;
    this->isProtected = isProtected;
    this->isVerified = isVerified;
    this->followersCount = followersCount;
    this->friendsCount = friendsCount;
    this->listedCount = listedCount;
    this->favouritesCount = favouritesCount;
    this->statusesCount = statusesCount;
    this->createdAt = createdAt;
    this->profileBannerImageUrl = profileBannerImageUrl;
    this->profileImageUrlHttps = profileImageUrlHttps;
    this->isDefaultProfile = isDefaultProfile;
    this->withheldInCountries = withheldInCountries;
    this->withheldScope = withheldScope;
    this->descriptionURLEntities = descriptionURLEntities;
    this->isGeoEnabled = isGeoEnabled;
    this->lang = lang;
    this->isContributorsEnabled = isContributorsEnabled;
    this->profileBackgroundColor = profileBackgroundColor;
    this->profileBackgroundImageUrl = profileBackgroundImageUrl;
    this->profileBackgroundImageUrlHttps = profileBackgroundImageUrlHttps;
    this->profileBackgroundTiled = profileBackgroundTiled;
    this->profileImageUrl = profileImageUrl;
    this->profileLinkColor = profileLinkColor;
    this->profileSidebarBorderColor = profileSidebarBorderColor;
    this->profileSidebarFillColor = profileSidebarFillColor;
    this->profileTextColor = profileTextColor;
    this->profileUseBackgroundImage = profileUseBackgroundImage;
    this->isDefaultProfileImage = isDefaultProfileImage;
    this->utcOffset = utcOffset;
    this->timeZone = timeZone;
    this->translator = translator;
    this->isFollowRequestSent = isFollowRequestSent;
    this->showAllInlineMedia = showAllInlineMedia;
}

