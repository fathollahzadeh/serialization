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


#ifndef Entities_H
#define Entities_H

#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"
#include "HashtagEntity.h"
#include "MediaEntity.h"
#include "URLEntity.h"
#include "UserMentionEntity.h"
#include "SymbolEntity.h"
#include "PollEntity.h"

using namespace std;

class Entities : public RootData {

public:
	vector<HashtagEntity *> hashtags;
	vector<MediaEntity *> media;
	vector<URLEntity *> urls;
	vector<UserMentionEntity *> userMentions;
	vector<SymbolEntity *> symbols;
	vector<PollEntity *> polls;
private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		// Simply list all the fields to be serialized/deserialized.
		ar & hashtags;
		ar & media;
		ar & urls;
		ar & userMentions;
		ar & symbols;
		ar & polls;

	}

public:
	//Default destructor:
	virtual ~Entities();

	//Copy constructor:
	Entities(const Entities &obj);

	//Default constructor:
	Entities();

	//Constructor with arguments:
	Entities(vector<HashtagEntity *> hashtags, vector<MediaEntity *> media, vector<URLEntity *> urls,
			 vector<UserMentionEntity *> userMentions, vector<SymbolEntity *> symbols,
			 vector<PollEntity *> polls);

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	Entities *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON buffer serialization
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	Entities *deserializeBSON(bsoncxx::document::view doc);

};

BOOST_CLASS_TRACKING(Entities, boost::serialization::track_never
)

#endif
