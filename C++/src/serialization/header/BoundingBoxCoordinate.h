#ifndef BoundingBoxCoordinate_H
#define BoundingBoxCoordinate_H


#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"

using namespace std;


/*
 *	Contains only the declaration of BoundingBoxCoordinate Class.
 */

class BoundingBoxCoordinate : public RootData {

public:
    string type;
    vector<vector<vector<double>>> coordinates;
private:
    //Boost Serialization:
    friend class boost::serialization::access;

    //Serialize method for boost:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // Simply list all the fields to be serialized/deserialized.
        ar & type;
        ar & coordinates;
    }
public:
    //Default destructor:
    virtual ~BoundingBoxCoordinate();

    //Default constructor:
    BoundingBoxCoordinate();

    //Constructor with arguments:
    BoundingBoxCoordinate(const string &type, const vector<vector<vector<double >>> &coordinates);

    //C++: Use explicitly for printing.
    string toJSON();

    //Hand Coded C++ serialization:
    //New API: Writes directly to File Page:
    char *serializeHandcoded(char *buffer, int &objectSize);

    //Hand Coded C++ de-serialization:
    BoundingBoxCoordinate *deserializeHandcoded(char *buffer, int &bytesRead);

    //BSON buffer serialization
    bsoncxx::document::value serializeBSON();

    //BSON de-serialization:
    BoundingBoxCoordinate * deserializeBSON(bsoncxx::document::view doc);

};
BOOST_CLASS_TRACKING(BoundingBoxCoordinate, boost::serialization::track_never)

#endif
