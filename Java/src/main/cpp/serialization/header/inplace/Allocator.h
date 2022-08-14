#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include "Object.h"

using namespace std;

// simple memory allocator
class Allocator {

private:
	size_t numBytes;
	void *location;
	size_t bytesUsed;

public:
	Allocator() {
		numBytes = 0;
		bytesUsed = 0;
	}

	~Allocator() {
	}

	void setUp(char *pageBuffer, size_t numBytesIn) {
		numBytes = numBytesIn;
		location = pageBuffer;
		bytesUsed = 0;
	}


	// return a pointer to a memory location of size indicated... return a nullptr if 
	// we are past the end of the file:
	void *allocate(size_t size) {
		void *retVal = ((char *) location) + bytesUsed;
		bytesUsed += size;
		if (bytesUsed > numBytes) {
			throw invalid_argument("Bytes exhausted inside InPlace buffer!");
		}
		return retVal;
	}


	size_t getBytesUsed() {
		return bytesUsed;
	}


	void setBytesUsed(long bytesTaken) {
		bytesUsed = bytesTaken;
	}
};

#endif
