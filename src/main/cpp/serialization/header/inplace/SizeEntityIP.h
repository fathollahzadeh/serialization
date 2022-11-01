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

#ifndef TWITTER_SIZEENTITYIP_H
#define TWITTER_SIZEENTITYIP_H

#include <iostream>
#include "SizeEntity.h"
#include "Object.h"

using namespace std;

class SizeEntityIP : public Object {

private:
	int width;
	int height;
	offset_ptr<char> resize;

public:

	SizeEntityIP();

	virtual ~SizeEntityIP();

	//In place object:
	SizeEntityIP(SizeEntity *sizeEntity);

	void serialize(SizeEntity *sizeEntity);
};


#endif //TWITTER_SIZEENTITYIP_H
