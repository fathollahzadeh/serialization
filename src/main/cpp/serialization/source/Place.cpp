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

#include "Place.h"

using namespace std;

//Default constructor:
Place::Place() {
}

//Constructor with arguments:
Place::Place(string name, string countryCode, string id, string country, string placeType, string url,
			 string fullName,
			 BoundingBoxCoordinate *boundingBoxCoordinates) {
	this->name = name;
	this->countryCode = countryCode;
	this->id = id;
	this->country = country;
	this->placeType = placeType;
	this->url = url;
	this->fullName = fullName;
	this->boundingBoxCoordinates = boundingBoxCoordinates;
}

//Hand Coded C++ serialization:
char *Place::serializeHandcoded(char *buffer, int &objectSize) {

	//Serialize the object.
	//Copy Strings:
	buffer = copyString(buffer, this->name, objectSize);
	buffer = copyString(buffer, this->countryCode, objectSize);
	buffer = copyString(buffer, this->id, objectSize);
	buffer = copyString(buffer, this->country, objectSize);
	buffer = copyString(buffer, this->placeType, objectSize);
	buffer = copyString(buffer, this->url, objectSize);
	buffer = copyString(buffer, this->fullName, objectSize);

	if (this->boundingBoxCoordinates != nullptr) {
		buffer = copyBool(buffer, false, objectSize);
		buffer = this->boundingBoxCoordinates->serializeHandcoded(buffer, objectSize);
	} else
		buffer = copyBool(buffer, true, objectSize);

	return buffer;
}


Place *Place::deserializeHandcoded(char *buffer, int &bytesRead) {

	//Parse Strings:
	parseString(buffer + bytesRead, this->name);
	bytesRead += (sizeof(int) + this->name.length());
	parseString(buffer + bytesRead, this->countryCode);
	bytesRead += (sizeof(int) + this->countryCode.length());
	parseString(buffer + bytesRead, this->id);
	bytesRead += (sizeof(int) + this->id.length());
	parseString(buffer + bytesRead, this->country);
	bytesRead += (sizeof(int) + this->country.length());
	parseString(buffer + bytesRead, this->placeType);
	bytesRead += (sizeof(int) + this->placeType.length());
	parseString(buffer + bytesRead, this->url);
	bytesRead += (sizeof(int) + this->url.length());
	parseString(buffer + bytesRead, this->fullName);
	bytesRead += (sizeof(int) + this->fullName.length());

	bool checknullptr;
	//BoundingBoxCoordinate:
	checknullptr = parseBool(buffer + bytesRead);
	bytesRead += sizeof(checknullptr);
	if (!checknullptr) {
		this->boundingBoxCoordinates = new BoundingBoxCoordinate();
		this->boundingBoxCoordinates->deserializeHandcoded(buffer, bytesRead);

	} else
		this->boundingBoxCoordinates = nullptr;
	return this;
}

bsoncxx::document::value Place::serializeBSON() {

	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;

	document doc = document{};
	doc << "name" << this->name <<
		"country_code" << this->countryCode <<
		"id" << this->id <<
		"country" << this->country <<
		"place_type" << this->placeType <<
		"url" << this->url <<
		"full_name" << this->fullName;

	if (this->boundingBoxCoordinates != nullptr) {
		doc << "bounding_box" << bsoncxx::types::b_document{this->boundingBoxCoordinates->serializeBSON().view()};
	}
	return doc << finalize;
}

Place *Place::deserializeBSON(bsoncxx::document::view doc) {
	bsoncxx::document::element element = doc["name"];
	this->name = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["country_code"];
	this->countryCode = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["id"];
	this->id = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["country"];
	this->country = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["place_type"];
	this->placeType = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["url"];
	this->url = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["full_name"];
	this->fullName = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["bounding_box"];
	if (element) {
		this->boundingBoxCoordinates = new BoundingBoxCoordinate();
		this->boundingBoxCoordinates->deserializeBSON(element.get_document().view());
	} else
		this->boundingBoxCoordinates = nullptr;
	return this;
}

Place::~Place() {
	if (boundingBoxCoordinates != nullptr) {
		delete boundingBoxCoordinates;
	}
}
