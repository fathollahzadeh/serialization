#ifndef C_ADDITIONALMEDIAINFOENTITY_H
#define C_ADDITIONALMEDIAINFOENTITY_H

#include <iostream>
#include "RootData.h"

using namespace std;

class AdditionalMediaInfoEntity : public RootData {

public:
	string title;
	string description;
	bool embeddable;
	bool monetizable;

private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		// Simply list all the fields to be serialized/deserialized.
		ar & title;
		ar & description;
		ar & embeddable;
		ar & monetizable;
	}

public:
	virtual ~AdditionalMediaInfoEntity();

	AdditionalMediaInfoEntity();

	AdditionalMediaInfoEntity(const string &title, const string &description, bool embeddable, bool monetizable);

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	AdditionalMediaInfoEntity *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON buffer serialization
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	AdditionalMediaInfoEntity *deserializeBSON(bsoncxx::document::view doc);

};

BOOST_CLASS_TRACKING(AdditionalMediaInfoEntity, boost::serialization::track_never
)

#endif //C_ADDITIONALMEDIAINFOENTITY_H
