#include "RandomRead.h"

using namespace std;

int main(int argc, char *argv[]) {

	if (argc < 5) {
		cout << "Requires serialized file path!!" << endl;
		cout << "Requires Data Serialization Type:" << endl;
		cout << " 1: HandCoded Data serialization" << endl;
		cout << " 2: InPlace Data Serialization" << endl;
		cout << " 3: Boost Data Serialization" << endl;
		cout << " 4: ProtoData Data Serialization" << endl;
		cout << "Number of objects" << endl;
		cout << "Run as: ./main <path/to/serialized/file> <serializationtype> <number of objects>" << endl;
		return 0;
	}

	//Set serialized file path
	string inFile = argv[1];

	int serializationType = atoi(argv[2]);

	long cunt_to_read = atol(argv[3]);

	int round = atoi(argv[4]);

	bool taskset;

	int ts = atoi(argv[6]);
	if (ts == 1)
		taskset = true;
	else
		taskset = false;

	//read random list from  file:
	ifstream infile;
	infile.open(argv[5]);
	if (!infile.is_open()) {
		throw runtime_error("cannot find random list file!!.");
	}
	string line;
	vector<long> objectIndexes;
	while (getline(infile, line)) {
		objectIndexes.push_back(atol(line.c_str()));
	}


	switch (serializationType) {
		case 1:
		case 3:
		case 5: {
			//Define variable for generate random object index:
			RandomRead <TweetStatus> *randomRead = new RandomRead<TweetStatus>(inFile, serializationType, cunt_to_read,
																			   round, taskset);
			randomRead->setObjectIndexes(objectIndexes);
			randomRead->runTheRandomRead();

			delete randomRead;
			break;
		}

		case 2: {
			//Define variable for generate random object index:
			RandomRead <TweetStatusIP> *randomRead = new RandomRead<TweetStatusIP>(inFile, serializationType,
																				   cunt_to_read, round, taskset);
			randomRead->setObjectIndexes(objectIndexes);
			randomRead->runTheRandomRead();

			delete randomRead;
			break;
		}

		case 4: {
			//Define variable for generate random object index:
			RandomRead <TweetStatusProto> *randomRead = new RandomRead<TweetStatusProto>(inFile, serializationType,
																						 cunt_to_read, round, taskset);
			randomRead->setObjectIndexes(objectIndexes);
			randomRead->runTheRandomRead();

			delete randomRead;

			break;
		}
		case 6: {
			//Define variable for generate random object index:
			RandomRead <TweetStatusFlatBuffers> *randomRead = new RandomRead<TweetStatusFlatBuffers>(inFile,
																									 serializationType,
																									 cunt_to_read,
																									 round, taskset);
			randomRead->setObjectIndexes(objectIndexes);
			randomRead->runTheRandomRead();

			delete randomRead;

			break;
		}

	}
	return 0;

}

