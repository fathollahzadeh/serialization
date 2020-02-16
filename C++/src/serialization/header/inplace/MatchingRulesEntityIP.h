//
// Created by saeed on 11/29/19.
//

#ifndef TWITTER_MATCHINGRULESENTITYIP_H
#define TWITTER_MATCHINGRULESENTITYIP_H

#include <iostream>
#include "../../header/MatchingRulesEntity.h"
#include "Object.h"

using namespace std;
class MatchingRulesEntityIP: public Object {
private:
    offset_ptr <char> tag;
    long id;
    offset_ptr <char> idStr;

public:
    MatchingRulesEntityIP();

    virtual ~MatchingRulesEntityIP();

    //In place object:
    MatchingRulesEntityIP(MatchingRulesEntity *matchingRulesEntity);

    void serialize(MatchingRulesEntity *matchingRulesEntity);
};


#endif //TWITTER_MATCHINGRULESENTITYIP_H
