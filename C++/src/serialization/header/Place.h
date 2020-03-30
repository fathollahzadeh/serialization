#ifndef Place_H
#define Place_H


#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"
#include "BoundingBoxCoordinate.h"

using namespace std;


/*
 *	Contains only the declaration of Place Class.
 */

class Place : public RootData {


public:
    string name;
    string countryCode;
    string id;
    string country;
    string placeType;
    string url;
    string fullName;
    BoundingBoxCoordinate *boundingBoxCoordinates;

private:
    //Boost Serialization:
    friend class boost::serialization::access;

    //Serialize method for boost:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {

        // Simply list all the fields to be serialized/deserialized.
        ar & name;
        ar & countryCode;
        ar & id;
        ar & country;
        ar & placeType;
        ar & url;
        ar & fullName;
        ar & BOOST_SERIALIZATION_NVP(boundingBoxCoordinates);

    }
public:
    //Default destructor:
    virtual ~Place();

    //Default constructor:
    Place();

    //Constructor with arguments:
    Place(string name, string countryCode, string id, string country, string placeType, string url, string fullName,
          BoundingBoxCoordinate *boundingBoxCoordinates);

    //C++: Use explicitly for printing.
    string toJSON();

    //Hand Coded C++ serialization:
    //New API: Writes directly to File Page:
    char *serializeHandcoded(char *buffer, int &objectSize);

    //Hand Coded C++ de-serialization:
    Place *deserializeHandcoded(char *buffer, int &bytesRead);

    //BSON buffer serialization
    bsoncxx::document::value serializeBSON();
};

BOOST_CLASS_TRACKING(Place, boost::serialization::track_never)

#endif
