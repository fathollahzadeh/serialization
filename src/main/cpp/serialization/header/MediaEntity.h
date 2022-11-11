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

#ifndef MediaEntity_H
#define MediaEntity_H

#include <iostream>
#include <cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"
#include "MediaSizesEntity.h"
#include "VariantEntity.h"
#include "VideoEntity.h"
#include "AdditionalMediaInfoEntity.h"


using namespace std;

class MediaEntity : public RootData {

private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {

		// Simply list all the fields to be serialized/deserialized.
		ar & displayURL;
		ar & expandedURL;
		ar & id;
        ar & idStr;
		ar & indices;
		ar & mediaURL;
		ar & mediaURLHttps;
		ar & BOOST_SERIALIZATION_NVP(sizes);
		ar & type;
		ar & sourceStatusId;
		ar & sourceStatusIdStr;
		ar & url;
		ar & BOOST_SERIALIZATION_NVP(videoInfo);
		ar & BOOST_SERIALIZATION_NVP(additionalMediaInfo);

	}

public:
    string displayURL;
    string expandedURL;
    long id;
    string idStr;
    vector<int> indices;
    string mediaURL;
    string mediaURLHttps;
    MediaSizesEntity *sizes;
    string type;
    long sourceStatusId;
    string sourceStatusIdStr;
    string url;
    VideoEntity *videoInfo;
    AdditionalMediaInfoEntity *additionalMediaInfo;

	//Default destructor:
	virtual ~MediaEntity();

	//Default constructor:
	MediaEntity();

	//Constructor with arguments:
	MediaEntity(string displayURL, string expandedURL, long id, string idStr, vector<int> indices, string mediaURL,
				string mediaURLHttps, MediaSizesEntity *sizes, long sourceStatusId, string sourceStatusIdStr,
                string type, string url, VideoEntity *videoInfo, AdditionalMediaInfoEntity *additionalMediaInfo);

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	MediaEntity *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON buffer serialization
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	MediaEntity *deserializeBSON(bsoncxx::document::view doc);

};

BOOST_CLASS_TRACKING(MediaEntity, boost::serialization::track_never)

#endif
