#include "SizeEntityIP.h"

SizeEntityIP::SizeEntityIP() {}

SizeEntityIP::~SizeEntityIP() {}


SizeEntityIP::SizeEntityIP(SizeEntity *sizeEntity) {

	this->serialize(sizeEntity);

}

void SizeEntityIP::serialize(SizeEntity *sizeEntity) {
	this->width = sizeEntity->width;
	this->height = sizeEntity->height;

	this->resize = malloc<char>(strlen(sizeEntity->resize.c_str()) + 1);
	strcpy(this->resize, sizeEntity->resize.c_str());
}
