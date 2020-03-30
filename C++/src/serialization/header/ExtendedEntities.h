#ifndef ExtendedEntities_H
#define ExtendedEntities_H


#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"
#include "MediaEntity.h"

using namespace std;


/*
 *	Contains only the declaration of ExtendedEntities Class.
 */

class ExtendedEntities : public RootData {

public:
    vector<MediaEntity *> media;
private:
    //Boost Serialization:
    friend class boost::serialization::access;

    //Serialize method for boost:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // Simply list all the fields to be serialized/deserialized.
        ar & media;

    }
public:
    //Default destructor:
    virtual ~ExtendedEntities();

    //Default constructor:
    ExtendedEntities();

    //Constructor with arguments:
    ExtendedEntities(vector<MediaEntity *> media);

    //C++: Use explicitly for printing.
    string toJSON();

    //Hand Coded C++ serialization:
    //New API: Writes directly to File Page:
    char *serializeHandcoded(char *buffer, int &objectSize);

    //Hand Coded C++ de-serialization:
    ExtendedEntities *deserializeHandcoded(char *buffer, int &bytesRead);

    //BSON buffer serialization
    bsoncxx::document::value serializeBSON();

};

BOOST_CLASS_TRACKING(ExtendedEntities, boost::serialization::track_never)
#endif
