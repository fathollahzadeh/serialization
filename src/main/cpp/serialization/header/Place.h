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

#ifndef Place_H
#define Place_H

#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"
#include "BoundingBoxCoordinate.h"

using namespace std;

class Place : public RootData {

public:
	string name;
	string countryCode;
	string id;
	string country;
	string placeType;
	string url;
	string fullName;
	BoundingBoxCoordinate *boundingBoxCoordinates;

private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {

		// Simply list all the fields to be serialized/deserialized.
		ar & name;
		ar & countryCode;
		ar & id;
		ar & country;
		ar & placeType;
		ar & url;
		ar & fullName;
		ar & BOOST_SERIALIZATION_NVP(boundingBoxCoordinates);

	}

public:
	//Default destructor:
	virtual ~Place();

	//Default constructor:
	Place();

	//Constructor with arguments:
	Place(string name, string countryCode, string id, string country, string placeType, string url, string fullName,
		  BoundingBoxCoordinate *boundingBoxCoordinates);

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	Place *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON buffer serialization
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	Place *deserializeBSON(bsoncxx::document::view doc);
};

BOOST_CLASS_TRACKING(Place, boost::serialization::track_never
)

#endif
