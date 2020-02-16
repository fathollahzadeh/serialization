//
// Created by saeed on 12/13/19.
//

#include "ExternalSort.h"

#include <iostream>
#include <TweetStatus.h>
#include <TweetStatusIP.h>

using namespace std;



int main(int argc, char *argv[]) {

    string fileName=argv[1];
    int numberOfFiles=atoi(argv[2]);
    int serializationType=atoi(argv[3]);
    int round=atoi(argv[4]);

    //if serialization type is Handcoded or Boost:
    if (serializationType==1 || serializationType==3){
        ExternalSort<TweetStatus> externalSort(fileName,numberOfFiles,serializationType,round);

        externalSort.runTheExternalSort();
    }
    //if serialization type is InPlace:
    else if(serializationType==2){
        ExternalSort<TweetStatusIP> externalSort(fileName,numberOfFiles,serializationType,round);

        externalSort.runTheExternalSort();
    }
        //if serialization type is Proto:
    else if(serializationType==4){
        ExternalSort<TweetStatusProto> externalSort(fileName,numberOfFiles,serializationType,round);

        externalSort.runTheExternalSort();
    }

    return 0;
}
