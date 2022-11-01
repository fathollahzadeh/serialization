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

#ifndef TWITTER_ADDITIONALMEDIAINFOENTITYIP_H
#define TWITTER_ADDITIONALMEDIAINFOENTITYIP_H

#include "AdditionalMediaInfoEntity.h"
#include "Object.h"

class AdditionalMediaInfoEntityIP : public Object {

private:
	offset_ptr<char> title;
	offset_ptr<char> description;
	bool embeddable;
	bool monetizable;
public:
	AdditionalMediaInfoEntityIP();

	virtual ~AdditionalMediaInfoEntityIP();

	//Create an InPlace object:
	AdditionalMediaInfoEntityIP(AdditionalMediaInfoEntity *additionalMediaInfoEntity);

	void serialize(AdditionalMediaInfoEntity *additionalMediaInfoEntity);

};


#endif //TWITTER_ADDITIONALMEDIAINFOENTITYIP_H
