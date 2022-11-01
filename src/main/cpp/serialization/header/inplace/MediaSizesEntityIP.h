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

#ifndef TWITTER_MEDIASIZESENTITYIP_H
#define TWITTER_MEDIASIZESENTITYIP_H

#include "SizeEntity.h"
#include "MediaSizesEntity.h"
#include "Object.h"
#include "SizeEntityIP.h"

class MediaSizesEntityIP: public Object {

private:
    offset_ptr <SizeEntityIP>thumb;
    bool  hasThumb;
    offset_ptr <SizeEntityIP>large;
    bool  hasLarge;
    offset_ptr <SizeEntityIP>medium;
    bool hasMedium;
    offset_ptr <SizeEntityIP>small;
    bool hasSmall;

public:

    MediaSizesEntityIP();

    virtual ~MediaSizesEntityIP();

    //In place serialization:
    MediaSizesEntityIP(MediaSizesEntity *mediaSizesEntity);

    void serialize(MediaSizesEntity *mediaSizesEntity);
};


#endif //TWITTER_MEDIASIZESENTITYIP_H
