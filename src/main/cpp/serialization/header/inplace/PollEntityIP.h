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

#ifndef TWITTER_POLLENTITYIP_H
#define TWITTER_POLLENTITYIP_H

#include <iostream>
#include "OptionEntity.h"
#include "PollEntity.h"
#include "Object.h"
#include "OptionEntityIP.h"

using namespace std;

class PollEntityIP : public Object {

private:
	offset_ptr<OptionEntityIP> options;
	int numOfOptionEntity;
	offset_ptr<char> endDatetime;
	offset_ptr<char> durationMinutes;

public:

	PollEntityIP();

	virtual ~PollEntityIP();

	//In place object:
	PollEntityIP(PollEntity *pollEntity);

	void serialize(PollEntity *pollEntity);
};


#endif //TWITTER_POLLENTITYIP_H
