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

#ifndef OBJECTS_H
#define OBJECTS_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include "offset_ptr.h"
#include "Allocator.h"
#include "RootData.h"
#include <map>
#include <thread>

using namespace std;

class Object : public RootData {

public:

	//static Allocator allocator;
    static map<thread::id, Allocator> allocator;

	template<typename T>
	static T *malloc(size_t size) {
		return (T *) allocator[this_thread::get_id()].allocate(size);
	}

	static void *operator new(size_t size) {
		return allocator[this_thread::get_id()].allocate(size);
	}

	void *operator new[](size_t size) {
		return allocator[this_thread::get_id()].allocate(size);
	}

	static void operator delete(void *p) {};

};

#endif
