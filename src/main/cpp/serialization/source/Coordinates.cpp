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

#include "Coordinates.h"

using namespace std;


//Default constructor:
Coordinates::Coordinates() {
}

//Constructor with arguments:
Coordinates::Coordinates(string type, double *coordinates) {
	this->type = type;
	this->coordinates[0] = *coordinates;
	this->coordinates[1] = *(coordinates + 1);
}

//Hand Coded C++ serialization:
char *Coordinates::serializeHandcoded(char *buffer, int &objectSize) {
	//Serialize the object.
	//Copy Strings:
	buffer = copyString(buffer, this->type, objectSize);

	//Copy Double:
	buffer = copyDouble(buffer, *this->coordinates, objectSize); // 8 bytes for latitudes
	buffer = copyDouble(buffer, *(this->coordinates + 1), objectSize); // 8 bytes for longitudes
	return buffer;
}


Coordinates *Coordinates::deserializeHandcoded(char *buffer, int &bytesRead) {

	//Parse Strings:
	parseString(buffer + bytesRead, this->type);
	bytesRead += (sizeof(int) + this->type.length());

	//Read 8 bytes for latitudes:
	this->coordinates[0] = parseDouble(buffer + bytesRead);
	bytesRead += sizeof(double);

	//Read 8 bytes for longitudes
	this->coordinates[1] = parseDouble(buffer + bytesRead);
	bytesRead += sizeof(double);

	return this;
}

Coordinates::~Coordinates() {
	// delete coordinates;
}

bsoncxx::document::value Coordinates::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::open_array;
	using bsoncxx::builder::stream::close_array;

	document doc = document{};
	doc << "type" << this->type <<
		"coordinates" << open_array << this->coordinates[0] << this->coordinates[1] << close_array;

	return doc << finalize;
}

Coordinates *Coordinates::deserializeBSON(bsoncxx::document::view doc) {
	bsoncxx::document::element element = doc["type"];
	this->type = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["coordinates"];
	auto val0 = element[0].get_double();
	auto val1 = element[1].get_double();
	if (val0 && val1) {
		this->coordinates[0] = val0.value;
		this->coordinates[1] = val1.value;
	}
	return this;
}



