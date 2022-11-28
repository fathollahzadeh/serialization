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

#include "SizeEntity.h"

using namespace std;


//Copy constructor:
SizeEntity::SizeEntity(const SizeEntity &obj) {
	throw invalid_argument("SizeEntity: Not copy constructible.");
}


//Default constructor:
SizeEntity::SizeEntity() {
}

//Constructor with arguments:
SizeEntity::SizeEntity(int width, int height, string resize) {
	this->width = width;
	this->height = height;
	this->resize = resize;
}

//Hand Coded C++ serialization:
char *SizeEntity::serializeHandcoded(char *buffer, int &objectSize) {
	//Serialize the object.
	//Copy Integers:
	buffer = copyInt(buffer, this->width, objectSize);
	buffer = copyInt(buffer, this->height, objectSize);

	//Copy string
	buffer = copyString(buffer, this->resize, objectSize);

	return buffer;
}


SizeEntity *SizeEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

	this->width = parseInt(buffer + bytesRead);
	bytesRead += sizeof(this->width);

	this->height = parseInt(buffer + bytesRead);
	bytesRead += sizeof(this->height);

	parseString(buffer + bytesRead, this->resize);
	bytesRead += (sizeof(int) + this->resize.length());

	return this;
}


SizeEntity::~SizeEntity() {}

bsoncxx::document::value SizeEntity::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::array;

	document doc = document{};
	doc << "width" << this->width <<
		"height" << this->height <<
		"resize" << this->resize;

	return doc << finalize;
}

SizeEntity *SizeEntity::deserializeBSON(bsoncxx::document::view doc) {

	bsoncxx::document::element element = doc["width"];
	this->width = element.get_int32();

	element = doc["height"];
	this->height = element.get_int32();

	element = doc["resize"];
	this->resize = bsoncxx::string::to_string(element.get_utf8().value);

	return this;
}
