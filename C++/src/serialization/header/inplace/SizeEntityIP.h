//
// Created by saeed on 11/29/19.
//

#ifndef TWITTER_SIZEENTITYIP_H
#define TWITTER_SIZEENTITYIP_H

#include <iostream>
#include "../../header/SizeEntity.h"
#include "Object.h"

using namespace std;
class SizeEntityIP: public Object {

private:
    int width;
    int height;
    offset_ptr <char> resize;

public:

    SizeEntityIP();

    virtual ~SizeEntityIP();

    //In place object:
    SizeEntityIP(SizeEntity *sizeEntity);

    void serialize(SizeEntity *sizeEntity);
};


#endif //TWITTER_SIZEENTITYIP_H
