#ifndef TweetStatus_H
#define TweetStatus_H

#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "Coordinates.h"
#include "Place.h"
#include "User.h"
#include "RootData.h"
#include "Entities.h"
#include "ExtendedEntities.h"
#include "MatchingRulesEntity.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

class TweetStatus : public RootData {

public:
	int objectsize;
	string createdAt;
	long id;
	string text;
	string source;
	bool isTruncated;
	long inReplyToStatusId;//nullable
	long inReplyToUserId;//nullable
	string inReplyToScreenName;//nullable
	User *user;
	Coordinates *coordinates;//nullable
	Place *place;//nullable
	long quotedStatusId;
	bool isQuoteStatus;
	TweetStatus *quotedStatus;
	TweetStatus *retweetedStatus;
	int quoteCount;//nullable
	int replyCount;
	int retweetCount;
	int favoriteCount;//nullable
	Entities *entities;
	ExtendedEntities *extendedEntities;
	bool isFavorited;//nullable
	bool isRetweeted;
	bool isPossiblySensitive;//nullable
	string filterLevel;
	string lang;//nullable
	vector<MatchingRulesEntity *> matchingRules;
	long currentUserRetweetedId;//nullable
	map<string, bool> scopes;//nullable
	bool withheldCopyright;//nullable
	vector <string> withheldInCountries;//nullable
	string withheldScope;//nullable

	bsoncxx::document::value bsonDoc = bsoncxx::document::value(nullptr, 0, nullptr);
	bool hasBsonDoc;

	bool isPointer;

private:

	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {

		// Simply list all the fields to be serialized/deserialized.
		ar & createdAt;
		ar & id;
		ar & text;
		ar & source;
		ar & isTruncated;
		ar & inReplyToStatusId;
		ar & inReplyToUserId;
		ar & inReplyToScreenName;
		ar & user;
		ar & BOOST_SERIALIZATION_NVP(coordinates);
		ar & BOOST_SERIALIZATION_NVP(place);
		ar & quotedStatusId;
		ar & isQuoteStatus;
		ar & BOOST_SERIALIZATION_NVP(quotedStatus);
		ar & BOOST_SERIALIZATION_NVP(retweetedStatus);
		ar & quoteCount;
		ar & replyCount;
		ar & retweetCount;
		ar & favoriteCount;
		ar & BOOST_SERIALIZATION_NVP(entities);
		ar & BOOST_SERIALIZATION_NVP(extendedEntities);
		ar & isFavorited;
		ar & isRetweeted;
		ar & isPossiblySensitive;
		ar & filterLevel;
		ar & lang;
		for (int i = 0; i < matchingRules.size(); ++i) {
			ar & *matchingRules[i];
		}
		ar & currentUserRetweetedId;
		ar & scopes;
		ar & withheldCopyright;
		ar & withheldInCountries;
		ar & withheldScope;
	}

public:

	//Default destructor:
	virtual ~TweetStatus();

	//Default constructor:
	TweetStatus();

	TweetStatus(bool isPointer);

	TweetStatus(string createdAt, long id, string text, string source,
				bool isTruncated, long inReplyToStatusId, long inReplyToUserId,
				string inReplyToScreenName, User *user, Coordinates *coordinates,
				Place *place, long quotedStatusId, bool isQuoteStatus, TweetStatus *quotedStatus,
				TweetStatus *retweetedStatus, int quoteCount, int replyCount, int retweetCount,
				int favoriteCount, Entities *entities, ExtendedEntities *extendedEntities,
				bool isFavorited, bool isRetweeted, bool isPossiblySensitive, string filterLevel,
				string lang, vector<MatchingRulesEntity *> matchingRules,
				long currentUserRetweetedId, map<string, bool> scopes, bool withheldCopyright,
				vector <string> withheldInCountries, string withheldScope);


	//C++: Use explicitly for printing.
	string toJSON();

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	TweetStatus *deserializeHandcoded(char *buffer, int &bytesRead);

	//Boost serialization:
	char *serializeBoost(char *buffer, int &objectSize);

	//Boost de-serialization:
	TweetStatus *deserializeBoost(char *buffer, int &bytesRead);

	//Proto buffer serialization
	char *serializeProto(char *buffer, int &objectSize);

	//proto buffer de-serialization
	TweetStatus *deserializeProto(char *buffer, int &bytesRead);

	TweetStatus *deserializeInPlace(char *buffer);

	//BSON buffer serialization
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	TweetStatus *deserializeBSON(bsoncxx::document::view doc);

	//Implement your own custom comparator:
	bool operator<(TweetStatus &other);

	//flatbuffers buffer serialization
	void serializeFlatBuffers(char *buffer, int &objectSize);

	//proto buffer de-serialization
	TweetStatus *deserializeFlatBuffers(char *buffer, int &bytesRead);

	//print order number:

	int getOrder();

	void setBsonDoc(bsoncxx::document::value bsonDoc);

};

BOOST_CLASS_TRACKING(TweetStatus, boost::serialization::track_never
)

#endif
