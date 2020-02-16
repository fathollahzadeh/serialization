//
// Created by saeed on 11/29/19.
//

#ifndef TWITTER_ADDITIONALMEDIAINFOENTITYIP_H
#define TWITTER_ADDITIONALMEDIAINFOENTITYIP_H

#include "../../header/AdditionalMediaInfoEntity.h"
#include "Object.h"

class AdditionalMediaInfoEntityIP: public Object {

private:
    offset_ptr <char> title;
    offset_ptr <char> description;
    bool embeddable;
    bool monetizable;
public:
    AdditionalMediaInfoEntityIP();

    virtual ~AdditionalMediaInfoEntityIP();

    //Create an InPlace object:
    AdditionalMediaInfoEntityIP(AdditionalMediaInfoEntity *additionalMediaInfoEntity);

    void serialize(AdditionalMediaInfoEntity *additionalMediaInfoEntity);

};


#endif //TWITTER_ADDITIONALMEDIAINFOENTITYIP_H
