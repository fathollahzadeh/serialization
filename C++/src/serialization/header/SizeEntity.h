#ifndef SizeEntity_H
#define SizeEntity_H


#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"

using namespace std;


/*
 *	Contains only the declaration of SizeEntity Class.
 */

class SizeEntity : public RootData {

public:
    int width;
    int height;
    string resize;
private:
    //Boost Serialization:
    friend class boost::serialization::access;

    //Serialize method for boost:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {

        // Simply list all the fields to be serialized/deserialized.
        ar & width;
        ar & height;
        ar & resize;
    }

public:
    //Default destructor:
    virtual ~SizeEntity();

    //Copy constructor:
    SizeEntity(const SizeEntity &obj);

    //Default constructor:
    SizeEntity();

    //Constructor with arguments:
    SizeEntity(int width, int height, string resize);

    //C++: Use explicitly for printing.
    string toJSON();

    //Hand Coded C++ serialization:
    //New API: Writes directly to File Page:
    char *serializeHandcoded(char *buffer, int &objectSize);

    //Hand Coded C++ de-serialization:
    SizeEntity *deserializeHandcoded(char *buffer, int &bytesRead);

    //BSON buffer serialization
    bsoncxx::document::value serializeBSON();

};
BOOST_CLASS_TRACKING(SizeEntity, boost::serialization::track_never)

#endif
