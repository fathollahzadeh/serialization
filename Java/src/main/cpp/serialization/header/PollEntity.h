#ifndef C_POLLENTITY_H
#define C_POLLENTITY_H

#include <iostream>
#include <vector>
#include "OptionEntity.h"

using namespace std;

class PollEntity : public RootData {
public:
	vector<OptionEntity *> options;
	string endDatetime;
	string durationMinutes;
private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {

		// Simply list all the fields to be serialized/deserialized.
		for (int i = 0; i < options.size(); ++i) {
			ar & *options[i];
		}
		ar & endDatetime;
		ar & durationMinutes;
	}

public:
	PollEntity();

	virtual ~PollEntity();

	PollEntity(const vector<OptionEntity *> &options, const string &endDatetime, const string &durationMinutes);

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	PollEntity *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON buffer serialization
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	PollEntity *deserializeBSON(bsoncxx::document::view doc);
};

BOOST_CLASS_TRACKING(PollEntity, boost::serialization::track_never
)

#endif //C_POLLENTITY_H
