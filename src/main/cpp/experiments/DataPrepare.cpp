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
#include "DataReader.h"

using namespace std;

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string outDataPath = argv[2];
    int nrow = atoi(argv[3]);

    DataReader dataReader;
    ObjectWriter *writer = new ObjectWriter(outDataPath, "HandCoded", nrow);
    ifstream infile;
    infile.open(inDataPath);
    string line;
    int l=0;
    while (getline(infile, line)) {
        Document d;
        d.Parse(line.c_str());
        TweetStatus *tweet = dataReader.generateTweetObject(d);
        writer->writeObjectToFile(tweet);

        //Free memory:
        delete tweet;

        if (++l>=nrow)
            break;
    }
    writer->flush();
    infile.close();
    infile.clear();

    delete writer;
    return 0;
}

