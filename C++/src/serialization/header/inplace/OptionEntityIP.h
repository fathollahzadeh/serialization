//
// Created by saeed on 11/29/19.
//

#ifndef TWITTER_OPTIONENTITYIP_H
#define TWITTER_OPTIONENTITYIP_H

#include <iostream>
#include "../../header/OptionEntity.h"
#include "Object.h"

using namespace std;
class OptionEntityIP: public Object {

private:
    int position;
    offset_ptr <char> text;

public:

    OptionEntityIP();

    virtual ~OptionEntityIP();

    //In place object:
    OptionEntityIP(OptionEntity *optionEntity);

    void serialize(OptionEntity *optionEntity);
};


#endif //TWITTER_OPTIONENTITYIP_H
