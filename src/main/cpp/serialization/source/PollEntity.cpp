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

#include "PollEntity.h"

PollEntity::PollEntity() {}

PollEntity::~PollEntity() {

	for (int i = 0; i < options.size(); ++i) {
		delete options.at(i);
	}
	options.shrink_to_fit();
}

PollEntity::PollEntity(const vector<OptionEntity *> &options, const string &endDatetime,
					   const string &durationMinutes) : options(options), endDatetime(endDatetime),
														durationMinutes(durationMinutes) {}

//Hand Coded C++ serialization:
char *PollEntity::serializeHandcoded(char *buffer, int &objectSize) {
	//Serialize the object.

	int numOfoptions = this->options.size();
	buffer = copyInt(buffer, numOfoptions, objectSize);
	for (int i = 0; i < numOfoptions; i++) {
		buffer = this->options.at(i)->serializeHandcoded(buffer, objectSize);
	}
	//Copy Strings:
	buffer = copyString(buffer, this->endDatetime, objectSize);
	buffer = copyString(buffer, this->durationMinutes, objectSize);

	return buffer;
}


PollEntity *PollEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

	int numOfoptions = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfoptions);
	for (int i = 0; i < numOfoptions; i++) {
		this->options.push_back(new OptionEntity());
		this->options.at(i)->deserializeHandcoded(buffer, bytesRead);

	}
	//Parse Strings:
	parseString(buffer + bytesRead, this->endDatetime);
	bytesRead += (sizeof(int) + this->endDatetime.length());
	parseString(buffer + bytesRead, this->durationMinutes);
	bytesRead += (sizeof(int) + this->durationMinutes.length());

	return this;
}

bsoncxx::document::value PollEntity::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::array;

	auto arroptions = array{};
	for (int i = 0; i < this->options.size(); ++i) {
		arroptions << bsoncxx::types::b_document{this->options[i]->serializeBSON().view()};
	}
	document doc = document{};
	doc << "end_datetime" << this->endDatetime <<
		"duration_minutes" << this->durationMinutes <<
		"options" << arroptions;

	return doc << finalize;
}

PollEntity *PollEntity::deserializeBSON(bsoncxx::document::view doc) {
	bsoncxx::document::element element = doc["end_datetime"];
	this->endDatetime = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["duration_minutes"];
	this->durationMinutes = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["options"];
	for (auto ele : element.get_array().value) {
		OptionEntity *optionEntity = new OptionEntity();
		optionEntity->deserializeBSON(ele.get_document().view());
		this->options.push_back(optionEntity);
	}
	return this;
}
