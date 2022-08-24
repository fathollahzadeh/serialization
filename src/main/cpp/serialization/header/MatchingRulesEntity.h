#ifndef C_MATCHINGRULESENTITY_H
#define C_MATCHINGRULESENTITY_H

#include "RootData.h"
#include <iostream>

using namespace std;

class MatchingRulesEntity : public RootData {
public:
	string tag;
	long id;
	string idStr;
private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		// Simply list all the fields to be serialized/deserialized.
		ar & tag;
		ar & id;
		ar & idStr;
	}

public:
	MatchingRulesEntity();

	virtual ~MatchingRulesEntity();

	MatchingRulesEntity(const string &tag, long id, const string &idStr);

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	MatchingRulesEntity *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON C++ serialization:
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	MatchingRulesEntity *deserializeBSON(bsoncxx::document::view doc);
};

BOOST_CLASS_TRACKING(MatchingRulesEntity, boost::serialization::track_never
)

#endif //C_MATCHINGRULESENTITY_H
