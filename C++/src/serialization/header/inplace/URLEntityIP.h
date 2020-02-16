//
// Created by saeed on 11/29/19.
//

#ifndef TWITTER_URLENTITYIP_H
#define TWITTER_URLENTITYIP_H

#include <iostream>
#include <vector>
#include "../../header/URLEntity.h"
#include "Object.h"

using namespace std;
class URLEntityIP: public Object {

private:
    vector<int> indices;
    offset_ptr <char> displayURL;
    offset_ptr <char> expandedURL;
    offset_ptr <char> url;

public:

    URLEntityIP();

    virtual ~URLEntityIP();

    //In place object:
    URLEntityIP(URLEntity *urlEntity);

    void serialize(URLEntity *urlEntity);
};


#endif //TWITTER_URLENTITYIP_H
