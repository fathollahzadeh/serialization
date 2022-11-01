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

#include <iostream>
#include "ObjectWriter.h"
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"

using namespace std;

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string outDataPath = argv[2];
    int nrow = atoi(argv[3]);
    string method = argv[4];

    ObjectReader *reader = new ObjectReader(inDataPath,"HandCoded");
    ObjectWriter *writer = new ObjectWriter(outDataPath,method, nrow);

    int size = BATCHSIZE;
    for (int i=0; i<nrow;){
        TweetStatus ** tweets = new TweetStatus*[size];
        int rdSize =  reader->readObjects(i, size, tweets);
        for (int j = 0; j < rdSize ; j++) {
            writer->writeObjectToFile(tweets[j]);
            delete tweets[j];
        }
        i += rdSize;
        size = min(nrow - i, BATCHSIZE);
        delete[] tweets;
    }
    writer->flush();
    delete reader;
    delete writer;
    return 0;
}



