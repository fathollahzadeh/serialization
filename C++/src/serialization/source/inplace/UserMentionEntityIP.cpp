#include "UserMentionEntityIP.h"

UserMentionEntityIP::UserMentionEntityIP() {}

UserMentionEntityIP::~UserMentionEntityIP() {}

UserMentionEntityIP::UserMentionEntityIP(UserMentionEntity *userMentionEntity) {
	this->serialize(userMentionEntity);
}

void UserMentionEntityIP::serialize(UserMentionEntity *userMentionEntity) {
	this->id = userMentionEntity->id;

	this->idStr = malloc<char>(strlen(userMentionEntity->idStr.c_str()) + 1);
	strcpy(this->idStr, userMentionEntity->idStr.c_str());

	//TODO: implement inplace for vector:
	//vector<int> indices;

	this->name = malloc<char>(strlen(userMentionEntity->name.c_str()) + 1);
	strcpy(this->name, userMentionEntity->name.c_str());

	this->screenName = malloc<char>(strlen(userMentionEntity->screenName.c_str()) + 1);
	strcpy(this->screenName, userMentionEntity->screenName.c_str());
}
