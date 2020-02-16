//
// Created by saeed on 11/29/19.
//

#ifndef TWITTER_PLACEIP_H
#define TWITTER_PLACEIP_H

#include <iostream>
#include "../../header/BoundingBoxCoordinate.h"
#include "../../header/Place.h"
#include "Object.h"
#include "BoundingBoxCoordinateIP.h"

using namespace std;

class PlaceIP: public Object {

private:
    offset_ptr <char> name;
    offset_ptr <char> countryCode;
    offset_ptr <char> id;
    offset_ptr <char> country;
    offset_ptr <char> placeType;
    offset_ptr <char> url;
    offset_ptr <char> fullName;
    offset_ptr<BoundingBoxCoordinateIP> boundingBoxCoordinates;
    bool hasBoundingBoxCoordinates;

public:

    PlaceIP();

    virtual ~PlaceIP();

    //In place serialization:
    PlaceIP(Place *place);

    void serialize(Place *place);
};


#endif //TWITTER_PLACEIP_H
