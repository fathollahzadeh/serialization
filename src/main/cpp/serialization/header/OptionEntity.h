#ifndef C_OPTIONENTITY_H
#define C_OPTIONENTITY_H

#include <iostream>
#include "RootData.h"

using namespace std;

class OptionEntity: public RootData {
public:
    int position;
    string text;
private:
    //Boost Serialization:
    friend class boost::serialization::access;

    //Serialize method for boost:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {

        // Simply list all the fields to be serialized/deserialized.
        ar & position;
        ar & text;
    }

public:
    OptionEntity();

    virtual ~OptionEntity();

    OptionEntity(int position, const string &text);

    //Hand Coded C++ serialization:
    //New API: Writes directly to File Page:
    char *serializeHandcoded(char *buffer, int &objectSize);

    //Hand Coded C++ de-serialization:
    OptionEntity *deserializeHandcoded(char *buffer, int &bytesRead);

    //BSON buffer serialization
    bsoncxx::document::value serializeBSON();

    //BSON de-serialization:
    OptionEntity * deserializeBSON(bsoncxx::document::view doc);
};

BOOST_CLASS_TRACKING(OptionEntity, boost::serialization::track_never)
#endif //C_OPTIONENTITY_H
