#include "VideoEntityIP.h"

VideoEntityIP::VideoEntityIP() {}

VideoEntityIP::~VideoEntityIP() {}

VideoEntityIP::VideoEntityIP(VideoEntity *videoEntity) {

	this->serialize(videoEntity);
}

void VideoEntityIP::serialize(VideoEntity *videoEntity) {
//TODO: implement InPlace to vector:
	//vector<int> aspectRatio;

	this->durationMillis = videoEntity->durationMillis;

	this->numOfVariantEntity = videoEntity->variants.size();
	this->variants = new VariantEntityIP[this->numOfVariantEntity];
	for (int i = 0; i < this->numOfVariantEntity; ++i) {
		this->variants[i].serialize(videoEntity->variants.at(i));
	}
}
