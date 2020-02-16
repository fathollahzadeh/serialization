//
// Created by saeed on 11/17/19.
//

#include "RandomRead.h"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc < 2) {
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

    int round=atoi(argv[4]);

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
        case 3:{
            //Define variable for generate random object index:
            RandomRead<TweetStatus> *randomRead=new RandomRead<TweetStatus>(inFile,serializationType,cunt_to_read,round);
            randomRead->setObjectIndexes(objectIndexes);
            randomRead->runTheRandomRead();

            delete randomRead;
            break;
        }

        case 2: {
            //Define variable for generate random object index:
            RandomRead<TweetStatusIP> *randomRead=new RandomRead<TweetStatusIP>(inFile,serializationType,cunt_to_read,round);
            randomRead->setObjectIndexes(objectIndexes);
            randomRead->runTheRandomRead();

            delete randomRead;
            break;
        }

        case 4: {
            //Define variable for generate random object index:
            RandomRead<TweetStatusProto> *randomRead=new RandomRead<TweetStatusProto>(inFile,serializationType,cunt_to_read,round);
            randomRead->setObjectIndexes(objectIndexes);
            randomRead->runTheRandomRead();

            delete randomRead;

            break;
        }

    }
    return 0;

}

