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

#ifndef TWITTER_PLACEIP_H
#define TWITTER_PLACEIP_H

#include <iostream>
#include "BoundingBoxCoordinate.h"
#include "Place.h"
#include "Object.h"
#include "BoundingBoxCoordinateIP.h"

using namespace std;

class PlaceIP : public Object {

private:
	offset_ptr<char> name;
	offset_ptr<char> countryCode;
	offset_ptr<char> id;
	offset_ptr<char> country;
	offset_ptr<char> placeType;
	offset_ptr<char> url;
	offset_ptr<char> fullName;
	offset_ptr<BoundingBoxCoordinateIP> boundingBoxCoordinates;
	bool hasBoundingBoxCoordinates;

public:

	PlaceIP();

	virtual ~PlaceIP();

	//In place serialization:
	PlaceIP(Place *place);

	void serialize(Place *place);
};


#endif //TWITTER_PLACEIP_H
