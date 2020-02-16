#ifndef HashtagEntity_H
#define HashtagEntity_H


#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"

using namespace std;


/*
 *	Contains only the declaration of HashtagEntity Class.
 */

class HashtagEntity : public RootData {

public:
    vector<int> indices;
    string text;
private:
    //Boost Serialization:
    friend class boost::serialization::access;

    //Serialize method for boost:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // Simply list all the fields to be serialized/deserialized.
        ar & indices;
        ar & text;
    }
public:
    //Default destructor:
    virtual ~HashtagEntity();

    //Default constructor:
    HashtagEntity();

    //Constructor with arguments:
    HashtagEntity(vector<int> indices, string text);

    //C++: Use explicitly for printing.
    string toJSON();

    //Hand Coded C++ serialization:
    //New API: Writes directly to File Page:
    char *serializeHandcoded(char *buffer, int &objectSize);

    //Hand Coded C++ de-serialization:
    HashtagEntity *deserializeHandcoded(char *buffer, int &bytesRead);

};
BOOST_CLASS_TRACKING(HashtagEntity, boost::serialization::track_never)

#endif
