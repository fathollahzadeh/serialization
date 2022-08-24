#include "EntitiesIP.h"

EntitiesIP::EntitiesIP() {}

EntitiesIP::~EntitiesIP() {}

EntitiesIP::EntitiesIP(Entities *entities) {

	this->serialize(entities);
}

void EntitiesIP::serialize(Entities *entities) {
	this->numOfHashtagEntity = entities->hashtags.size();
	this->hashtags = new HashtagEntityIP[this->numOfHashtagEntity];
	for (int i = 0; i < this->numOfHashtagEntity; ++i) {
		this->hashtags[i].serialize(entities->hashtags.at(i));
	}

	this->numOfMediaEntity = entities->media.size();
	this->media = new MediaEntityIP[this->numOfMediaEntity];
	for (int i = 0; i < this->numOfMediaEntity; ++i) {
		this->media[i].serialize(entities->media.at(i));
	}

	this->numOfURLEntity = entities->urls.size();
	this->urls = new URLEntityIP[this->numOfURLEntity];
	for (int i = 0; i < this->numOfURLEntity; ++i) {
		this->urls[i].serialize(entities->urls.at(i));
	}

	this->numOfUserMentionEntity = entities->userMentions.size();
	this->userMentions = new UserMentionEntityIP[this->numOfUserMentionEntity];
	for (int i = 0; i < this->numOfUserMentionEntity; ++i) {
		this->userMentions[i].serialize(entities->userMentions.at(i));
	}

	this->numOfSymbolEntity = entities->symbols.size();
	this->symbols = new SymbolEntityIP[this->numOfSymbolEntity];
	for (int i = 0; i < this->numOfSymbolEntity; ++i) {
		this->symbols[i].serialize(entities->symbols.at(i));
	}

	this->numOfPollEntity = entities->polls.size();
	this->polls = new PollEntityIP[this->numOfPollEntity];
	for (int i = 0; i < this->numOfPollEntity; ++i) {
		this->polls[i].serialize(entities->polls.at(i));
	}
}
