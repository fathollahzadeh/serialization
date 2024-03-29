#include "TweetStatusIP.h"

TweetStatusIP::TweetStatusIP() {}

TweetStatusIP::~TweetStatusIP() {}


TweetStatusIP::TweetStatusIP(TweetStatus *tweetStatus) {
	this->serialize(tweetStatus);
}

void TweetStatusIP::serialize(TweetStatus *tweetStatus) {
	this->createdAt = malloc<char>(strlen(tweetStatus->createdAt.c_str()) + 1);
	strcpy(this->createdAt, tweetStatus->createdAt.c_str());

	this->id = tweetStatus->id;

    this->id_str = malloc<char>(strlen(tweetStatus->idStr.c_str()) + 1);
    strcpy(this->id_str, tweetStatus->idStr.c_str());

	this->text = malloc<char>(strlen(tweetStatus->text.c_str()) + 1);
	strcpy(this->text, tweetStatus->text.c_str());

	this->source = malloc<char>(strlen(tweetStatus->source.c_str()) + 1);
	strcpy(this->source, tweetStatus->source.c_str());

	this->isTruncated = tweetStatus->isTruncated;
	this->inReplyToStatusId = tweetStatus->inReplyToStatusId;
	this->inReplyToUserId = tweetStatus->inReplyToUserId;

	this->inReplyToScreenName = malloc<char>(strlen(tweetStatus->inReplyToScreenName.c_str()) + 1);
	strcpy(this->inReplyToScreenName, tweetStatus->inReplyToScreenName.c_str());

	this->user = new UserIP[1];
	this->user[0].serialize(tweetStatus->user);

	if (tweetStatus->coordinates != nullptr) {
		this->hasCoordinates = true;
		this->coordinates = new CoordinatesIP[1];
		this->coordinates[0].serialize(tweetStatus->coordinates);
	} else
		this->hasCoordinates = false;

	if (tweetStatus->place != nullptr) {
		this->hasPlace = true;
		this->place = new PlaceIP[1];
		this->place[0].serialize(tweetStatus->place);
	} else
		this->hasPlace = false;

	this->quotedStatusId = tweetStatus->quotedStatusId;
	this->isQuoteStatus = tweetStatus->isQuoteStatus;

	if (tweetStatus->quotedStatus != nullptr) {
		this->hasQuotedStatus = true;
		this->quotedStatus = new TweetStatusIP[1];
		this->quotedStatus[0].serialize(tweetStatus->quotedStatus);

	} else
		this->hasQuotedStatus = false;


	if (tweetStatus->retweetedStatus != nullptr) {
		this->hasRetweetedStatus = true;
		this->retweetedStatus = new TweetStatusIP[1];
		this->retweetedStatus[0].serialize(tweetStatus->retweetedStatus);
	} else
		this->hasRetweetedStatus = false;

	this->quoteCount = tweetStatus->quoteCount;
	this->replyCount = tweetStatus->replyCount;
	this->retweetCount = tweetStatus->retweetCount;
	this->favoriteCount = tweetStatus->favoriteCount;

	if (tweetStatus->entities != nullptr) {
		this->hasEntities = true;
		this->entities = new EntitiesIP[1];
		this->entities[0].serialize(tweetStatus->entities);
	} else
		this->hasEntities = false;

	if (tweetStatus->extendedTweet != nullptr) {
		this->hasExtendedTweet = false;
		this->extendedTweet = new ExtendedTweetIP[1];
		this->extendedTweet[0].serialize(tweetStatus->extendedTweet);
	} else
		this->hasExtendedTweet = false;

	this->isFavorited = tweetStatus->isFavorited;
	this->isRetweeted = tweetStatus->isRetweeted;
	this->isPossiblySensitive = tweetStatus->isPossiblySensitive;

	this->filterLevel = malloc<char>(strlen(tweetStatus->filterLevel.c_str()) + 1);
	strcpy(this->filterLevel, tweetStatus->filterLevel.c_str());

	this->lang = malloc<char>(strlen(tweetStatus->lang.c_str()) + 1);
	strcpy(this->lang, tweetStatus->lang.c_str());

	this->numOfMatchingRulesEntity = tweetStatus->matchingRules.size();
	this->matchingRules = new MatchingRulesEntityIP[this->numOfMatchingRulesEntity];
	for (int i = 0; i < this->numOfMatchingRulesEntity; ++i) {
		this->matchingRules[i].serialize(tweetStatus->matchingRules.at(i));
	}

	this->currentUserRetweetedId = tweetStatus->currentUserRetweetedId;

	//TODO: implement InPlace for Map:
	// map<string,string> scopes;//nullable
	this->withheldCopyright = tweetStatus->withheldCopyright;

	//TODO: implement InPlace for vector:
	//vector<string> withheldInCountries;//nullable
	// this->numOfWithheldInCountries=2;//tweetStatus->withheldInCountries.size();

//    vector<string> tv;
//    this->withheldInCountries=&tv;
//    for (int j = 0; j <this->numOfWithheldInCountries ; ++j) {
//        string aa="saeed";
//        offset_ptr<char > ts=malloc < char > (strlen(aa.c_str()) + 1);;
//        strcpy(ts, aa.c_str());
//        tv.push_back(string(ts));
//
//       // this->withheldInCountries[j]=malloc < char > (strlen(aa.c_str()) + 1);
//       // strcpy(this->withheldInCountries[j], aa.c_str());
//    }

	this->withheldScope = malloc<char>(strlen(tweetStatus->withheldScope.c_str()) + 1);
	strcpy(this->withheldScope, tweetStatus->withheldScope.c_str());

}

//Implement your own custom comparator:
bool TweetStatusIP::operator<(TweetStatusIP &other) {

	int countLevel = 0;
	int countLevelOtherTweet = 0;

	// get text
	countLevel += string(this->text).length();

	countLevelOtherTweet += string(other.text).length();

	// get QuoteStatus
	if (this->hasQuotedStatus)
		countLevel += string(this->quotedStatus->text).length();

	if (other.hasQuotedStatus)
		countLevelOtherTweet += string(other.quotedStatus->text).length();

	// get Retweet
	if (this->hasRetweetedStatus)
		countLevel += this->retweetedStatus->retweetCount;

	if (other.hasRetweetedStatus)
		countLevelOtherTweet += other.retweetedStatus->retweetCount;
	return countLevel < countLevelOtherTweet;
}

int TweetStatusIP::getOrder() {

	int countLevel = 0;

	// get text
	countLevel += string(this->text).length();

	// get QuoteStatus
	if (this->hasQuotedStatus)
		countLevel += string(this->quotedStatus->text).length();

	// get Retweet
	if (this->hasRetweetedStatus)
		countLevel += this->retweetedStatus->retweetCount;

	return countLevel;
}

