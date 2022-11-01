/*
* Copyright 2022 Saeed Fathollahzadeh. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

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
    offset_ptr<char> idStr;
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
