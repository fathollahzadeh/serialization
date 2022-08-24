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
