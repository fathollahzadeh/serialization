#include "AdditionalMediaInfoEntityIP.h"

AdditionalMediaInfoEntityIP::AdditionalMediaInfoEntityIP() {}

AdditionalMediaInfoEntityIP::~AdditionalMediaInfoEntityIP() {}

AdditionalMediaInfoEntityIP::AdditionalMediaInfoEntityIP(AdditionalMediaInfoEntity *additionalMediaInfoEntity) {

	this->serialize(additionalMediaInfoEntity);
}

void AdditionalMediaInfoEntityIP::serialize(AdditionalMediaInfoEntity *additionalMediaInfoEntity) {

	this->title = malloc<char>(strlen(additionalMediaInfoEntity->title.c_str()) + 1);
	strcpy(this->title, additionalMediaInfoEntity->title.c_str());

	this->description = malloc<char>(strlen(additionalMediaInfoEntity->description.c_str()) + 1);
	strcpy(this->description, additionalMediaInfoEntity->description.c_str());

	this->embeddable = additionalMediaInfoEntity->embeddable;

	this->monetizable = additionalMediaInfoEntity->monetizable;
}
