#ifndef CPP_EXTENDEDTWEETIP_H
#define CPP_EXTENDEDTWEETIP_H


#include <vector>
#include <iostream>
#include "HashtagEntity.h"
#include "Object.h"
#include "EntitiesIP.h"
#include "ExtendedEntitiesIP.h"
#include "ExtendedTweet.h"

using namespace std;

class ExtendedTweetIP: public Object {

private:
    offset_ptr<char> fullText;
    vector<int> displayTextRange;
    offset_ptr<EntitiesIP> entities;
    bool hasEntities;
    offset_ptr<ExtendedEntitiesIP> extendedEntities;
    bool hasExtendedEntities;

public:
    ExtendedTweetIP();

    virtual ~ExtendedTweetIP();

    //In place object:
    ExtendedTweetIP(ExtendedTweet *extendedTweet);

    void serialize(ExtendedTweet *extendedTweet);

};


#endif //CPP_EXTENDEDTWEETIP_H
