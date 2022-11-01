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

#ifndef TWITTER_URLENTITYIP_H
#define TWITTER_URLENTITYIP_H

#include <iostream>
#include <vector>
#include "URLEntity.h"
#include "Object.h"

using namespace std;

class URLEntityIP : public Object {

private:
	vector<int> indices;
	offset_ptr<char> displayURL;
	offset_ptr<char> expandedURL;
	offset_ptr<char> url;

public:

	URLEntityIP();

	virtual ~URLEntityIP();

	//In place object:
	URLEntityIP(URLEntity *urlEntity);

	void serialize(URLEntity *urlEntity);
};


#endif //TWITTER_URLENTITYIP_H
