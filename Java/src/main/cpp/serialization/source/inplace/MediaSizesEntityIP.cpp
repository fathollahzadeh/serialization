#include "MediaSizesEntityIP.h"

MediaSizesEntityIP::MediaSizesEntityIP() {}

MediaSizesEntityIP::~MediaSizesEntityIP() {}

MediaSizesEntityIP::MediaSizesEntityIP(MediaSizesEntity *mediaSizesEntity) {

	this->serialize(mediaSizesEntity);

}

void MediaSizesEntityIP::serialize(MediaSizesEntity *mediaSizesEntity) {

	if (mediaSizesEntity->thumb != nullptr) {
		this->hasThumb = true;
		this->thumb = new SizeEntityIP[1];
		this->thumb[0].serialize(mediaSizesEntity->thumb);
	} else
		this->hasThumb = false;

	if (mediaSizesEntity->large != nullptr) {
		this->hasLarge = true;
		this->large = new SizeEntityIP[1];
		this->large[0].serialize(mediaSizesEntity->small);
	} else
		this->hasLarge = false;

	if (mediaSizesEntity->medium != nullptr) {
		this->hasMedium = true;
		this->medium = new SizeEntityIP[1];
		this->medium[0].serialize(mediaSizesEntity->small);
	} else
		this->hasMedium = false;

	if (mediaSizesEntity->small != nullptr) {
		this->hasSmall = true;
		this->small = new SizeEntityIP[1];
		this->small[0].serialize(mediaSizesEntity->small);
	} else
		this->hasSmall = false;
}
