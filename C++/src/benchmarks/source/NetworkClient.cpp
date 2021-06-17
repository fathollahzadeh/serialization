#include "NetworkClient.h"

using namespace std;

int main(int argc, char *argv[]) {

	//serializationType: [1-4]
	if (argc != 8) {
		cout << argc << endl;
		cout << "Arguments are: hostName serializationType objectType numObjects " << endl;
		cout << "Run as: ./NetworkClient serialization_1.se localhost 0 0 10000 3000 2000000" << endl;
		return 0;
	}

	//Set serialized file path
	string inFile = argv[1];
	string hostName = string(argv[2]);
	int serializationType = atoi(argv[3]);
	int numOfObjects = atoi(argv[4]);
	int portNumber = atoi(argv[5]);
	int ioType = atoi(argv[6]);
	long networkPageSize = atol(argv[7]);

	switch (serializationType) {
		case 1:
		case 3: {
			NetworkClient <TweetStatus> *networkClient = new NetworkClient<TweetStatus>(inFile, serializationType,
																						numOfObjects, hostName,
																						portNumber, networkPageSize,
																						ioType);
			networkClient->runTheNetworkClient();

			// free memory
			delete networkClient;
			break;
		}

		case 2: {
			NetworkClient <TweetStatusIP> *networkClient = new NetworkClient<TweetStatusIP>(inFile, serializationType,
																							numOfObjects, hostName,
																							portNumber, networkPageSize,
																							ioType);
			networkClient->runTheNetworkClient();

			// free memory
			delete networkClient;
			break;
		}

		case 4:
			NetworkClient <TweetStatusProto> *networkClient = new NetworkClient<TweetStatusProto>(inFile,
																								  serializationType,
																								  numOfObjects,
																								  hostName, portNumber,
																								  networkPageSize,
																								  ioType);
			networkClient->runTheNetworkClient();

			// free memory
			delete networkClient;
			break;

	}
	return 0;
}
