#ifndef MediaEntity_H
#define MediaEntity_H


#include <iostream>
#include <cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"
#include "MediaSizesEntity.h"
#include "VariantEntity.h"
#include "VideoEntity.h"
#include "AdditionalMediaInfoEntity.h"


using namespace std;


/*
 *	Contains only the declaration of MediaEntity Class.
 */

class MediaEntity : public RootData {

public:
    string displayURL;
    string expandedURL;
    long id;
    vector<int> indices;
    string mediaURL;
    string mediaURLHttps;
    MediaSizesEntity *sizes;
    string type;
    long sourceStatusId;
    string sourceStatusIdStr;
    string url;
    VideoEntity *videoInfo;
    AdditionalMediaInfoEntity *additionalMediaInfo;
private:
    //Boost Serialization:
    friend class boost::serialization::access;

    //Serialize method for boost:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {

        // Simply list all the fields to be serialized/deserialized.
        ar & displayURL;
        ar & expandedURL;
        ar & id;
        ar & indices;
        ar & mediaURL;
        ar & mediaURLHttps;
        ar & BOOST_SERIALIZATION_NVP(sizes);
        ar & type;
        ar & sourceStatusId;
        ar & sourceStatusIdStr;
        ar & url;
        ar & BOOST_SERIALIZATION_NVP(videoInfo);
        ar & BOOST_SERIALIZATION_NVP(additionalMediaInfo);

    }
public:
    //Default destructor:
    virtual ~MediaEntity();

    //Default constructor:
    MediaEntity();

    //Constructor with arguments:
    MediaEntity(string displayURL, string expandedURL, long id, vector<int> indices, string mediaURL,
                string mediaURLHttps,
                MediaSizesEntity *sizes, long sourceStatusId, string sourceStatusIdStr, string type, string url,
                VideoEntity *videoInfo, AdditionalMediaInfoEntity *additionalMediaInfo);

    //C++: Use explicitly for printing.
    string toJSON();

    //Hand Coded C++ serialization:
    //New API: Writes directly to File Page:
    char *serializeHandcoded(char *buffer, int &objectSize);

    //Hand Coded C++ de-serialization:
    MediaEntity *deserializeHandcoded(char *buffer, int &bytesRead);

    //BSON buffer serialization
    bsoncxx::document::value serializeBSON();

    //BSON de-serialization:
    MediaEntity * deserializeBSON(bsoncxx::document::view doc);

};
BOOST_CLASS_TRACKING(MediaEntity, boost::serialization::track_never)

#endif
