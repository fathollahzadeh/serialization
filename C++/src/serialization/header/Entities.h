#ifndef Entities_H
#define Entities_H


#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"
#include "HashtagEntity.h"
#include "MediaEntity.h"
#include "URLEntity.h"
#include "UserMentionEntity.h"
#include "SymbolEntity.h"
#include "PollEntity.h"

using namespace std;


/*
 *	Contains only the declaration of Entities Class.
 */

class Entities: public RootData {

public:
    vector<HashtagEntity *> hashtags;
    vector<MediaEntity *> media;
    vector<URLEntity *> urls;
    vector<UserMentionEntity *> userMentions;
    vector<SymbolEntity *> symbols;
    vector<PollEntity *> polls;
private:
    //Boost Serialization:
    friend class boost::serialization::access;

    //Serialize method for boost:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // Simply list all the fields to be serialized/deserialized.
        ar & hashtags;
        ar & media;
        ar & urls;
        ar & userMentions;
        ar & symbols;
        ar & polls;

    }
public:
    //Default destructor:
    virtual ~Entities();

    //Copy constructor:
    Entities(const Entities &obj);

    //Default constructor:
    Entities();

    //Constructor with arguments:
    Entities(vector<HashtagEntity *> hashtags, vector<MediaEntity *> media, vector<URLEntity *> urls,
               vector<UserMentionEntity *> userMentions, vector<SymbolEntity *> symbols,
               vector<PollEntity *> polls);

    //C++: Use explicitly for printing.
    string toJSON();

    //Hand Coded C++ serialization:
    //New API: Writes directly to File Page:
    char *serializeHandcoded(char *buffer, int &objectSize);

    //Hand Coded C++ de-serialization:
    Entities *deserializeHandcoded(char *buffer, int &bytesRead);

};
BOOST_CLASS_TRACKING(Entities, boost::serialization::track_never)

#endif
