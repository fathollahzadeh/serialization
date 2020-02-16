
#include "TweetStatus.h"


using namespace std;

TweetStatus::~TweetStatus() {

    //free memory
    if (this->isPointer) {
        if (user != nullptr)
            delete user;
        if (coordinates != nullptr)
            delete coordinates;
        if (place != nullptr)
            delete place;
        if (quotedStatus != nullptr)
            delete quotedStatus;
        if (retweetedStatus != nullptr)
            delete retweetedStatus;
        if (entities != nullptr)
            delete entities;
        if (extendedEntities != nullptr)
            delete extendedEntities;
        for (int i = 0; i < matchingRules.size(); ++i) {
            delete matchingRules.at(i);
        }

        withheldInCountries.shrink_to_fit();
    }

}

TweetStatus::TweetStatus() {
    this->isPointer= true;
}

TweetStatus::TweetStatus(string createdAt, long id, string text, string source,
                         bool isTruncated, long inReplyToStatusId, long inReplyToUserId,
                         string inReplyToScreenName, User *user, Coordinates *coordinates,
                         Place *place, long quotedStatusId, bool isQuoteStatus, TweetStatus *quotedStatus,
                         TweetStatus *retweetedStatus, int quoteCount, int replyCount, int retweetCount,
                         int favoriteCount, Entities *entities, ExtendedEntities *extendedEntities,
                         bool isFavorited, bool isRetweeted, bool isPossiblySensitive, string filterLevel,
                         string lang, vector<MatchingRulesEntity *> matchingRules,
                         long currentUserRetweetedId, map<string, bool> scopes, bool withheldCopyright,
                         vector<string> withheldInCountries, string withheldScope) {
    this->createdAt = createdAt;
    this->id = id;
    this->text = text;
    this->source = source;
    this->isTruncated = isTruncated;
    this->inReplyToStatusId = inReplyToStatusId;
    this->inReplyToUserId = inReplyToUserId;
    this->inReplyToScreenName = inReplyToScreenName;
    this->user = user;
    this->coordinates = coordinates;
    this->place = place;
    this->quotedStatusId = quotedStatusId;
    this->isQuoteStatus = isQuoteStatus;
    this->quotedStatus = quotedStatus;
    this->retweetedStatus = retweetedStatus;
    this->quoteCount = quoteCount;
    this->replyCount = replyCount;
    this->retweetCount = retweetCount;
    this->favoriteCount = favoriteCount;
    this->entities = entities;
    this->extendedEntities = extendedEntities;
    this->isFavorited = isFavorited;
    this->isRetweeted = isRetweeted;
    this->isPossiblySensitive = isPossiblySensitive;
    this->filterLevel = filterLevel;
    this->lang = lang;
    this->matchingRules = matchingRules;
    this->currentUserRetweetedId = currentUserRetweetedId;
    this->scopes = scopes;
    this->withheldCopyright = withheldCopyright;
    this->withheldInCountries = withheldInCountries;
    this->withheldScope = withheldScope;
    this->isPointer= true;
}


//C++: Explicit call needed for printing content:
string TweetStatus::toJSON() {

    string stringS = "{" +
                     getStringKeyValue("createdAt", this->createdAt) + "," +
                     getLongKeyValue("id", this->id) + ", " +
                     getStringKeyValue("text", this->text) + "," +
                     getStringKeyValue("source", this->source) + " , " +
                     getBoolKeyValue("isTruncated", this->isTruncated) + " , " +
                     "\"user\":" + (*this->user).toJSON() + " , " +
                     getLongKeyValue("quotedStatusId", this->quotedStatusId) + " , " +
                     getIntKeyValue("replyCount", this->replyCount) + ", " +
                     getIntKeyValue("retweetCount", this->retweetCount) + " , ";
    stringS += "\"entities\":" + entities->toJSON() + ",";

    stringS += getBoolKeyValue("isRetweeted", this->isRetweeted) + " , " +
               getLongKeyValue("inReplyToStatusId", this->inReplyToStatusId) + " , " +
               getLongKeyValue("inReplyToUserId", this->inReplyToUserId) + " , " +
               getStringKeyValue("inReplyToScreenName", this->inReplyToScreenName) + " , ";
    if (this->coordinates != nullptr)
        stringS += "\"coordinates\": " + (*this->coordinates).toJSON() + " , ";
    if (place != nullptr)
        stringS += "\"place\": " + (*this->place).toJSON() + " , ";
    /* getBoolKeyValue("isQuoteStatus ", this->getIsQuoteStatus()) + " , " +*/
    if (this->quotedStatus != nullptr)
        stringS += "\"quotedStatus\": " + (*this->quotedStatus).toJSON() + " , ";
    /*
     "\"retweetedStatus\": " + (*this->getRetweetedStatus()).toJSON() + " - " +
     "quoteCount: " + itos(this->getQuoteCount()) + " , " +*/
    stringS += getIntKeyValue("favoriteCount", this->favoriteCount) + " , " +
               getBoolKeyValue("isFavorited", this->isFavorited) + " , " +
               getBoolKeyValue("isPossiblySensitive ", this->isPossiblySensitive) + " , " +
               getStringKeyValue("lang ", this->lang) + " , " +
               getLongKeyValue("currentUserRetweetId", this->currentUserRetweetedId);


    stringS += "}";


    return stringS;

}


//Hand Coded C++ serialization:
char *TweetStatus::serializeHandcoded(char *buffer, int &objectSize) {


    //Copy Integers:
    buffer = copyInt(buffer, this->replyCount, objectSize);
    buffer = copyInt(buffer, this->retweetCount, objectSize);
    buffer = copyInt(buffer, this->quoteCount, objectSize);
    buffer = copyInt(buffer, this->favoriteCount, objectSize);

    //Copy Longs:
    buffer = copyLong(buffer, this->id, objectSize);
    buffer = copyLong(buffer, this->quotedStatusId, objectSize);
    buffer = copyLong(buffer, this->inReplyToStatusId, objectSize);
    buffer = copyLong(buffer, this->inReplyToUserId, objectSize);
    buffer = copyLong(buffer, this->currentUserRetweetedId, objectSize);

    //Copy Booleans:
    buffer = copyBool(buffer, this->isTruncated, objectSize);
    buffer = copyBool(buffer, this->isRetweeted, objectSize);
    buffer = copyBool(buffer, this->isQuoteStatus, objectSize);
    buffer = copyBool(buffer, this->isFavorited, objectSize);
    buffer = copyBool(buffer, this->isPossiblySensitive, objectSize);
    buffer = copyBool(buffer, this->withheldCopyright, objectSize);

    //Copy Strings:
    buffer = copyString(buffer, this->createdAt, objectSize);
    buffer = copyString(buffer, this->text, objectSize);
    buffer = copyString(buffer, this->source, objectSize);
    buffer = copyString(buffer, this->inReplyToScreenName, objectSize);
    buffer = copyString(buffer, this->lang, objectSize);
    buffer = copyString(buffer, this->filterLevel, objectSize);
    buffer = copyString(buffer, this->withheldScope, objectSize);


    int numOfScopes = this->scopes.size();
    buffer = copyInt(buffer, numOfScopes, objectSize);
    for (auto it = scopes.begin(); it != scopes.end(); ++it) {
        buffer = this->copyString(buffer, it->first, objectSize);
        buffer = this->copyBool(buffer, it->second, objectSize);
    }

    int numOfwithheldInCountries = this->withheldInCountries.size();
    buffer = copyInt(buffer, numOfwithheldInCountries, objectSize);
    for (int i = 0; i < numOfwithheldInCountries; i++) {
        buffer = copyString(buffer, this->withheldInCountries.at(i), objectSize);
    }

    if (this->coordinates != nullptr) {
        buffer = copyBool(buffer, false, objectSize);
        buffer = this->coordinates->serializeHandcoded(buffer, objectSize);
    } else
        buffer = copyBool(buffer, true, objectSize);

    if (this->entities != nullptr) {
        buffer = copyBool(buffer, false, objectSize);
        buffer = this->entities->serializeHandcoded(buffer, objectSize);
    } else
        buffer = copyBool(buffer, true, objectSize);

    buffer = this->user->serializeHandcoded(buffer, objectSize);

    if (this->extendedEntities != nullptr) {
        buffer = copyBool(buffer, false, objectSize);
        buffer = this->extendedEntities->serializeHandcoded(buffer, objectSize);
    } else
        buffer = copyBool(buffer, true, objectSize);


    if (this->quotedStatus != nullptr) {
        buffer = copyBool(buffer, false, objectSize);
        buffer = this->quotedStatus->serializeHandcoded(buffer, objectSize);
    } else
        buffer = copyBool(buffer, true, objectSize);

    if (this->retweetedStatus != nullptr) {
        buffer = copyBool(buffer, false, objectSize);
        buffer = this->retweetedStatus->serializeHandcoded(buffer, objectSize);
    } else
        buffer = copyBool(buffer, true, objectSize);

    if (this->place != nullptr) {
        buffer = copyBool(buffer, false, objectSize);
        buffer = this->place->serializeHandcoded(buffer, objectSize);
    } else
        buffer = copyBool(buffer, true, objectSize);

    int numOfMatchingRules = this->matchingRules.size();
    buffer = copyInt(buffer, numOfMatchingRules, objectSize);
    for (int i = 0; i < numOfMatchingRules; i++) {
        buffer = this->matchingRules.at(i)->serializeHandcoded(buffer, objectSize);
    }

    //cout<<this->toJSON()<<endl;

    return buffer;
}


TweetStatus *TweetStatus::deserializeHandcoded(char *buffer, int &bytesRead) {

    // Integer elements
    this->replyCount = parseInt(buffer + bytesRead);
    bytesRead += sizeof(this->replyCount);
    this->retweetCount = parseInt(buffer + bytesRead);
    bytesRead += sizeof(this->retweetCount);
    this->quoteCount = parseInt(buffer + bytesRead);
    bytesRead += sizeof(this->quoteCount);
    this->favoriteCount = parseInt(buffer + bytesRead);
    bytesRead += sizeof(this->favoriteCount);

    // Long elements
    this->id = parseLong(buffer + bytesRead);
    bytesRead += sizeof(this->id);
    this->quotedStatusId = parseLong(buffer + bytesRead);
    bytesRead += sizeof(this->quotedStatusId);
    this->inReplyToStatusId = parseLong(buffer + bytesRead);
    bytesRead += sizeof(this->inReplyToStatusId);
    this->inReplyToUserId = parseLong(buffer + bytesRead);
    bytesRead += sizeof(this->inReplyToUserId);
    this->currentUserRetweetedId = parseLong(buffer + bytesRead);
    bytesRead += sizeof(this->currentUserRetweetedId);

    // Boolean elements
    this->isTruncated = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->isTruncated);
    this->isRetweeted = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->isRetweeted);
    this->isQuoteStatus = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->isQuoteStatus);
    this->isFavorited = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->isFavorited);
    this->isPossiblySensitive = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->isPossiblySensitive);
    this->withheldCopyright = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->withheldCopyright);

    //Parse Strings:
    parseString(buffer + bytesRead, this->createdAt);
    bytesRead += (sizeof(int) + this->createdAt.length());
    parseString(buffer + bytesRead, this->text);
    bytesRead += (sizeof(int) + this->text.length());
    parseString(buffer + bytesRead, this->source);
    bytesRead += (sizeof(int) + this->source.length());
    parseString(buffer + bytesRead, this->inReplyToScreenName);
    bytesRead += (sizeof(int) + this->inReplyToScreenName.length());
    parseString(buffer + bytesRead, this->lang);
    bytesRead += (sizeof(int) + this->lang.length());
    parseString(buffer + bytesRead, this->filterLevel);
    bytesRead += (sizeof(int) + this->filterLevel.length());
    parseString(buffer + bytesRead, this->withheldScope);
    bytesRead += (sizeof(int) + this->withheldScope.length());

    int numOfScopes = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfScopes);
    for (int i = 0; i < numOfScopes; i++) {
        string key;
        parseString(buffer + bytesRead, key);
        bytesRead += (sizeof(int) + key.length());

        bool value;
        value = parseBool(buffer + bytesRead);
        bytesRead += sizeof(value);

        scopes[key] = value;
    }

    int numOfwithheldInCountries = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfwithheldInCountries);
    for (int i = 0; i < numOfwithheldInCountries; i++) {
        string tempstring;
        parseString(buffer + bytesRead, tempstring);
        bytesRead += (sizeof(int) + tempstring.length());
        this->withheldInCountries.push_back(tempstring);
    }

    bool checknullptr;
    //CoordinatesHC:
    checknullptr = parseBool(buffer + bytesRead);
    bytesRead += sizeof(checknullptr);
    if (!checknullptr) {
        this->coordinates = new Coordinates();
        this->coordinates->deserializeHandcoded(buffer, bytesRead);
    } else
        this->coordinates = nullptr;

    //EntitiesHC:
    checknullptr = parseBool(buffer + bytesRead);
    bytesRead += sizeof(checknullptr);
    if (!checknullptr) {
        this->entities = new Entities();
        this->entities->deserializeHandcoded(buffer, bytesRead);
    } else
        this->entities = nullptr;

    //UserHC:
    this->user = new User();
    this->user->deserializeHandcoded(buffer, bytesRead);

    //ExntendedEntitiesHC:
    checknullptr = parseBool(buffer + bytesRead);
    bytesRead += sizeof(checknullptr);
    if (!checknullptr) {
        this->extendedEntities = new ExtendedEntities();
        this->extendedEntities->deserializeHandcoded(buffer, bytesRead);
    } else
        this->extendedEntities = nullptr;

    //Quoted Status:
    checknullptr = parseBool(buffer + bytesRead);
    bytesRead += sizeof(checknullptr);
    if (!checknullptr) {
        this->quotedStatus = new TweetStatus();
        this->quotedStatus->deserializeHandcoded(buffer, bytesRead);

    } else
        this->quotedStatus = nullptr;

    //Retweeted Status:
    checknullptr = parseBool(buffer + bytesRead);
    bytesRead += sizeof(checknullptr);
    if (!checknullptr) {
        this->retweetedStatus = new TweetStatus();
        this->retweetedStatus->deserializeHandcoded(buffer, bytesRead);
    } else
        this->retweetedStatus = nullptr;

    //Place:
    checknullptr = parseBool(buffer + bytesRead);
    bytesRead += sizeof(checknullptr);
    if (!checknullptr) {
        this->place = new Place();
        this->place->deserializeHandcoded(buffer, bytesRead);
    } else
        this->place = nullptr;

    int numOfMatchingRules = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfMatchingRules);
    for (int i = 0; i < numOfMatchingRules; i++) {
        this->matchingRules.push_back(new MatchingRulesEntity());
        this->matchingRules.at(i)->deserializeHandcoded(buffer, bytesRead);
    }
    return this;
}

//Boost serialization method:
char *TweetStatus::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    TweetStatus *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);

    //Serialize:
    oa << T;

    //Now, serialize the object.
    char *tempBuffer = buffer;

    //Copy String:
    copyString(tempBuffer, ss.str(), objectSize);

    return buffer;
}

//Boost de-serialization:
TweetStatus *TweetStatus::deserializeBoost(char *buffer, int &bytesRead) {

    TweetStatus *boostObject=this; //new TweetStatus();

    //Use this subsequently:
    char *tempBuffer = buffer;

    //Parse "length" of the string.
    int sizeofString;
    memcpy(&sizeofString, tempBuffer, sizeof(int));
    tempBuffer += sizeof(int);
    bytesRead += sizeof(int);

    //Create stream on heap: Keep stream alive:
    stringstream *rs= new stringstream();
    rs->write(tempBuffer, sizeofString);
    bytesRead += sizeofString;

    //Create archive on heap: Keep stream alive:
    boost::archive::text_iarchive *ia = new boost::archive::text_iarchive(*rs, boost::archive::no_header);
    (*ia) >> boostObject;

    ia->delete_created_pointers();
    delete ia;
    delete rs;
    return boostObject;
}

//proto serialization:
char *TweetStatus::serializeProto(char *buffer, int &objectSize) {
    return nullptr;
}

//Proto de-serialization:
TweetStatus *TweetStatus::deserializeProto(char *buffer, int &bytesRead) {
    return nullptr;
}

TweetStatus *TweetStatus::deserializeInPlace(char *buffer) {
    return nullptr;
}

//Implement your own custom comparator:
bool TweetStatus::operator<(TweetStatus &other) {

    int countLevel = 0;
    int countLevelOtherTweet = 0;

    // get text
    countLevel += this->text.length();

    countLevelOtherTweet += other.text.length();

    // get QuoteStatus
    if (this->quotedStatus != nullptr)
        countLevel += this->quotedStatus->text.length();

    if (other.quotedStatus != nullptr)
        countLevelOtherTweet += other.quotedStatus->text.length();

    // get Retweet
    if (this->retweetedStatus != nullptr)
        countLevel += this->retweetedStatus->retweetCount;

    if (other.retweetedStatus != nullptr)
        countLevelOtherTweet += other.retweetedStatus->retweetCount;
    return countLevel < countLevelOtherTweet;
}

int TweetStatus::getOrder() {
    int countLevel = 0;

    // get text
    countLevel += this->text.length();

    // get QuoteStatus
    if (this->quotedStatus != nullptr)
        countLevel += this->quotedStatus->text.length();

    // get Retweet
    if (this->retweetedStatus != nullptr)
        countLevel += this->retweetedStatus->retweetCount;

    return countLevel;
}
TweetStatus::TweetStatus(bool isPointer) : isPointer(isPointer) {}







