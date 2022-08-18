#ifndef TWITTER_COORDINATESIP_H
#define TWITTER_COORDINATESIP_H

#include "Coordinates.h"
#include "Object.h"

class CoordinatesIP : public Object {
private:
	offset_ptr<char> type;
	double *coordinates;

public:
	CoordinatesIP();

	virtual ~CoordinatesIP();

	//Create InPlace object:
	CoordinatesIP(Coordinates *coordinates);

	void serialize(Coordinates *coordinates);

	string getType();
};


#endif //TWITTER_COORDINATESIP_H