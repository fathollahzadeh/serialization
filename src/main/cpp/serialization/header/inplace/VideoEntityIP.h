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

#ifndef TWITTER_VIDEOENTITYIP_H
#define TWITTER_VIDEOENTITYIP_H

#include <iostream>
#include <vector>
#include "VariantEntity.h"
#include "VideoEntity.h"
#include "Object.h"
#include "VariantEntityIP.h"

using namespace std;

class VideoEntityIP : public Object {

private:
	vector<int> aspectRatio;
	int durationMillis;
	offset_ptr<VariantEntityIP> variants;
	int numOfVariantEntity;

public:
	VideoEntityIP();

	virtual ~VideoEntityIP();

	//In place object:
	VideoEntityIP(VideoEntity *videoEntity);

	void serialize(VideoEntity *videoEntity);

};


#endif //TWITTER_VIDEOENTITYIP_H
