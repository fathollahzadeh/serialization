//
// Created by saeed on 11/29/19.
//

#include "HashtagEntityIP.h"

HashtagEntityIP::HashtagEntityIP() {}

HashtagEntityIP::~HashtagEntityIP() {}

HashtagEntityIP::HashtagEntityIP(HashtagEntity *hashtagEntity) {
    this->serialize(hashtagEntity);
}

void HashtagEntityIP::serialize(HashtagEntity *hashtagEntity) {

    //TODO: implement inplace for indices:
    //vector<int> indices;

    this->text = malloc < char > (strlen(hashtagEntity->text.c_str()) + 1);
    strcpy(this->text, hashtagEntity->text.c_str());
}
