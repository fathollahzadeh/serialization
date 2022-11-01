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

#ifndef CPP_EXTENDEDTWEETIP_H
#define CPP_EXTENDEDTWEETIP_H


#include <vector>
#include <iostream>
#include "HashtagEntity.h"
#include "Object.h"
#include "EntitiesIP.h"
#include "ExtendedEntitiesIP.h"
#include "ExtendedTweet.h"

using namespace std;

class ExtendedTweetIP: public Object {

private:
    offset_ptr<char> fullText;
    vector<int> displayTextRange;
    offset_ptr<EntitiesIP> entities;
    bool hasEntities;
    offset_ptr<ExtendedEntitiesIP> extendedEntities;
    bool hasExtendedEntities;

public:
    ExtendedTweetIP();

    virtual ~ExtendedTweetIP();

    //In place object:
    ExtendedTweetIP(ExtendedTweet *extendedTweet);

    void serialize(ExtendedTweet *extendedTweet);

};


#endif //CPP_EXTENDEDTWEETIP_H
