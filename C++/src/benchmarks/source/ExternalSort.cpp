#include "ExternalSort.h"
#include <iostream>
#include <TweetStatus.h>
#include <TweetStatusIP.h>

using namespace std;

int main(int argc, char *argv[]) {

	string fileName = argv[1];
	int numberOfFiles = atoi(argv[2]);
	int serializationType = atoi(argv[3]);
	int round = atoi(argv[4]);
	bool taskset;

	int ts = atoi(argv[5]);
	if (ts == 1)
		taskset = true;
	else
		taskset = false;

	//if serialization type is Handcoded or Boost:
	if (serializationType == 1 || serializationType == 3 || serializationType == 5) {
		ExternalSort <TweetStatus> externalSort(fileName, numberOfFiles, serializationType, round, taskset);

		externalSort.runTheExternalSort();
	}
		//if serialization type is InPlace:
	else if (serializationType == 2) {
		ExternalSort <TweetStatusIP> externalSort(fileName, numberOfFiles, serializationType, round, taskset);

		externalSort.runTheExternalSort();
	}
		//if serialization type is Proto:
	else if (serializationType == 4) {
		ExternalSort <TweetStatusProto> externalSort(fileName, numberOfFiles, serializationType, round, taskset);

		externalSort.runTheExternalSort();
	}
		//if serialization type is Proto:
	else if (serializationType == 6) {
		ExternalSort <TweetStatusFlatBuffers> externalSort(fileName, numberOfFiles, serializationType, round, taskset);

		externalSort.runTheExternalSort();
	}

	return 0;
}
