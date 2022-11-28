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

#include "UserMentionEntity.h"

using namespace std;

//Default constructor:
UserMentionEntity::UserMentionEntity() {
}

//Constructor with arguments:
UserMentionEntity::UserMentionEntity(long id, string idStr, vector<int> indices, string name, string screenName) {
	this->id = id;
	this->idStr = idStr;
	this->indices = indices;
	this->name = name;
	this->screenName = screenName;
}

//Hand Coded C++ serialization:
char *UserMentionEntity::serializeHandcoded(char *buffer, int &objectSize) {
	//Serialize the object.
	//Copy Long Elements:
	buffer = copyLong(buffer, this->id, objectSize);
	//Copy Integers:
	buffer = copyInt(buffer, this->indices.size(), objectSize);
	for (int i = 0; i < this->indices.size(); ++i) {
		buffer = copyInt(buffer, this->indices[i], objectSize);
	}

	//Copy Strings:
	buffer = copyString(buffer, this->idStr, objectSize);

	buffer = copyString(buffer, this->name, objectSize);
	buffer = copyString(buffer, this->screenName, objectSize);

	return buffer;
}


UserMentionEntity *UserMentionEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

	this->id = parseLong(buffer + bytesRead);
	bytesRead += sizeof(this->id);

	int numOfIndices = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfIndices);
	for (int i = 0; i < numOfIndices; ++i) {
		this->indices.push_back(parseInt(buffer + bytesRead));
		bytesRead += sizeof(int);
	}

	//Parse Strings:
	parseString(buffer + bytesRead, this->idStr);
	bytesRead += (sizeof(int) + this->idStr.length());

	parseString(buffer + bytesRead, this->name);
	bytesRead += (sizeof(int) + this->name.length());

	parseString(buffer + bytesRead, this->screenName);
	bytesRead += (sizeof(int) + this->screenName.length());

	return this;
}

UserMentionEntity::~UserMentionEntity() {
	//free memory:
	indices.shrink_to_fit();
}

bsoncxx::document::value UserMentionEntity::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::array;

	auto arrindices = array{};
	for (int i = 0; i < this->indices.size(); ++i) {
		arrindices << this->indices[i];
	}
	document doc = document{};
	doc << "id" << this->id <<
		"id_str" << this->idStr <<
		"name" << this->name <<
		"screen_name" << this->screenName <<
		"indices" << arrindices;

	return doc << finalize;
}

UserMentionEntity *UserMentionEntity::deserializeBSON(bsoncxx::document::view doc) {
	bsoncxx::document::element element = doc["id"];
	this->id = element.type() == bsoncxx::type::k_int64 ? element.get_int64() : element.get_int32();

	element = doc["id_str"];
	this->idStr = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["name"];
	this->name = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["screen_name"];
	this->screenName = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["indices"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele : element.get_array().value) {
			this->indices.push_back(ele.get_int32());
		}
	}
	return this;
}
