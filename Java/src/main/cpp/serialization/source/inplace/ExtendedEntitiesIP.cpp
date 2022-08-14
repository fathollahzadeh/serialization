#include "ExtendedEntitiesIP.h"

ExtendedEntitiesIP::ExtendedEntitiesIP() {}

ExtendedEntitiesIP::~ExtendedEntitiesIP() {}

ExtendedEntitiesIP::ExtendedEntitiesIP(ExtendedEntities *extendedEntities) {

	this->serialize(extendedEntities);
}

void ExtendedEntitiesIP::serialize(ExtendedEntities *extendedEntities) {
	this->numOfMediaEntity = extendedEntities->media.size();
	this->media = new MediaEntityIP[this->numOfMediaEntity];
	for (int i = 0; i < this->numOfMediaEntity; ++i) {
		this->media[i].serialize(extendedEntities->media.at(i));
	}
}
