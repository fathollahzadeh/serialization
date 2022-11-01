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

#ifndef TWITTER_USERIP_H
#define TWITTER_USERIP_H

#include <iostream>
#include <vector>
#include "URLEntity.h"
#include "User.h"
#include "Object.h"
#include "URLEntityIP.h"

using namespace std;

class UserIP : public Object {

public:
	long id;
    offset_ptr<char> idStr;
	offset_ptr<char> name;
	offset_ptr<char> screenName;
	offset_ptr<char> location;//nullable
	offset_ptr<char> url;//nullable
	offset_ptr<char> description;//nullable
	bool isProtected;
	bool isVerified;
	int followersCount;
	int friendsCount;
	int listedCount;
	int favouritesCount;
	int statusesCount;
	offset_ptr<char> createdAt;
	offset_ptr<char> profileBannerImageUrl;
	offset_ptr<char> profileImageUrlHttps;
	bool isDefaultProfile;
	vector <string> withheldInCountries;
	offset_ptr<char> withheldScope;

	//No longer supported (deprecated) attributes
	offset_ptr<URLEntityIP> descriptionURLEntities;
	int numOfURLEntity;
	bool isGeoEnabled;
	offset_ptr<char> lang;
	bool isContributorsEnabled;
	offset_ptr<char> profileBackgroundColor;
	offset_ptr<char> profileBackgroundImageUrl;
	offset_ptr<char> profileBackgroundImageUrlHttps;
	bool profileBackgroundTiled;
	offset_ptr<char> profileImageUrl;
	offset_ptr<char> profileLinkColor;
	offset_ptr<char> profileSidebarBorderColor;
	offset_ptr<char> profileSidebarFillColor;
	offset_ptr<char> profileTextColor;
	bool profileUseBackgroundImage;
	bool isDefaultProfileImage;
	int utcOffset;
	offset_ptr<char> timeZone;
	bool translator;
	bool isFollowRequestSent;
	bool showAllInlineMedia;

public:
	UserIP();

	virtual ~UserIP();

	//In place object:
	UserIP(User *user);

	void serialize(User *user);
};


#endif //TWITTER_USERIP_H
