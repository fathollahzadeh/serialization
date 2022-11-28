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

#include "OptionEntity.h"

OptionEntity::OptionEntity() {}

OptionEntity::~OptionEntity() {

}

OptionEntity::OptionEntity(int position, const string &text) : position(position), text(text) {}

//Hand Coded C++ serialization:
char *OptionEntity::serializeHandcoded(char *buffer, int &objectSize) {
	//Serialize the object.
	//Copy Integers:
	buffer = copyInt(buffer, this->position, objectSize);
	//Copy Strings:
	buffer = copyString(buffer, this->text, objectSize);

	return buffer;
}


OptionEntity *OptionEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

	OptionEntity *optionEntity = new OptionEntity();
	//Parse Integer:
	optionEntity->position = parseInt(buffer + bytesRead);
	bytesRead += sizeof(optionEntity->position);

	//Parse Strings:
	parseString(buffer + bytesRead, optionEntity->text);
	bytesRead += (sizeof(int) + optionEntity->text.length());

	return optionEntity;
}

bsoncxx::document::value OptionEntity::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;

	document doc = document{};
	doc << "position" << this->position <<
		"text" << this->text;
	return doc << finalize;
}

OptionEntity *OptionEntity::deserializeBSON(bsoncxx::document::view doc) {
	bsoncxx::document::element element = doc["position"];
	this->position = element.get_int32();

	element = doc["text"];
	this->text = bsoncxx::string::to_string(element.get_utf8().value);

	return this;
}
