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
	this->isPointer = true;
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
						 vector <string> withheldInCountries, string withheldScope) {
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
	this->isPointer = true;
	this->hasBsonDoc = false;

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

	TweetStatus *boostObject = this; //new TweetStatus();

	//Use this subsequently:
	char *tempBuffer = buffer;

	//Parse "length" of the string.
	int sizeofString;
	memcpy(&sizeofString, tempBuffer, sizeof(int));
	tempBuffer += sizeof(int);
	bytesRead += sizeof(int);

	//Create stream on heap: Keep stream alive:
	stringstream *rs = new stringstream();
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

bsoncxx::document::value TweetStatus::serializeBSON() {

	if (this->hasBsonDoc) {
		return this->bsonDoc;
	}

	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::array;
	using bsoncxx::builder::stream::open_array;
	using bsoncxx::builder::stream::close_array;
	using bsoncxx::builder::stream::open_document;
	using bsoncxx::builder::stream::close_document;

	document doc = document{};
	doc << "created_at" << this->createdAt <<
		"id" << this->id <<
		"text" << this->text <<
		"source" << this->source <<
		"truncated" << this->isTruncated <<
		"in_reply_to_status_id" << bsoncxx::types::b_int64{this->inReplyToStatusId} <<//nullable
		"in_reply_to_user_id" << this->inReplyToUserId <<//nullable
		"in_reply_to_screen_name" << this->inReplyToScreenName << //nullable
		"user" << bsoncxx::types::b_document{this->user->serializeBSON().view()};
	if (this->coordinates != nullptr)
		doc << "coordinates" << bsoncxx::types::b_document{this->coordinates->serializeBSON().view()};
	if (this->place != nullptr) {
		doc << "place" << bsoncxx::types::b_document{this->place->serializeBSON().view()};
	}
	doc << "quoted_status_id" << this->quotedStatusId <<
		"is_quote_status" << this->isQuoteStatus;
	if (this->quotedStatus != nullptr) {
		doc << "quoted_status" << bsoncxx::types::b_document{this->quotedStatus->serializeBSON().view()};
	}
	if (retweetedStatus != nullptr) {
		doc << "retweeted_status" << bsoncxx::types::b_document{this->retweetedStatus->serializeBSON().view()};
	}
	doc << "quote_count" << this->quoteCount <<//nullable
		"reply_count" << this->replyCount <<
		"retweet_count" << this->retweetCount <<
		"favorite_count" << this->favoriteCount <<//nullable
		"entities" << bsoncxx::types::b_document{this->entities->serializeBSON().view()};
	if (this->extendedEntities != nullptr) {
		doc << "extended_entities" << bsoncxx::types::b_document{this->extendedEntities->serializeBSON().view()};
	}
	doc << "favorited" << this->isFavorited <<//nullable
		"retweeted" << this->isRetweeted <<
		"possibly_sensitive" << this->isPossiblySensitive <<//nullable
		"filter_level" << this->filterLevel <<
		"lang" << this->lang;//nullable

	auto arrMatchingRules = array{};

	for (int i = 0; i < this->matchingRules.size(); ++i) {
		arrMatchingRules << bsoncxx::types::b_document{this->matchingRules[i]->serializeBSON().view()};
	}

	doc << "matching_rules" << arrMatchingRules <<
		"current_user_retweet" << this->currentUserRetweetedId << //nullable
		"scopes" << open_document;

	for (auto it = scopes.begin(); it != scopes.end(); ++it) {
		doc << it->first << it->second;
	}
	doc << close_document;
	doc << "withheld_copyright" << this->withheldCopyright;//nullable

	auto arrwithheldInCountries = array{};
	for (int i = 0; i < this->withheldInCountries.size(); ++i) {
		arrwithheldInCountries << this->withheldInCountries[i];
	}
	doc << " withheld_in_countries" << arrwithheldInCountries <<//nullable
		"withheld_scope" << this->withheldScope;
	return doc << finalize;
}

TweetStatus *TweetStatus::deserializeBSON(bsoncxx::document::view doc) {

	bsoncxx::document::element element = doc["created_at"];
	this->createdAt = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["id"];
	this->id = element.type() == bsoncxx::type::k_int64 ? element.get_int64() : element.get_int32();

	element = doc["text"];
	this->text = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["source"];
	this->source = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["truncated"];
	this->isTruncated = element.get_bool().value;

	element = doc["in_reply_to_status_id"];
	this->inReplyToStatusId = element.type() == bsoncxx::type::k_int64 ? element.get_int64() : element.get_int32();

	element = doc["in_reply_to_user_id"];
	this->inReplyToUserId = element.type() == bsoncxx::type::k_int64 ? element.get_int64() : element.get_int32();

	element = doc["in_reply_to_screen_name"];
	this->inReplyToScreenName = bsoncxx::string::to_string(element.get_utf8().value);


	this->user = new User();
	element = doc["user"];
	this->user->deserializeBSON(element.get_document().view());

	element = doc["coordinates"];
	if (element) {
		this->coordinates = new Coordinates();
		this->coordinates->deserializeBSON(element.get_document().view());
	} else
		this->coordinates = nullptr;

	element = doc["place"];
	if (element) {
		this->place = new Place();
		this->place->deserializeBSON(element.get_document().view());
	} else
		this->place = nullptr;

	element = doc["quoted_status_id"];
	this->quotedStatusId = element.type() == bsoncxx::type::k_int64 ? element.get_int64() : element.get_int32();

	element = doc["is_quote_status"];
	this->isQuoteStatus = element.get_bool();

	element = doc["quoted_status"];
	if (element) {
		this->quotedStatus = new TweetStatus();
		this->quotedStatus->deserializeBSON(element.get_document().view());
	} else
		this->quotedStatus = nullptr;

	if (element) {
		this->retweetedStatus = new TweetStatus();
		this->retweetedStatus->deserializeBSON(element.get_document().view());
	} else
		this->retweetedStatus = nullptr;

	element = doc["quote_count"];
	this->quoteCount = element.type() == bsoncxx::type::k_int32 ? element.get_int32() : -1;

	element = doc["reply_count"];
	this->replyCount = element.type() == bsoncxx::type::k_int32 ? element.get_int32() : -1;

	element = doc["retweet_count"];
	this->retweetCount = element.type() == bsoncxx::type::k_int32 ? element.get_int32() : -1;

	element = doc["favorite_count"];
	this->favoriteCount = element.type() == bsoncxx::type::k_int32 ? element.get_int32() : -1;

	element = doc["favorited"];
	this->isFavorited = element.get_bool();

	element = doc["retweeted"];
	this->isRetweeted = element.get_bool();

	element = doc["possibly_sensitive"];
	this->isPossiblySensitive = element.get_bool();

	element = doc["filter_level"];
	this->filterLevel = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["lang"];
	this->lang = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["matching_rules"];
	for (auto ele : element.get_array().value) {
		MatchingRulesEntity *matchingRulesEntity = new MatchingRulesEntity();
		matchingRulesEntity->deserializeBSON(ele.get_document().view());
		this->matchingRules.push_back(matchingRulesEntity);
	}

	element = doc["current_user_retweet"];
	this->currentUserRetweetedId = element.type() == bsoncxx::type::k_int64 ? element.get_int64() : element.get_int32();

	element = doc["withheld_copyright"];
	this->withheldCopyright = element.get_bool();

	element = doc["withheld_in_countries"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele : element.get_array().value) {
			this->withheldInCountries.push_back(bsoncxx::string::to_string(ele.get_utf8().value));
		}
	}

	element = doc["withheld_scope"];
	this->withheldScope = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["scopes"];
	for (bsoncxx::document::element ele : element.get_document().view()) {
		this->scopes[ele.key().to_string()] = ele.get_bool();

	}

	element = doc["entities"];
	this->entities = new Entities();
	this->entities->deserializeBSON(element.get_document().view());

	element = doc["extended_entities"];
	if (element) {
		this->extendedEntities = new ExtendedEntities();
		this->extendedEntities->deserializeBSON(element.get_document().view());
	} else
		this->extendedEntities = nullptr;
	return this;
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

void TweetStatus::serializeFlatBuffers(char *buffer, int &objectSize) {

}

TweetStatus *TweetStatus::deserializeFlatBuffers(char *buffer, int &bytesRead) {
	return nullptr;
}

void TweetStatus::setBsonDoc(bsoncxx::document::value bsonDoc) {
	this->bsonDoc = bsonDoc;
	this->hasBsonDoc = true;
}







