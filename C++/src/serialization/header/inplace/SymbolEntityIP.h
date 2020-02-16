//
// Created by saeed on 11/29/19.
//

#ifndef TWITTER_SYMBOLENTITYIP_H
#define TWITTER_SYMBOLENTITYIP_H

#include <iostream>
#include <vector>
#include "../../header/SymbolEntity.h"
#include "Object.h"

using namespace std;
class SymbolEntityIP: public Object {

private:
    vector<int> indices;
    offset_ptr <char> text;

public:

    SymbolEntityIP();

    virtual ~SymbolEntityIP();

    //In place object:
    SymbolEntityIP(SymbolEntity *symbolEntity);

    void serialize(SymbolEntity *symbolEntity);
};


#endif //TWITTER_SYMBOLENTITYIP_H
