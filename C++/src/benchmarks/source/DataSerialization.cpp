//
// Created by saeed on 11/4/19.
//


#include <flatbuffers/TweetStatusFlatBuffers.h>
#include "DataSerialization.h"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc < 3) {
        cout << "Requires Tweeter JSON file path!!" << endl;
        cout << "Requires Data Serialization Type:" << endl;
        cout << " 1: HandCoded Data serialization" << endl;
        cout << " 2: InPlace Data Serialization" << endl;
        cout << " 3: Boost Data Serialization" << endl;
        cout << " 4: ProtoData Data Serialization" << endl;
        cout << "Run as: ./main <path/to/tweet.json> <serializationtype> <path/to/output/file>" << endl;
        return 0;
    }

    // Set input file path:
    string inputFile = argv[1];

    int serializationType = atoi(argv[2]);

    //Set output file path
    string outFile = argv[3];

    //set number Of Tweets
    long numberOfTweets=atoi(argv[4]);

    switch (serializationType) {
        case 1:
        case 3:
        case 5:{
            DataSerialization<TweetStatus> *dataSerialization=new DataSerialization<TweetStatus>(inputFile,outFile,serializationType,numberOfTweets);
            dataSerialization->runTheDataSerialization();

            delete dataSerialization;
            break;
        }

        case 2: {
            DataSerialization<TweetStatusIP> *dataSerialization=new DataSerialization<TweetStatusIP>(inputFile,outFile,serializationType,numberOfTweets);
            dataSerialization->runTheDataSerialization();

            delete dataSerialization;
            break;
        }

        case 4: {
            DataSerialization<TweetStatusProto> *dataSerialization=new DataSerialization<TweetStatusProto>(inputFile,outFile,serializationType,numberOfTweets);
            dataSerialization->runTheDataSerialization();

            delete dataSerialization;
            break;
        }
        case 6: {
            DataSerialization<TweetStatusFlatBuffers> *dataSerialization=new DataSerialization<TweetStatusFlatBuffers>(inputFile,outFile,serializationType,numberOfTweets);
            dataSerialization->runTheDataSerialization();

            delete dataSerialization;
            break;
        }
    }
    return 0;

}
