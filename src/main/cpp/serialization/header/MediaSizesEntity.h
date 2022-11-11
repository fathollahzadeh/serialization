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

#ifndef MediaSizesEntity_H
#define MediaSizesEntity_H


#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"
#include "SizeEntity.h"

using namespace std;

class MediaSizesEntity : public RootData {

public:
	SizeEntity *thumb;
	SizeEntity *large;
	SizeEntity *medium;
	SizeEntity *small;
private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {

		// Simply list all the fields to be serialized/deserialized.
		ar & BOOST_SERIALIZATION_NVP(thumb);
		ar & BOOST_SERIALIZATION_NVP(large);
		ar & BOOST_SERIALIZATION_NVP(medium);
		ar & BOOST_SERIALIZATION_NVP(small);

	}

public:
	//Default destructor:
	virtual ~MediaSizesEntity();

	//Default constructor:
	MediaSizesEntity();
	//Constructor with arguments:
	//MediaSizesEntity(SizeEntityHC thumb, SizeEntityHC large, SizeEntityHC medium, SizeEntityHC small);

	MediaSizesEntity(SizeEntity *thumb, SizeEntity *large, SizeEntity *medium, SizeEntity *small);

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	MediaSizesEntity *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON buffer serialization
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	MediaSizesEntity *deserializeBSON(bsoncxx::document::view doc);

};

BOOST_CLASS_TRACKING(MediaSizesEntity, boost::serialization::track_never
)
#endif
