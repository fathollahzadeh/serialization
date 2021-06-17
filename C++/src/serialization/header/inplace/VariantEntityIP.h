#ifndef TWITTER_VARIANTENTITYIP_H
#define TWITTER_VARIANTENTITYIP_H

#include <iostream>
#include "VariantEntity.h"
#include "Object.h"

using namespace std;

class VariantEntityIP : public Object {

private:
	long bitrate;
	offset_ptr<char> contentType;
	offset_ptr<char> url;

public:

	VariantEntityIP();

	virtual ~VariantEntityIP();

	//In place serialization:
	VariantEntityIP(VariantEntity *variantEntity);

	void serialize(VariantEntity *variantEntity);
};


#endif //TWITTER_VARIANTENTITYIP_H
