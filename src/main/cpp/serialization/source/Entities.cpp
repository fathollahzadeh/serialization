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

#include "Entities.h"

using namespace std;

//Default constructor:
Entities::Entities() {
}

//Constructor with arguments:
Entities::Entities(vector<HashtagEntity *> hashtags, vector<MediaEntity *> media, vector<URLEntity *> urls,
				   vector<UserMentionEntity *> userMentions, vector<SymbolEntity *> symbols,
				   vector<PollEntity *> polls) {
	this->hashtags = hashtags;
	this->media = media;
	this->urls = urls;
	this->userMentions = userMentions;
	this->symbols = symbols;
	this->polls = polls;
}

//Hand Coded C++ serialization:
char *Entities::serializeHandcoded(char *buffer, int &objectSize) {

	//Serialize the object.
	//Copy encapsulated objects:
	int numOfHashtags = this->hashtags.size();
	buffer = copyInt(buffer, numOfHashtags, objectSize);

	for (int i = 0; i < this->hashtags.size(); i++) {
		buffer = this->hashtags.at(i)->serializeHandcoded(buffer, objectSize);
	}

	int numOfMedia = this->media.size();
	buffer = copyInt(buffer, numOfMedia, objectSize);

	for (int i = 0; i < this->media.size(); i++) {
		buffer = this->media.at(i)->serializeHandcoded(buffer, objectSize);
	}

	int numOfUrls = this->urls.size();
	buffer = copyInt(buffer, numOfUrls, objectSize);

	for (int i = 0; i < this->urls.size(); i++) {
		buffer = this->urls.at(i)->serializeHandcoded(buffer, objectSize);
	}

	int numOfUserMentions = this->userMentions.size();
	buffer = copyInt(buffer, numOfUserMentions, objectSize);

	for (int i = 0; i < this->userMentions.size(); i++) {
		buffer = this->userMentions.at(i)->serializeHandcoded(buffer, objectSize);
	}

	int numOfSymbols = this->symbols.size();
	buffer = copyInt(buffer, numOfSymbols, objectSize);

	for (int i = 0; i < this->symbols.size(); i++) {
		buffer = this->symbols.at(i)->serializeHandcoded(buffer, objectSize);
	}

	int numOfPollss = this->polls.size();
	buffer = copyInt(buffer, numOfPollss, objectSize);

	for (int i = 0; i < this->polls.size(); i++) {
		buffer = this->polls.at(i)->serializeHandcoded(buffer, objectSize);
	}

	return buffer;
}


Entities *Entities::deserializeHandcoded(char *buffer, int &bytesRead) {

	//Encapsulated objects:
	int numOfHashtags = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfHashtags);
	for (int i = 0; i < numOfHashtags; i++) {
		this->hashtags.push_back(new HashtagEntity());
		this->hashtags.at(i)->deserializeHandcoded(buffer, bytesRead);
	}

	int numOfMedia = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfMedia);
	for (int i = 0; i < numOfMedia; i++) {
		this->media.push_back(new MediaEntity());
		this->media.at(i)->deserializeHandcoded(buffer, bytesRead);
	}

	int numOfUrls = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfUrls);
	for (int i = 0; i < numOfUrls; i++) {
		this->urls.push_back(new URLEntity());
		this->urls.at(i)->deserializeHandcoded(buffer, bytesRead);
	}

	int numOfUserMentions = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfUserMentions);
	for (int i = 0; i < numOfUserMentions; i++) {
		this->userMentions.push_back(new UserMentionEntity());
		this->userMentions.at(i)->deserializeHandcoded(buffer, bytesRead);
	}

	int numOfSymbols = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfSymbols);
	for (int i = 0; i < numOfSymbols; i++) {
		this->symbols.push_back(new SymbolEntity());
		this->symbols.at(i)->deserializeHandcoded(buffer, bytesRead);
	}

	int numOfPollss = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfPollss);
	for (int i = 0; i < numOfPollss; i++) {
		this->polls.push_back(new PollEntity());
		this->polls.at(i)->deserializeHandcoded(buffer, bytesRead);
	}
	return this;
}

Entities::~Entities() {

	//free memory:
	for (int i = 0; i < hashtags.size(); ++i) {
		delete hashtags.at(i);
	}
	hashtags.shrink_to_fit();

	for (int i = 0; i < media.size(); ++i) {
		delete media.at(i);
	}
	media.shrink_to_fit();

	for (int i = 0; i < urls.size(); ++i) {
		delete urls.at(i);
	}
	urls.shrink_to_fit();

	for (int i = 0; i < userMentions.size(); ++i) {
		delete userMentions.at(i);
	}
	userMentions.shrink_to_fit();

	for (int i = 0; i < symbols.size(); ++i) {
		delete symbols.at(i);
	}
	symbols.shrink_to_fit();

	for (int i = 0; i < polls.size(); ++i) {
		delete polls.at(i);
	}
	polls.shrink_to_fit();

}

bsoncxx::document::value Entities::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::array;

	auto arrhashtags = array{};
	for (int i = 0; i < this->hashtags.size(); ++i) {
		arrhashtags << bsoncxx::types::b_document{this->hashtags[i]->serializeBSON().view()};
	}

	auto arrmedia = array{};
	for (int i = 0; i < this->media.size(); ++i) {
		arrmedia << bsoncxx::types::b_document{this->media[i]->serializeBSON().view()};
	}

	auto arrurls = array{};
	for (int i = 0; i < this->urls.size(); ++i) {
		arrurls << bsoncxx::types::b_document{this->urls[i]->serializeBSON().view()};
	}

	auto arruserMentions = array{};
	for (int i = 0; i < this->userMentions.size(); ++i) {
		arruserMentions << bsoncxx::types::b_document{this->userMentions[i]->serializeBSON().view()};
	}

	auto arrsymbols = array{};
	for (int i = 0; i < this->symbols.size(); ++i) {
		arrsymbols << bsoncxx::types::b_document{this->symbols[i]->serializeBSON().view()};
	}

	auto arrpolls = array{};
	for (int i = 0; i < this->polls.size(); ++i) {
		arrpolls << bsoncxx::types::b_document{this->polls[i]->serializeBSON().view()};
	}
	document doc = document{};
	doc << "hashtags" << arrhashtags << "media" << arrmedia << "urls" << arrurls << "user_mentions" << arruserMentions
		<< "symbols" << arrsymbols << "polls" << arrpolls;

	return doc << finalize;
}

Entities *Entities::deserializeBSON(bsoncxx::document::view doc) {

	bsoncxx::document::element element = doc["hashtags"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele : element.get_array().value) {
			HashtagEntity *hashtagEntity = new HashtagEntity();
			hashtagEntity->deserializeBSON(ele.get_document().view());
			this->hashtags.push_back(hashtagEntity);
		}
	}

	element = doc["media"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele : element.get_array().value) {
			MediaEntity *mediaEntity = new MediaEntity();
			mediaEntity->deserializeBSON(ele.get_document().view());
			this->media.push_back(mediaEntity);
		}
	}

	element = doc["urls"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele : element.get_array().value) {
			URLEntity *urlEntity = new URLEntity();
			urlEntity->deserializeBSON(ele.get_document().view());
			this->urls.push_back(urlEntity);
		}
	}

	element = doc["user_mentions"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele : element.get_array().value) {
			UserMentionEntity *userMentionEntity = new UserMentionEntity();
			userMentionEntity->deserializeBSON(ele.get_document().view());
			this->userMentions.push_back(userMentionEntity);
		}
	}

	element = doc["symbols"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele : element.get_array().value) {
			SymbolEntity *symbolEntity = new SymbolEntity();
			symbolEntity->deserializeBSON(ele.get_document().view());
			this->symbols.push_back(symbolEntity);
		}
	}
	element = doc["polls"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele : element.get_array().value) {
			PollEntity *pollEntity = new PollEntity();
			pollEntity->deserializeBSON(ele.get_document().view());
			this->polls.push_back(pollEntity);
		}
	}
	return this;
}



