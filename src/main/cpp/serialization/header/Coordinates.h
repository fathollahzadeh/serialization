#ifndef Coordinates_H
#define Coordinates_H

#include<iostream>
#include<cstring>
#include <vector>
#include <stdexcept>
#include "RootData.h"

using namespace std;

class Coordinates : public RootData {

public:
	string type;
	double coordinates[2];
private:
	//Boost Serialization:
	friend class boost::serialization::access;

	//Serialize method for boost:
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {

		// Simply list all the fields to be serialized/deserialized.
		ar & type;
		ar & coordinates;
	}

public:
	//Default destructor:
	virtual ~Coordinates();

	//Default constructor:
	Coordinates();

	//Constructor with arguments:
	Coordinates(string type, double *coordinates);

	//Hand Coded C++ serialization:
	//New API: Writes directly to File Page:
	char *serializeHandcoded(char *buffer, int &objectSize);

	//Hand Coded C++ de-serialization:
	Coordinates *deserializeHandcoded(char *buffer, int &bytesRead);

	//BSON buffer serialization
	bsoncxx::document::value serializeBSON();

	//BSON de-serialization:
	Coordinates *deserializeBSON(bsoncxx::document::view doc);
};

BOOST_CLASS_TRACKING(Coordinates, boost::serialization::track_never
)

#endif
