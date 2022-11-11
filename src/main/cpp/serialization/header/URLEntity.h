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

#ifndef URLEntity_H
#define URLEntity_H


#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"

using namespace std;

class URLEntity : public RootData {

public:
	vector<int> indices;
	string displayURL;
	string expandedURL;
	string url;
private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {

		// Simply list all the fields to be serialized/deserialized.
		ar & indices;
		ar & displayURL;
		ar & expandedURL;
		ar & url;

	}

public:
	//Default destructor:
	virtual ~URLEntity();

	//Copy constructor:
	URLEntity(const URLEntity &obj);

	//Default constructor:
	URLEntity();

	//Constructor with arguments:
	URLEntity(vector<int> indices, string displayURL, string expandedURL, string url);

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	URLEntity *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON buffer serialization
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	URLEntity *deserializeBSON(bsoncxx::document::view doc);
};

BOOST_CLASS_TRACKING(URLEntity, boost::serialization::track_never
)
#endif
