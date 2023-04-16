/*
* Copyright 2023 Saeed Fathollahzadeh. All rights reserved.
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

#ifndef CPP_COMPLEXOBJECTIP13_H
#define CPP_COMPLEXOBJECTIP13_H


#include <Object.h>
#include "ComplexObjectIP14.h"
#include "ComplexObject13.h"

class ComplexObjectIP13 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP14> complexObject;

    ComplexObjectIP13();

    ComplexObjectIP13(ComplexObject13 *object);

    void serialize(ComplexObject13 *complexObject);
};


#endif //CPP_COMPLEXOBJECTIP13_H
