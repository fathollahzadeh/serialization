#ifndef TWITTER_EXTENDEDENTITIESIP_H
#define TWITTER_EXTENDEDENTITIESIP_H

#include "ExtendedEntities.h"
#include "Object.h"
#include "MediaEntityIP.h"

class ExtendedEntitiesIP : public Object {

private:
	offset_ptr<MediaEntityIP> media;
	int numOfMediaEntity;

public:
	ExtendedEntitiesIP();

	virtual ~ExtendedEntitiesIP();

	//In place object:
	ExtendedEntitiesIP(ExtendedEntities *extendedEntities);

	void serialize(ExtendedEntities *extendedEntities);

};


#endif //TWITTER_EXTENDEDENTITIESIP_H