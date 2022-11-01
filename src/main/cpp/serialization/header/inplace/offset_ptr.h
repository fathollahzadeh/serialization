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

#ifndef OFFSET_PTR_H
#define OFFSET_PTR_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

// offset pointer class
template<typename T>
class offset_ptr {

	size_t value;

public:

	T &operator[](size_t which) {
		return ((T *) (((char *) this) + value))[which];
	}

	T *operator->() {
		return ((T *) (((char *) this) + value));
	}

	T *operator*() {
		return ((T *) (((char *) this) + value))[0];
	}

	offset_ptr<T> &operator=(T *me) {
		value = ((char *) me - (char *) this);
		return *this;
	}

	offset_ptr<T> &operator=(offset_ptr<T> &me) {
		value = ((char *) &me - (char *) this) + me.value;
		return *this;
	}

	operator T *() {
		return (T *) (((char *) this) + value);
	}

	operator void *() {
		return (T *) (((char *) this) + value);
	}

	offset_ptr(T *fromMe) {
		value = ((char *) fromMe) - (char *) this;
	}

	offset_ptr() {
		value = -1;
	}

	bool is_null() {
		return value == -1;
	}

	offset_ptr(void *fromMe) {
		value = ((char *) fromMe) - (char *) this;
	}
};

#endif
