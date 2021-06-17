#ifndef TWITTER_MEDIAENTITYIP_H
#define TWITTER_MEDIAENTITYIP_H

#include <iostream>
#include <vector>
#include "MediaSizesEntity.h"
#include "VideoEntity.h"
#include "AdditionalMediaInfoEntity.h"
#include "MediaEntity.h"
#include "Object.h"
#include "MediaSizesEntityIP.h"
#include "VideoEntityIP.h"
#include "AdditionalMediaInfoEntityIP.h"

using namespace std;

class MediaEntityIP : public Object {

private:
	offset_ptr<char> displayURL;
	offset_ptr<char> expandedURL;
	long id;
	vector<int> indices;
	offset_ptr<char> mediaURL;
	offset_ptr<char> mediaURLHttps;
	offset_ptr<MediaSizesEntityIP> sizes;
	bool hasSizes;
	offset_ptr<char> type;
	long sourceStatusId;
	offset_ptr<char> sourceStatusIdStr;
	offset_ptr<char> url;
	offset_ptr<VideoEntityIP> videoInfo;
	bool hasVideoInfo;
	offset_ptr<AdditionalMediaInfoEntityIP> additionalMediaInfo;
	bool hasAdditionalMediaInfo;

public:

	MediaEntityIP();

	virtual ~MediaEntityIP();

	//In place object:
	MediaEntityIP(MediaEntity *mediaEntity);

	void serialize(MediaEntity *mediaEntity);
};


#endif //TWITTER_MEDIAENTITYIP_H
