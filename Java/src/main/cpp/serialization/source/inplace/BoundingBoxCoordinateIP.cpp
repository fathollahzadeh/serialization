#include "BoundingBoxCoordinateIP.h"

BoundingBoxCoordinateIP::BoundingBoxCoordinateIP() {}

BoundingBoxCoordinateIP::~BoundingBoxCoordinateIP() {}

BoundingBoxCoordinateIP::BoundingBoxCoordinateIP(BoundingBoxCoordinate *boundingBoxCoordinate) {

	this->serialize(boundingBoxCoordinate);
}

void BoundingBoxCoordinateIP::serialize(BoundingBoxCoordinate *boundingBoxCoordinate) {
	this->type = malloc<char>(strlen(boundingBoxCoordinate->type.c_str()) + 1);
	strcpy(this->type, boundingBoxCoordinate->type.c_str());

	//TODO: implement inplace for vector
	//vector<vector<double *>> coordinates;
}
