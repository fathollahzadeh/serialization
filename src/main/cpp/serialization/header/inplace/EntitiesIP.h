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

#ifndef TWITTER_ENTITIESIP_H
#define TWITTER_ENTITIESIP_H

#include "HashtagEntity.h"
#include "MediaEntity.h"
#include "URLEntity.h"
#include "UserMentionEntity.h"
#include "SymbolEntity.h"
#include "PollEntity.h"
#include "Entities.h"
#include "Object.h"
#include "HashtagEntityIP.h"
#include "MediaEntityIP.h"
#include "URLEntityIP.h"
#include "UserMentionEntityIP.h"
#include "SymbolEntityIP.h"
#include "PollEntityIP.h"

class EntitiesIP : public Object {

private:
	offset_ptr<HashtagEntityIP> hashtags;
	int numOfHashtagEntity;
	offset_ptr<MediaEntityIP> media;
	int numOfMediaEntity;
	offset_ptr<URLEntityIP> urls;
	int numOfURLEntity;
	offset_ptr<UserMentionEntityIP> userMentions;
	int numOfUserMentionEntity;
	offset_ptr<SymbolEntityIP> symbols;
	int numOfSymbolEntity;
	offset_ptr<PollEntityIP> polls;
	int numOfPollEntity;

public:
	EntitiesIP();

	virtual ~EntitiesIP();

	//Create InPlace object:
	EntitiesIP(Entities *entities);

	void serialize(Entities *entities);
};

#endif //TWITTER_ENTITIESIP_H
