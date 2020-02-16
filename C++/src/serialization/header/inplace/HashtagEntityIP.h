//
// Created by saeed on 11/29/19.
//

#ifndef TWITTER_HASHTAGENTITYIP_H
#define TWITTER_HASHTAGENTITYIP_H

#include <vector>
#include <iostream>
#include "../../header/HashtagEntity.h"
#include "Object.h"

using  namespace std;
class HashtagEntityIP: public Object {

private:
    vector<int> indices;
    offset_ptr <char> text;

public:

    HashtagEntityIP();

    virtual ~HashtagEntityIP();

    //In place object:
    HashtagEntityIP(HashtagEntity *hashtagEntity);

    void serialize(HashtagEntity *hashtagEntity);
};


#endif //TWITTER_HASHTAGENTITYIP_H
