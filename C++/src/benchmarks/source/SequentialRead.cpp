//
// Created by saeed on 11/6/19.
//

#include "SequentialRead.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "Requires serialized file path!!" << endl;
        cout << "Requires Data Serialization Type:" << endl;
        cout << " 1: HandCoded Data serialization" << endl;
        cout << " 2: InPlace Data Serialization" << endl;
        cout << " 3: Boost Data Serialization" << endl;
        cout << " 4: ProtoData Data Serialization" << endl;
        cout << "Start position" << endl;
        cout << "End position" << endl;
        cout << "Run as: ./main <path/to/serialized/file> <serializationtype> <start> <end>" << endl;
        return 0;
    }

    //Set serialized file path
    string inFile = argv[1];

    int serializationType = atoi(argv[2]);

    int from = atoi(argv[3]);

    int numberofobjects = atoi(argv[4]);

    int round=atoi(argv[5]);

    switch (serializationType) {
        case 1:
        case 3:{
            SequentialRead<TweetStatus> *sequentialRead=new SequentialRead<TweetStatus>(inFile,serializationType,from,numberofobjects,round);
            sequentialRead->runTheSequentialRead();

            // free memory
            delete sequentialRead;
            break;
        }

        case 2: {
            SequentialRead<TweetStatusIP> *sequentialRead=new SequentialRead<TweetStatusIP>(inFile,serializationType,from,numberofobjects,round);
            sequentialRead->runTheSequentialRead();

            // free memory
            delete sequentialRead;
            break;
        }

        case 4:
            SequentialRead<TweetStatusProto> *sequentialRead=new SequentialRead<TweetStatusProto>(inFile,serializationType,from,numberofobjects,round);
            sequentialRead->runTheSequentialRead();

            // free memory
            delete sequentialRead;
            break;

    }
    return 0;

}

