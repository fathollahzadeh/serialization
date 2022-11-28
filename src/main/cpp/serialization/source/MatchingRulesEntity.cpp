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

#include "MatchingRulesEntity.h"

MatchingRulesEntity::MatchingRulesEntity(const string &tag, long id, const string &idStr) : tag(tag), id(id),
																							idStr(idStr) {}

MatchingRulesEntity::MatchingRulesEntity() {}

char *MatchingRulesEntity::serializeHandcoded(char *buffer, int &objectSize) {
	//Copy Longs:
	buffer = copyLong(buffer, this->id, objectSize);
	//Copy Strings:
	buffer = copyString(buffer, this->tag, objectSize);
	buffer = copyString(buffer, this->idStr, objectSize);
	return buffer;
}

MatchingRulesEntity *MatchingRulesEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

	// Long elements
	this->id = parseLong(buffer + bytesRead);
	bytesRead += sizeof(this->id);

	//Parse Strings:
	parseString(buffer + bytesRead, this->tag);
	bytesRead += (sizeof(int) + this->tag.length());
	parseString(buffer + bytesRead, this->idStr);
	bytesRead += (sizeof(int) + this->idStr.length());

	return this;
}


MatchingRulesEntity::~MatchingRulesEntity() {

}

bsoncxx::document::value MatchingRulesEntity::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::array;

	document doc = document{};
	doc << "tag" << this->tag <<
		"id" << this->id <<
		"id_str" << this->idStr;

	return doc << finalize;
}

MatchingRulesEntity *MatchingRulesEntity::deserializeBSON(bsoncxx::document::view doc) {
	bsoncxx::document::element element = doc["tag"];
	this->tag = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["id"];
	this->id = element.type() == bsoncxx::type::k_int64 ? element.get_int64().value : element.get_int32().value;

	element = doc["id_str"];
	this->idStr = bsoncxx::string::to_string(element.get_utf8().value);

	return this;
}
