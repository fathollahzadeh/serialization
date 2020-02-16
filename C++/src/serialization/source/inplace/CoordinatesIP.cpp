//
// Created by saeed on 11/29/19.
//

#include "CoordinatesIP.h"

CoordinatesIP::CoordinatesIP() {}

CoordinatesIP::~CoordinatesIP() {}

CoordinatesIP::CoordinatesIP(Coordinates *coordinates) {
    this->serialize(coordinates);
}

void CoordinatesIP::serialize(Coordinates *coordinates) {
    this->type = malloc <char> (strlen (coordinates->type.c_str ()) + 1);
    strcpy (this->type, coordinates->type.c_str ());

    //TODO: serialize double* coordinates:
    //double* coordinates
}

string CoordinatesIP::getType(){
    return string(type);
}
