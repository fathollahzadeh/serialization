#ifndef TWITTER_BOUNDINGBOXCOORDINATEIP_H
#define TWITTER_BOUNDINGBOXCOORDINATEIP_H

#include "BoundingBoxCoordinate.h"
#include "Object.h"

class BoundingBoxCoordinateIP : public Object {
private:
	offset_ptr<char> type;
	vector <vector<double *>> coordinates;

public:
	BoundingBoxCoordinateIP();

	virtual ~BoundingBoxCoordinateIP();

	//Create InPlace object:
	BoundingBoxCoordinateIP(BoundingBoxCoordinate *boundingBoxCoordinate);

	void serialize(BoundingBoxCoordinate *boundingBoxCoordinate);
};


#endif //TWITTER_BOUNDINGBOXCOORDINATEIP_H
