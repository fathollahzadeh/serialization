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

#include "ExtendedEntities.h"

using namespace std;

//Default constructor:
ExtendedEntities::ExtendedEntities() {
}

//Constructor with arguments:
ExtendedEntities::ExtendedEntities(vector<MediaEntity *> media) {
	this->media = media;
}

//Hand Coded C++ serialization:
char *ExtendedEntities::serializeHandcoded(char *buffer, int &objectSize) {
	//Serialize the object.
	//Copy encapsulated objects:
	int numOfMedia = this->media.size();
	buffer = copyInt(buffer, numOfMedia, objectSize);

	for (int i = 0; i < this->media.size(); i++) {
		buffer = this->media.at(i)->serializeHandcoded(buffer, objectSize);
	}
	return buffer;
}


ExtendedEntities *ExtendedEntities::deserializeHandcoded(char *buffer, int &bytesRead) {
	//Encapsulated objects:
	int numOfMedia = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfMedia);

	for (int i = 0; i < numOfMedia; i++) {
		this->media.push_back(new MediaEntity());
		this->media.at(i)->deserializeHandcoded(buffer, bytesRead);
	}
	return this;
}

ExtendedEntities::~ExtendedEntities() {
	//free memory
	for (int i = 0; i < media.size(); ++i) {
		delete media.at(i);
	}
	media.shrink_to_fit();
}

bsoncxx::document::value ExtendedEntities::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::array;

	auto arrmedia = array{};
	for (int i = 0; i < this->media.size(); ++i) {
		arrmedia << bsoncxx::types::b_document{this->media[i]->serializeBSON().view()};
	}
	document doc = document{};
	doc << "media" << arrmedia;

	return doc << finalize;
}

ExtendedEntities *ExtendedEntities::deserializeBSON(bsoncxx::document::view doc) {
	bsoncxx::document::element element = doc["media"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele : element.get_array().value) {
			MediaEntity *mediaEntity = new MediaEntity();
			mediaEntity->deserializeBSON(ele.get_document().view());
			this->media.push_back(mediaEntity);
		}
	}
	return this;
}
