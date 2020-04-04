#ifndef VariantEntity_H
#define VariantEntity_H


#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"

using namespace std;


/*
 *	Contains only the declaration of VariantEntity Class.
 */

class VariantEntity : public RootData {

public:
    long bitrate;
    string contentType;
    string url;
private:
    //Boost Serialization:
    friend class boost::serialization::access;

    //Serialize method for boost:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {

        // Simply list all the fields to be serialized/deserialized.
        ar & bitrate;
        ar & contentType;
        ar & url;
    }

public:
    //Default destructor:
    virtual ~VariantEntity();

    //Copy constructor:
    VariantEntity(const VariantEntity &obj);

    //Default constructor:
    VariantEntity();

    //Constructor with arguments:
    VariantEntity(long bitrate, string contentType, string url);

    //C++: Use explicitly for printing.
    string toJSON();

    //Hand Coded C++ serialization:
    //New API: Writes directly to File Page:
    char *serializeHandcoded(char *buffer, int &objectSize);

    //Hand Coded C++ de-serialization:
    VariantEntity *deserializeHandcoded(char *buffer, int &bytesRead);

    //BSON buffer serialization
    bsoncxx::document::value serializeBSON();

    //BSON de-serialization:
    VariantEntity * deserializeBSON(bsoncxx::document::view doc);

};
BOOST_CLASS_TRACKING(VariantEntity, boost::serialization::track_never)

#endif
