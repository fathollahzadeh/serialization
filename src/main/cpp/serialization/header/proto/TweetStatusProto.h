#ifndef TWITTER_TWEETSTATUSPROTO_H
#define TWITTER_TWEETSTATUSPROTO_H


#include <TweetStatus.h>

#include "TweetStatusP.pb.h"


class TweetStatusProto : public RootData {

private:

	proto::TweetStatusP *proto;

	void setMediaEntityP(proto::MediaEntityP *mediaEntityP, MediaEntity *mediaEntity);

	void setSizeEntityP(proto::SizeEntityP *sizeEntityP, SizeEntity *sizeEntity);

    proto::EntitiesP *setEntities(Entities *entities, proto::EntitiesP *entitiesP);

	bool isPointer = false;

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

	proto::TweetStatusP *getProto() const;

	bool operator<(TweetStatusProto &other);
};


#endif //TWITTER_TWEETSTATUSPROTO_H
