#ifndef TWITTER_TWEETSTATUSPROTO_H
#define TWITTER_TWEETSTATUSPROTO_H


#include <TweetStatus.h>

#include "TweetStatusP.pb.h"


class TweetStatusProto : public RootData {

private:

	proto::TweetStatusP *proto;

	void setMediaEntityP(proto::MediaEntityP *mediaEntityP, MediaEntity *mediaEntity);

	void setSizeEntityP(proto::SizeEntityP *sizeEntityP, SizeEntity *sizeEntity);

	bool isPointer;

public:

	int objectsize = 0;

	TweetStatusProto();

	TweetStatusProto(bool isPointer);

	virtual ~TweetStatusProto();

	// Create an proto object:
	TweetStatusProto(TweetStatus *tweetStatus);

	//Proto buffer serialization
	char *serializeProto(char *buffer, int &objectSize);

	//proto buffer de-serialization
	TweetStatusProto *deserializeProto(char *buffer, int &bytesRead);

	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	TweetStatusProto *deserializeHandcoded(char *buffer, int &bytesRead);

	//Boost serialization:
	char *serializeBoost(char *buffer, int &objectSize);

	//Boost de-serialization:
	TweetStatusProto *deserializeBoost(char *buffer, int &bytesRead);

	TweetStatusProto *deserializeInPlace(char *buffer);

	//BSON buffer serialization
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	TweetStatusProto *deserializeBSON(bsoncxx::document::view doc);

	//flatbuffers buffer serialization
	void serializeFlatBuffers(char *buffer, int &objectSize);

	//proto buffer de-serialization
	TweetStatusProto *deserializeFlatBuffers(char *buffer, int &bytesRead);

	void setBsonDoc(bsoncxx::document::value bsonDoc);

	proto::TweetStatusP *getProto() const;

	bool operator<(TweetStatusProto &other);
};


#endif //TWITTER_TWEETSTATUSPROTO_H
