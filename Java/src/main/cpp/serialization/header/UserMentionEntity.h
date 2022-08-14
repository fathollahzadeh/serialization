#ifndef UserMentionEntity_H
#define UserMentionEntity_H


#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"

using namespace std;

class UserMentionEntity : public RootData {

public:
	long id;
	string idStr;
	vector<int> indices;
	string name;
	string screenName;
private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {

		// Simply list all the fields to be serialized/deserialized.
		ar & id;
		ar & idStr;
		ar & indices;
		ar & name;
		ar & screenName;

	}

public:
	//Default destructor:
	virtual ~UserMentionEntity();

	//Default constructor:
	UserMentionEntity();

	//Constructor with arguments:
	UserMentionEntity(long id, string idStr, vector<int> indices, string name, string screenName);

	//C++: Use explicitly for printing.
	string toJSON();

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	UserMentionEntity *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON buffer serialization
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	UserMentionEntity *deserializeBSON(bsoncxx::document::view doc);
};

BOOST_CLASS_TRACKING(UserMentionEntity, boost::serialization::track_never
)
#endif
