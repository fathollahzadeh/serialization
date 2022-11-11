/*
* Copyright 2022 Saeed Fathollahzadeh. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef TWITTER_TWEETSTATUSPROTO_H
#define TWITTER_TWEETSTATUSPROTO_H


#include <TweetStatus.h>

#include "TweetStatusP.pb.h"


class TweetStatusProto : public RootData {

private:

	proto::TweetStatusP *proto;

	void setMediaEntityP(proto::MediaEntityP *mediaEntityP, MediaEntity *mediaEntity);

	void setSizeEntityP(proto::SizeEntityP *sizeEntityP, SizeEntity *sizeEntity);

    void setEntities(Entities *entities, proto::EntitiesP *entitiesP);

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
