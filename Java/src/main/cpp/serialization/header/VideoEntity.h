#ifndef C_VIDEOENTITU_H
#define C_VIDEOENTITU_H

#include <iostream>
#include <vector>
#include "VariantEntity.h"

using namespace std;

class VideoEntity : public RootData {
public:
	vector<int> aspectRatio;
	int durationMillis;
	vector<VariantEntity *> variants;
private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {

		// Simply list all the fields to be serialized/deserialized.
		ar & aspectRatio;
		ar & durationMillis;
		ar & variants;

	}

public:
	virtual ~VideoEntity();

	VideoEntity();

	VideoEntity(const vector<int> &aspectRatio, int durationMillis, const vector<VariantEntity *> &variants);

	string toJSON();

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	VideoEntity *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON buffer serialization
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	VideoEntity *deserializeBSON(bsoncxx::document::view doc);
};

BOOST_CLASS_TRACKING(VideoEntity, boost::serialization::track_never
)

#endif //C_VIDEOENTITU_H
