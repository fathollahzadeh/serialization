//
// Created by saeed on 11/29/19.
//

#ifndef TWITTER_ENTITIESIP_H
#define TWITTER_ENTITIESIP_H


#include "../../header/HashtagEntity.h"
#include "../../header/MediaEntity.h"
#include "../../header/URLEntity.h"
#include "../../header/UserMentionEntity.h"
#include "../../header/SymbolEntity.h"
#include "../../header/PollEntity.h"
#include "../../header/Entities.h"
#include "Object.h"
#include "HashtagEntityIP.h"
#include "MediaEntityIP.h"
#include "URLEntityIP.h"
#include "UserMentionEntityIP.h"
#include "SymbolEntityIP.h"
#include "PollEntityIP.h"

class EntitiesIP: public Object {

private:
    offset_ptr<HashtagEntityIP> hashtags;
    int numOfHashtagEntity;
    offset_ptr<MediaEntityIP> media;
    int numOfMediaEntity;
    offset_ptr<URLEntityIP> urls;
    int numOfURLEntity;
    offset_ptr<UserMentionEntityIP> userMentions;
    int numOfUserMentionEntity;
    offset_ptr<SymbolEntityIP> symbols;
    int numOfSymbolEntity;
    offset_ptr<PollEntityIP> polls;
    int numOfPollEntity;

public:
    EntitiesIP();

    virtual ~EntitiesIP();

    //Create InPlace object:
    EntitiesIP(Entities *entities);

    void serialize(Entities *entities);
};


#endif //TWITTER_ENTITIESIP_H
