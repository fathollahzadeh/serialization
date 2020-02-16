//
// Created by saeed on 11/29/19.
//

#ifndef TWITTER_VARIANTENTITYIP_H
#define TWITTER_VARIANTENTITYIP_H

#include <iostream>
#include "../../header/VariantEntity.h"
#include "Object.h"

using  namespace std;
class VariantEntityIP : public Object {

private:
    long bitrate;
    offset_ptr <char> contentType;
    offset_ptr <char> url;

public:

    VariantEntityIP();

    virtual ~VariantEntityIP();

    //In place serialization:
    VariantEntityIP(VariantEntity *variantEntity);

    void serialize(VariantEntity *variantEntity);
};


#endif //TWITTER_VARIANTENTITYIP_H
