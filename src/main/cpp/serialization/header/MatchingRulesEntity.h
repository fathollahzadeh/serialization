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

#ifndef C_MATCHINGRULESENTITY_H
#define C_MATCHINGRULESENTITY_H

#include "RootData.h"
#include <iostream>

using namespace std;

class MatchingRulesEntity : public RootData {
public:
	string tag;
	long id;
	string idStr;
private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		// Simply list all the fields to be serialized/deserialized.
		ar & tag;
		ar & id;
		ar & idStr;
	}

public:
	MatchingRulesEntity();

	virtual ~MatchingRulesEntity();

	MatchingRulesEntity(const string &tag, long id, const string &idStr);

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	MatchingRulesEntity *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON C++ serialization:
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	MatchingRulesEntity *deserializeBSON(bsoncxx::document::view doc);
};

BOOST_CLASS_TRACKING(MatchingRulesEntity, boost::serialization::track_never
)

#endif //C_MATCHINGRULESENTITY_H
