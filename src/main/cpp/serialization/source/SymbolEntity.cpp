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

#include "SymbolEntity.h"

using namespace std;

//Default constructor:
SymbolEntity::SymbolEntity() {
}

//Constructor with arguments:
SymbolEntity::SymbolEntity(vector<int> indices, string text) {
	this->indices = indices;
	this->text = text;
}


//Hand Coded C++ serialization:
char *SymbolEntity::serializeHandcoded(char *buffer, int &objectSize) {
	//Serialize the object.
	//Copy Integers:
	buffer = copyInt(buffer, this->indices.size(), objectSize);
	for (int i = 0; i < this->indices.size(); ++i) {
		buffer = copyInt(buffer, this->indices[i], objectSize);
	}
	//Copy Strings:
	buffer = copyString(buffer, this->text, objectSize);

	return buffer;
}


SymbolEntity *SymbolEntity::deserializeHandcoded(char *buffer, int &bytesRead) {
	int numOfIndices = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfIndices);
	for (int i = 0; i < numOfIndices; ++i) {
		this->indices.push_back(parseInt(buffer + bytesRead));
		bytesRead += sizeof(int);
	}
	//Parse Strings:
	parseString(buffer + bytesRead, this->text);
	bytesRead += (sizeof(int) + this->text.length());
	return this;
}

SymbolEntity::~SymbolEntity() {
	//free memory:
	indices.shrink_to_fit();
}

bsoncxx::document::value SymbolEntity::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::array;

	auto arrindices = array{};
	for (int i = 0; i < this->indices.size(); ++i) {
		arrindices << this->indices[i];
	}

	document doc = document{};
	doc << "text" << this->text;
	doc << "indices" << arrindices;

	return doc << finalize;
}

SymbolEntity *SymbolEntity::deserializeBSON(bsoncxx::document::view doc) {
	bsoncxx::document::element element = doc["text"];
	this->text = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["indices"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele : element.get_array().value) {
			this->indices.push_back(ele.get_int32());
		}
	}
	return this;
}
