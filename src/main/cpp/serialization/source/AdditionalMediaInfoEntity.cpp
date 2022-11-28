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

#include "AdditionalMediaInfoEntity.h"

AdditionalMediaInfoEntity::AdditionalMediaInfoEntity() {}

AdditionalMediaInfoEntity::~AdditionalMediaInfoEntity() {}

AdditionalMediaInfoEntity::AdditionalMediaInfoEntity(const string &title, const string &description,
													 bool embeddable, bool monetizable) : title(title),
																						  description(description),
																						  embeddable(embeddable),
																						  monetizable(
																								  monetizable) {}
//Hand Coded C++ serialization:
char *AdditionalMediaInfoEntity::serializeHandcoded(char *buffer, int &objectSize) {
	//Copy Strings:
	buffer = copyString(buffer, this->title, objectSize);
	buffer = copyString(buffer, this->description, objectSize);
	//Copy Booleans:
	buffer = copyBool(buffer, this->embeddable, objectSize);
	buffer = copyBool(buffer, this->monetizable, objectSize);
	return buffer;
}

//Hand Coded C++ de-serialization:
AdditionalMediaInfoEntity *AdditionalMediaInfoEntity::deserializeHandcoded(char *buffer, int &bytesRead) {
	//Parse Strings:
	parseString(buffer + bytesRead, this->title);
	bytesRead += (sizeof(int) + this->title.length());

	parseString(buffer + bytesRead, this->description);
	bytesRead += (sizeof(int) + this->description.length());

	// Boolean elements
	this->embeddable = parseBool(buffer + bytesRead);
	bytesRead += sizeof(this->embeddable);
	this->monetizable = parseBool(buffer + bytesRead);
	bytesRead += sizeof(this->monetizable);
	return this;
}

bsoncxx::document::value AdditionalMediaInfoEntity::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;

	document doc = document{};
	doc << "title" << this->title <<
		"description" << this->description <<
		"embeddable" << this->embeddable <<
		"monetizable" << this->monetizable;

	return doc << finalize;
}

AdditionalMediaInfoEntity *AdditionalMediaInfoEntity::deserializeBSON(bsoncxx::document::view doc) {


	bsoncxx::document::element element = doc["title"];
	this->title = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["description"];
	this->description = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["embeddable"];
	this->embeddable = element.get_bool();

	element = doc["monetizable"];
	this->monetizable = element.get_bool();

	return this;
}


