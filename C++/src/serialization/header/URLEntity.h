#ifndef URLEntity_H
#define URLEntity_H


#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"

using namespace std;

class URLEntity : public RootData {

public:
	vector<int> indices;
	string displayURL;
	string expandedURL;
	string url;
private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {

		// Simply list all the fields to be serialized/deserialized.
		ar & indices;
		ar & displayURL;
		ar & expandedURL;
		ar & url;

	}

public:
	//Default destructor:
	virtual ~URLEntity();

	//Copy constructor:
	URLEntity(const URLEntity &obj);

	//Default constructor:
	URLEntity();

	//Constructor with arguments:
	URLEntity(vector<int> indices, string displayURL, string expandedURL, string url);

	//C++: Use explicitly for printing.
	string toJSON();

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	URLEntity *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON buffer serialization
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	URLEntity *deserializeBSON(bsoncxx::document::view doc);
};

BOOST_CLASS_TRACKING(URLEntity, boost::serialization::track_never
)
#endif
