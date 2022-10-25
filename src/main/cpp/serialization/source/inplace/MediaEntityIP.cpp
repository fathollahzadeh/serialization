#include "MediaEntityIP.h"

MediaEntityIP::MediaEntityIP() {}

MediaEntityIP::~MediaEntityIP() {}

MediaEntityIP::MediaEntityIP(MediaEntity *mediaEntity) {

	this->serialize(mediaEntity);

}

void MediaEntityIP::serialize(MediaEntity *mediaEntity) {
	this->displayURL = malloc<char>(strlen(mediaEntity->displayURL.c_str()) + 1);
	strcpy(this->displayURL, mediaEntity->displayURL.c_str());

    this->idStr = malloc<char>(strlen(mediaEntity->idStr.c_str()) + 1);
    strcpy(this->idStr, mediaEntity->idStr.c_str());

	this->expandedURL = malloc<char>(strlen(mediaEntity->expandedURL.c_str()) + 1);
	strcpy(this->expandedURL, mediaEntity->expandedURL.c_str());

	this->id = mediaEntity->id;

	//TODO: implement inplace for vector:
	// vector<int> indices;

	this->mediaURL = malloc<char>(strlen(mediaEntity->mediaURL.c_str()) + 1);
	strcpy(this->mediaURL, mediaEntity->mediaURL.c_str());

	this->mediaURLHttps = malloc<char>(strlen(mediaEntity->mediaURLHttps.c_str()) + 1);
	strcpy(this->mediaURLHttps, mediaEntity->mediaURLHttps.c_str());

	if (mediaEntity->sizes != nullptr) {

		this->hasSizes = true;
		this->sizes = new MediaSizesEntityIP[1];
		this->sizes[0].serialize(mediaEntity->sizes);
	} else
		this->hasSizes = false;

	this->type = malloc<char>(strlen(mediaEntity->type.c_str()) + 1);
	strcpy(this->type, mediaEntity->type.c_str());

	this->sourceStatusId = mediaEntity->sourceStatusId;

	this->sourceStatusIdStr = malloc<char>(strlen(mediaEntity->sourceStatusIdStr.c_str()) + 1);
	strcpy(this->sourceStatusIdStr, mediaEntity->sourceStatusIdStr.c_str());

	this->url = malloc<char>(strlen(mediaEntity->url.c_str()) + 1);
	strcpy(this->url, mediaEntity->url.c_str());

	if (mediaEntity->videoInfo != nullptr) {
		hasVideoInfo = true;
		this->videoInfo = new VideoEntityIP[1];
		this->videoInfo[0].serialize(mediaEntity->videoInfo);
	} else
		hasVideoInfo = false;

	if (mediaEntity->additionalMediaInfo != nullptr) {
		hasAdditionalMediaInfo = true;
		this->additionalMediaInfo = new AdditionalMediaInfoEntityIP[1];
		this->additionalMediaInfo[0].serialize(mediaEntity->additionalMediaInfo);
	} else
		hasAdditionalMediaInfo = false;

}
