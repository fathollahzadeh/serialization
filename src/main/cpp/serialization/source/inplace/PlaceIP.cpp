#include "PlaceIP.h"

PlaceIP::PlaceIP() {}

PlaceIP::~PlaceIP() {}

PlaceIP::PlaceIP(Place *place) {

	this->serialize(place);
}

void PlaceIP::serialize(Place *place) {
	this->name = malloc<char>(strlen(place->name.c_str()) + 1);
	strcpy(this->name, place->name.c_str());

	this->countryCode = malloc<char>(strlen(place->countryCode.c_str()) + 1);
	strcpy(this->countryCode, place->countryCode.c_str());

	this->id = malloc<char>(strlen(place->id.c_str()) + 1);
	strcpy(this->id, place->id.c_str());

	this->country = malloc<char>(strlen(place->country.c_str()) + 1);
	strcpy(this->country, place->country.c_str());

	this->placeType = malloc<char>(strlen(place->placeType.c_str()) + 1);
	strcpy(this->placeType, place->placeType.c_str());

	this->url = malloc<char>(strlen(place->url.c_str()) + 1);
	strcpy(this->url, place->url.c_str());

	this->fullName = malloc<char>(strlen(place->fullName.c_str()) + 1);
	strcpy(this->fullName, place->fullName.c_str());

	if (place->boundingBoxCoordinates != nullptr) {
		this->hasBoundingBoxCoordinates = true;
		this->boundingBoxCoordinates = new BoundingBoxCoordinateIP[1];
		this->boundingBoxCoordinates[0].serialize(place->boundingBoxCoordinates);
	} else
		this->hasBoundingBoxCoordinates = false;
}
