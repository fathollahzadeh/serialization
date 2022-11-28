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

#include "VideoEntity.h"

VideoEntity::VideoEntity() {}

VideoEntity::VideoEntity(const vector<int> &aspectRatio, int durationMillis,
						 const vector<VariantEntity *> &variants) : aspectRatio(aspectRatio),
																	durationMillis(durationMillis),
																	variants(variants) {}

char *VideoEntity::serializeHandcoded(char *buffer, int &objectSize) {

	//Serialize the object.
	//Copy vector:
	int numOfAspectRatio = this->aspectRatio.size();
	buffer = copyInt(buffer, numOfAspectRatio, objectSize);

	for (int i = 0; i < numOfAspectRatio; i++) {
		buffer = copyInt(buffer, this->aspectRatio.at(i), objectSize);
	}

	int numOfVariants = this->variants.size();
	buffer = copyInt(buffer, numOfVariants, objectSize);
	for (int i = 0; i < numOfVariants; i++) {
		buffer = this->variants.at(i)->serializeHandcoded(buffer, objectSize);
	}
	//Copy Integer:
	buffer = copyInt(buffer, this->durationMillis, objectSize);

	return buffer;

}

VideoEntity *VideoEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

	int numOfAspectRatio = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfAspectRatio);
	for (int i = 0; i < numOfAspectRatio; ++i) {
		this->aspectRatio.push_back(parseInt(buffer + bytesRead));
		bytesRead += sizeof(int);
	}

	int numOfVariants = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfVariants);
	for (int i = 0; i < numOfVariants; i++) {
		this->variants.push_back(new VariantEntity());
		this->variants.at(i)->deserializeHandcoded(buffer, bytesRead);
	}

	//Parse Integer:
	this->durationMillis = parseInt(buffer + bytesRead);
	bytesRead += sizeof(this->durationMillis);
	return this;

}

VideoEntity::~VideoEntity() {
	//free memory:
	aspectRatio.shrink_to_fit();
	for (int i = 0; i < variants.size(); ++i) {
		delete variants.at(i);
	}
	variants.shrink_to_fit();
}

bsoncxx::document::value VideoEntity::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::array;

	auto arraspect_ratio = array{};
	for (int i = 0; i < this->aspectRatio.size(); ++i) {
		arraspect_ratio << this->aspectRatio[i];
	}

	auto arrvariants = array{};
	for (int i = 0; i < this->variants.size(); ++i) {
		arrvariants << bsoncxx::types::b_document{this->variants[i]->serializeBSON().view()};
	}

	document doc = document{};
	doc << "duration_millis" << this->durationMillis <<
		"aspect_ratio" << arraspect_ratio <<
		"variants" << arrvariants;

	return doc << finalize;
}

VideoEntity *VideoEntity::deserializeBSON(bsoncxx::document::view doc) {
	bsoncxx::document::element element = doc["duration_millis"];
	this->durationMillis = element.get_int32();

	element = doc["aspect_ratio"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele : element.get_array().value) {
			this->aspectRatio.push_back(ele.get_int32());
		}
	}

	element = doc["variants"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele : element.get_array().value) {
			VariantEntity *variantEntity = new VariantEntity();
			variantEntity->deserializeBSON(ele.get_document().view());
			this->variants.push_back(variantEntity);
		}
	}

	return this;
}



