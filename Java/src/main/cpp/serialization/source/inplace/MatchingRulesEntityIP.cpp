#include "MatchingRulesEntityIP.h"

MatchingRulesEntityIP::MatchingRulesEntityIP() {}

MatchingRulesEntityIP::~MatchingRulesEntityIP() {}

MatchingRulesEntityIP::MatchingRulesEntityIP(MatchingRulesEntity *matchingRulesEntity) {

	this->serialize(matchingRulesEntity);
}

void MatchingRulesEntityIP::serialize(MatchingRulesEntity *matchingRulesEntity) {
	this->tag = malloc<char>(strlen(matchingRulesEntity->tag.c_str()) + 1);
	strcpy(this->tag, matchingRulesEntity->tag.c_str());

	this->id = matchingRulesEntity->id;

	this->idStr = malloc<char>(strlen(matchingRulesEntity->idStr.c_str()) + 1);
	strcpy(this->idStr, matchingRulesEntity->idStr.c_str());
}
