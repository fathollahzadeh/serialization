#include "ExtendedTweetIP.h"

ExtendedTweetIP::ExtendedTweetIP() {}

ExtendedTweetIP::~ExtendedTweetIP() {}

ExtendedTweetIP::ExtendedTweetIP(ExtendedTweet *extendedTweet) {
    this->serialize(extendedTweet);
}

void ExtendedTweetIP::serialize(ExtendedTweet *extendedTweet) {
    //TODO: implement inplace for integers:

    this->fullText = malloc<char>(strlen(extendedTweet->fullText.c_str()) + 1);
    strcpy(this->fullText, extendedTweet->fullText.c_str());

    if (extendedTweet->entities != nullptr) {
        this->hasEntities = true;
        this->entities = new EntitiesIP[1];
        this->entities[0].serialize(extendedTweet->entities);
    } else
        this->hasEntities = false;

    if (extendedTweet->extendedEntities != nullptr) {
        this->hasExtendedEntities = true;
        this->extendedEntities = new ExtendedEntitiesIP[1];
        this->extendedEntities[0].serialize(extendedTweet->extendedEntities);
    } else
        this->hasExtendedEntities = false;
}
