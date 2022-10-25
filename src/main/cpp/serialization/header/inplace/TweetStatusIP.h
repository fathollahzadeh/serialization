#ifndef TWITTER_TWEETSTATUSIP_H
#define TWITTER_TWEETSTATUSIP_H

#include <Object.h>
#include "UserIP.h"
#include "TweetStatus.h"
#include "CoordinatesIP.h"
#include "PlaceIP.h"
#include "EntitiesIP.h"
#include "MatchingRulesEntityIP.h"
#include "ExtendedTweetIP.h"

class TweetStatusIP : public Object {

public:
	int objectsize;
	offset_ptr<char> createdAt;
	long id;
    offset_ptr<char> id_str;
	offset_ptr<char> text;
	offset_ptr<char> source;
	bool isTruncated;
	long inReplyToStatusId;//nullable
	long inReplyToUserId;//nullable
	offset_ptr<char> inReplyToScreenName;//nullable*/
	offset_ptr<UserIP> user;
	offset_ptr<CoordinatesIP> coordinates;//nullable
	bool hasCoordinates;
	offset_ptr<PlaceIP> place;//nullable
	bool hasPlace;
	long quotedStatusId;
	bool isQuoteStatus;
	offset_ptr<TweetStatusIP> quotedStatus;
	bool hasQuotedStatus;
	offset_ptr<TweetStatusIP> retweetedStatus;
	bool hasRetweetedStatus;
	int quoteCount;//nullable
	int replyCount;
	int retweetCount;
	int favoriteCount;//nullable
	offset_ptr<EntitiesIP> entities;
	bool hasEntities;
	offset_ptr<ExtendedTweetIP> extendedTweet; //nullable
	bool hasExtendedTweet; //nullable
	bool isFavorited;//nullable
	bool isRetweeted;
	bool isPossiblySensitive;//nullable
	offset_ptr<char> filterLevel;
	offset_ptr<char> lang;//nullable
	offset_ptr<MatchingRulesEntityIP> matchingRules;
	int numOfMatchingRulesEntity;
	long currentUserRetweetedId;//nullable
	//map<string,bool> scopes;//nullable
	bool withheldCopyright;//nullable
	//offset_ptr<vector<string>> withheldInCountries;
	//int numOfWithheldInCountries;
	//vector<string> withheldInCountries;//nullable
	offset_ptr<char> withheldScope;//nullable

public:

	TweetStatusIP();

	TweetStatusIP(bool isPointer);

	virtual ~TweetStatusIP();

	// Create an InPlace object:
	TweetStatusIP(TweetStatus *tweetStatus);

	void serialize(TweetStatus *tweetStatus);

	//Implement your own custom comparator:
	bool operator<(TweetStatusIP &other);

	//print order number:
	int getOrder();

};


#endif //TWITTER_TWEETSTATUSIP_H
