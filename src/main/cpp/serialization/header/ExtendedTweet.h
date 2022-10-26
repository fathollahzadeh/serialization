#ifndef CPP_EXTENDEDTWEET_H
#define CPP_EXTENDEDTWEET_H
#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"
#include "Entities.h"
#include "ExtendedEntities.h"

using namespace std;
class ExtendedTweet : public RootData {

private:
    //Boost Serialization:
    friend class boost::serialization::access;

    //Serialize method for boost:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // Simply list all the fields to be serialized/deserialized.
        ar & fullText;
        ar & displayTextRange;
        ar & BOOST_SERIALIZATION_NVP(entities);
        ar & BOOST_SERIALIZATION_NVP(extendedEntities);
    }
public:
    string fullText;
    vector<int> displayTextRange;
    Entities *entities;
    ExtendedEntities *extendedEntities;

    //Default destructor:
    virtual ~ExtendedTweet();

    //Default constructor:
    ExtendedTweet();

    //Constructor with arguments:
    ExtendedTweet(const string &fullText, const vector<int> &displayTextRange, Entities *entities,
                  ExtendedEntities *extendedEntities);

    //Hand Coded C++ serialization:
    //New API: Writes directly to File Page:
    char *serializeHandcoded(char *buffer, int &objectSize);

    //Hand Coded C++ de-serialization:
    ExtendedTweet *deserializeHandcoded(char *buffer, int &bytesRead);

    //BSON buffer serialization
    bsoncxx::document::value serializeBSON();

    //BSON de-serialization:
    ExtendedTweet *deserializeBSON(bsoncxx::document::view doc);
};

BOOST_CLASS_TRACKING(ExtendedTweet, boost::serialization::track_never)
#endif //CPP_EXTENDEDTWEET_H
