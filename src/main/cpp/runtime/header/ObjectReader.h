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

#ifndef CPP_OBJECTREADER_H
#define CPP_OBJECTREADER_H

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "TweetStatus.h"
#include <TweetStatusIP.h>
#include <TweetStatusProto.h>
#include <TweetStatusFlatBuffers.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "Const.h"
#include "RootData.h"
#include "Object.h"
#include "math.h"

using namespace std;

class ObjectReader {
protected:
    long currentPageNumber;
    int currentOffset;
    int row;
    int rlen;
    int method;
    char *pageBuffer;
    int *pageIndex;
    int *objectIndex;
    int *objectLength;
    map<int, int> objectInEachPage;
    ifstream inStreamRegularFile;

private:
    RootData rootData;

    void  readIndexesFromFile(const string & fname);

    char * readPageFromFile(int id);

    int networkPageCount;
    long fileSize;

public:
    ObjectReader(const string & fname, const string &method);

    ObjectReader(const string &method);

    virtual ~ObjectReader();

    int readObjects(int i, int n, TweetStatus ** objectList);
    TweetStatus * readObject(int i);

    int readObjects(int i, int n, TweetStatusIP ** objectList);
    TweetStatusIP * readObjectIP(int i);

    int readObjects(int i, int n, TweetStatusProto ** objectList);
    TweetStatusProto * readObjectProto(int i);

    int readObjects(int i, int n, TweetStatusFlatBuffers ** objectList);
    TweetStatusFlatBuffers * readObjectFlatBuffers(int i);

    int readIO(long i, int n, vector<char*> &list, vector<int> &listLength, int *pIndex,int *oIndex, int *oLength);
    void readIO(long i, int n);
    void readIO(long i);
    void readBinaryObjects(char **binaryObjects);

    int getRlen();

    int getMethod() const;

    map<int, int> getObjectInEachPage();

    void deSerializeNetworkBuffer(char* buffer, int pageSize, vector<TweetStatus *> &list);

    void deSerializeNetworkBuffer(char* buffer, int pageSize, vector<TweetStatusIP *> &list);

    void deSerializeNetworkBuffer(char* buffer, int pageSize, vector<TweetStatusProto *> &list);

    void deSerializeNetworkBuffer(char* buffer, int pageSize, vector<TweetStatusFlatBuffers *> &list);

    void readAllPages(char **pages);

    int getNetworkPageCount() const;

};
#endif //CPP_OBJECTREADER_H
