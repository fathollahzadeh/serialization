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

#include "ObjectReader.h"

ObjectReader::ObjectReader(const string &method) {
    if (strcasecmp(method.c_str(), "HandCoded") == 0) {
        this->method = HANDCODED;
    } else if (strcasecmp(method.c_str(), "InPlace") == 0) {
        this->method = INPLACE;
    } else if (strcasecmp(method.c_str(), "Boost") == 0) {
        this->method = BOOST;
    } else if (strcasecmp(method.c_str(), "BoostBinary") == 0) {
        this->method = BOOSTBINARY;
    }else if (strcasecmp(method.c_str(), "ProtoBuf") == 0) {
        this->method = PROTOBUF;
    } else if (strcasecmp(method.c_str(), "Bson") == 0) {
        this->method = BSON;
    } else if (strcasecmp(method.c_str(), "FlatBuf") == 0) {
        this->method = FLATBUF;
    }
    this->currentOffset = 0;
    this->row = 0;
}

ObjectReader::ObjectReader(const string &fname, const string &method) : ObjectReader(method) {

    this->currentOffset = 0;

    //Allocates write page buffer:
    this->pageBuffer = new char[2 * PAGESIZE];
    memset(pageBuffer, '\0', 2 * PAGESIZE);

    this->inStreamRegularFile.open(fname.c_str(), ofstream::binary | ios::in);

    //Read the page and object map data from file
    this->readIndexesFromFile(fname);

    this->currentPageNumber = -1;

    //calculate object in each page:
    for (long i = 0; i < rlen; ++i) {
        if (objectInEachPage.find(pageIndex[i]) == objectInEachPage.end())
            objectInEachPage[pageIndex[i]] = 0;
        objectInEachPage[pageIndex[i]] = objectInEachPage[pageIndex[i]] + 1;
    }

    inStreamRegularFile.seekg(0, std::ifstream::end);
    fileSize = inStreamRegularFile.tellg();
    inStreamRegularFile.seekg(0, std::ifstream::beg);

    networkPageCount = ceil((double) fileSize / NETWORK_PAGESIZE);
}

void ObjectReader::readIndexesFromFile(const string &fname) {

    //Start to open index file for reade page index and object index maps:
    ifstream inIndexFile;
    inIndexFile.open((fname + ".index").c_str(), ifstream::binary);

    // Define a variable for index file size:
    long indexFileSize;

    //Check index file available:
    if (!inIndexFile.is_open()) {
        throw runtime_error("cannot find index file!!>> " + fname + ".index");
    }

    //Find index file size:
    inIndexFile.seekg(0, std::ifstream::end);
    indexFileSize = inIndexFile.tellg();
    inIndexFile.seekg(0, std::ifstream::beg);

    //Define a buffer for read index file:
    char *buffer = new char[indexFileSize];

    //Read data from file to buffer:
    inIndexFile.read(buffer, indexFileSize);

    int bytesRead = 0;
    //Read PageIndex size:
    int pageIndexVectorSize = this->rootData.parseInt(buffer + bytesRead);
    bytesRead += sizeof(pageIndexVectorSize);

    int value;

    //Read PageIndex vector from buffer:
    this->pageIndex = new int[pageIndexVectorSize];
    for (int i = 0; i < pageIndexVectorSize; i++) {
        value = this->rootData.parseInt(buffer + bytesRead);
        bytesRead += sizeof(value);
        pageIndex[i] = value;
    }
    //Read ObjectIndex size:
    int objectIndexVectorSize = this->rootData.parseInt(buffer + bytesRead);
    bytesRead += sizeof(objectIndexVectorSize);

    //Read ObjectIndex vector from buffer:
    this->objectIndex = new int[objectIndexVectorSize];
    for (int i = 0; i < objectIndexVectorSize; i++) {
        value = this->rootData.parseInt(buffer + bytesRead);
        bytesRead += sizeof(value);
        objectIndex[i] = value;
    }

    //Read ObjectIndex size:
    int objectLengthVectorSize = this->rootData.parseInt(buffer + bytesRead);
    bytesRead += sizeof(objectLengthVectorSize);

    //Read ObjectIndex vector from buffer:
    this->objectLength = new int[objectLengthVectorSize];
    for (int i = 0; i < objectLengthVectorSize; i++) {
        value = this->rootData.parseInt(buffer + bytesRead);
        bytesRead += sizeof(value);
        objectLength[i] = value;
    }

    //Free for memory leak:
    delete[] buffer;

    //Close time index file:
    inIndexFile.close();

    this->rlen = objectIndexVectorSize;
}

int ObjectReader::readObjects(int i, int n, TweetStatus **objectList) {
    int listSize = (i + n) > this->rlen ? this->rlen : (i + n);
    //Iterate over all objects that you aspire to read.
    int index = 0;
    for (int j = i; j < listSize; j++)
        objectList[index++] = this->readObject(j);
    return index;
}

TweetStatus *ObjectReader::readObject(int i) {
    TweetStatus *object = nullptr;
    char *curBuffer = readPageFromFile(pageIndex[i]);

    //Read the object using a object index.
    //Deserialize object based on preference:
    int tempObjectSize = 0;

    if (this->method == HANDCODED) {
        object = new TweetStatus();
        object->deserializeHandcoded(curBuffer + objectIndex[i], tempObjectSize);
    } else if (this->method == BOOST) {
        object = TweetStatus(false).deserializeBoost(curBuffer + objectIndex[i], tempObjectSize);
    } else if (this->method == BOOSTBINARY) {
        object = TweetStatus(false).deserializeBoostBinary(curBuffer + objectIndex[i], tempObjectSize);
    }
    else if (this->method == BSON) {
        object = new TweetStatus();
        memcpy(&tempObjectSize, curBuffer + objectIndex[i], sizeof(int));
        //keep data in heap
        char *tBuffer = new char[tempObjectSize + 1];
        memcpy(tBuffer, curBuffer + objectIndex[i] + sizeof(int), tempObjectSize);
        memcpy(tBuffer + tempObjectSize, "\0", 1);

        bsoncxx::document::value bsonObj = bsoncxx::from_json(tBuffer);
        bsoncxx::document::view doc = bsonObj.view();
        object->deserializeBSON(doc);
        //object->setBsonDoc(bsonObj);
        delete[] tBuffer;
    }
    return object;
}

int ObjectReader::readObjects(int i, int n, TweetStatusIP **objectList) {
    int listSize = (i + n) > this->rlen ? this->rlen : (i + n);
    //Iterate over all objects that you aspire to read.
    int index = 0;
    for (int j = i; j < listSize; j++)
        objectList[index++] = this->readObjectIP(j);

    return index;
}

TweetStatusIP *ObjectReader::readObjectIP(int i) {

    //Initialize the buffer with the existing page:
    char *curBuffer = readPageFromFile(pageIndex[i]);

    int objectSize = this->rootData.parseInPlaceInt(curBuffer + objectIndex[i]);

    //keep data in heap
    char *tBuffer = new char[objectSize];
    memcpy(tBuffer, curBuffer + objectIndex[i] + sizeof(objectSize), objectSize);

    TweetStatusIP *object = (TweetStatusIP *) tBuffer;
    object->objectsize = objectSize;
    return object;
}

int ObjectReader::readObjects(int i, int n, TweetStatusProto **objectList) {
    int listSize = (i + n) > this->rlen ? this->rlen : (i + n);
    //Iterate over all objects that you aspire to read.
    int index = 0;
    for (int j = i; j < listSize; j++)
        objectList[index++] = this->readObjectProto(j);
    return index;
}

TweetStatusProto *ObjectReader::readObjectProto(int i) {
    char *curBuffer = readPageFromFile(pageIndex[i]);

    //Read the object using a object index.
    //Deserialize object based on preference:
    int tempObjectSize = 0;

    TweetStatusProto *object = new TweetStatusProto();
    object->deserializeProto(curBuffer + objectIndex[i], tempObjectSize);
    return object;
}

int ObjectReader::readObjects(int i, int n, TweetStatusFlatBuffers **objectList) {

    int listSize = (i + n) > this->rlen ? this->rlen : (i + n);
    //Iterate over all objects that you aspire to read.
    int index = 0;
    for (int j = i; j < listSize; j++)
        objectList[index++] = this->readObjectFlatBuffers(j);

    return index;
}

TweetStatusFlatBuffers *ObjectReader::readObjectFlatBuffers(int i) {
    char *curBuffer = readPageFromFile(pageIndex[i]);

    //Read the object using a object index.
    //Deserialize object based on preference:
    int tempObjectSize = 0;

    //keep data in heap
    memcpy(&tempObjectSize, curBuffer + objectIndex[i], sizeof(int));
    char *tBuffer = new char[tempObjectSize];
    memcpy(tBuffer, curBuffer + objectIndex[i] + sizeof(tempObjectSize), tempObjectSize);

    TweetStatusFlatBuffers *object = new TweetStatusFlatBuffers();
    object->deserializeFlatBuffers(tBuffer, tempObjectSize);
    delete[] tBuffer;
    return object;
}


char *ObjectReader::readPageFromFile(int id) {
    //If page is already in RAM: Use from RAM:
    if (currentPageNumber == id) {
        return pageBuffer;
    }
        //Page not in RAM: Disk IO:
    else {
        long newPosition = (long) id * PAGESIZE;
        inStreamRegularFile.clear();
        inStreamRegularFile.seekg(newPosition, std::ifstream::beg);
        currentPageNumber = id;
        inStreamRegularFile.read(pageBuffer, PAGESIZE);
        return pageBuffer;
    }
}

int ObjectReader::getRlen() {
    return this->rlen;
}

int ObjectReader::getMethod() const {
    return method;
}

int ObjectReader::readIO(long i, int n, vector<char*> &list, vector<int> &listLength, int *pIndex, int *oIndex, int *oLength) {
    int listSize = (i + n) > this->rlen ? this->rlen : (i + n);
    int currOffset = 0;
    int currPageNumber = 0;
    char *tBuffer = new char[PAGESIZE];
    //Iterate over all objects that you aspire to read.
    int index = 0;
    for (int j = i; j < listSize; j++){
        //Initialize the buffer with the existing page:
        char *curBuffer = readPageFromFile(pageIndex[j]);

        //Read the object using a object index.
        //Deserialize object based on preference:
        int tempObjectSize = objectLength[j];

        if ((currOffset + tempObjectSize) > PAGESIZE) {
            list.push_back(tBuffer);
            listLength.push_back(currOffset);
            currOffset = 0;
            currPageNumber++;
            tBuffer = new char[PAGESIZE];
        }
        memcpy(tBuffer+currOffset, curBuffer + objectIndex[j], tempObjectSize);
        pIndex[index] = currPageNumber;
        oIndex[index] = currOffset;
        oLength[index] = tempObjectSize;
        currOffset += tempObjectSize;
        index++;
    }
    list.push_back(tBuffer);
    listLength.push_back(currOffset);
    return index;
}

void ObjectReader::readIO(long i, int n) {

    int listSize = (i + n) > this->rlen ? this->rlen : (i + n);
    //Iterate over all objects that you aspire to read.
    for (int j = i; j < listSize; j++)
        this->readIO(j);
}

void ObjectReader::readIO(long i) {
    //Initialize the buffer with the existing page:
    char *curBuffer = readPageFromFile(pageIndex[i]);

    //Read the object using a object index.
    //Deserialize object based on preference:
    int tempObjectSize = objectLength[i];
    int extra = 0;
    if (method == INPLACE) {
        memcpy(&tempObjectSize, curBuffer + objectIndex[i], sizeof(int));
        extra = sizeof(int);
    }
    //keep data in heap
    char *tBuffer = new char[tempObjectSize];
    memcpy(tBuffer, curBuffer + objectIndex[i] + extra, tempObjectSize);
    delete[] tBuffer;
}

void ObjectReader::readBinaryObjects(char **binaryObjects) {
    for (long i = 0; i < rlen; ++i) {
        char *curBuffer = readPageFromFile(pageIndex[i]);

        //Read the object using a object index.
        //Deserialize object based on preference:
        int tempObjectSize = objectLength[i];
        char *tBuffer = new char[tempObjectSize];
        memcpy(tBuffer, curBuffer + objectIndex[i], tempObjectSize);
        binaryObjects[i] = tBuffer;
    }
}


map<int, int> ObjectReader::getObjectInEachPage() {
    return this->objectInEachPage;
}

void ObjectReader::deSerializeNetworkBuffer(char *buffer, int pageSize, vector<TweetStatus *> &list) {
    int relativePosition = 0;
    do {
        int objectSize = 0;

        TweetStatus *object;
        if (this->method == HANDCODED) {
            object = new TweetStatus();
            object->deserializeHandcoded(buffer + relativePosition, objectSize);
        } else if (this->method == BOOST) {
            object = TweetStatus(false).deserializeBoost(buffer + relativePosition, objectSize);
        } else if (this->method == BOOSTBINARY) {
            object = TweetStatus(false).deserializeBoostBinary(buffer + relativePosition, objectSize);
        } else if (this->method == BSON) {
            object = new TweetStatus();
            memcpy(&objectSize, buffer + relativePosition, sizeof(int));
            //keep data in heap
            char *tBuffer = new char[objectSize + 1];
            memcpy(tBuffer, buffer + relativePosition + sizeof(int), objectSize);
            memcpy(tBuffer + objectSize, "\0", 1);

            bsoncxx::document::value bsonObj = bsoncxx::from_json(tBuffer);
            bsoncxx::document::view doc = bsonObj.view();
            object->deserializeBSON(doc);
            //object->setBsonDoc(bsonObj);
            delete[] tBuffer;
            relativePosition += sizeof(objectSize);
        }
        list.push_back(object);
        relativePosition += objectSize;
    } while (relativePosition < pageSize);
}

void ObjectReader::deSerializeNetworkBuffer(char *buffer, int pageSize, vector<TweetStatusIP *> &list) {
    int relativePosition = 0;
    do {
        int objectSize;
        objectSize = this->rootData.parseInPlaceInt(buffer + relativePosition);

        char *tBuffer = new char[objectSize];
        memcpy(tBuffer, buffer + relativePosition + sizeof(objectSize), objectSize);

        TweetStatusIP *object = (TweetStatusIP *) tBuffer;
        object->objectsize = objectSize;

        list.push_back(object);
        relativePosition += objectSize + sizeof(objectSize);
    } while (relativePosition < pageSize);
}

void ObjectReader::deSerializeNetworkBuffer(char *buffer, int pageSize, vector<TweetStatusProto *> &list) {
    int relativePosition = 0;
    do {
        int objectSize = 0;
        TweetStatusProto *object = new TweetStatusProto();
        object->deserializeProto(buffer + relativePosition, objectSize);
        list.push_back(object);
        relativePosition += objectSize;
    } while (relativePosition < pageSize);
}

void ObjectReader::deSerializeNetworkBuffer(char *buffer, int pageSize, vector<TweetStatusFlatBuffers *> &list) {
    int relativePosition = 0;
    do {
        int objectSize;

        //keep data in heap
        memcpy(&objectSize, buffer + relativePosition, sizeof(int));
        char *tBuffer = new char[objectSize];
        memcpy(tBuffer, buffer + relativePosition + sizeof(objectSize), objectSize);

        TweetStatusFlatBuffers *object = new TweetStatusFlatBuffers();
        object->deserializeFlatBuffers(tBuffer, objectSize);
        delete[] tBuffer;

        list.push_back(object);
        relativePosition += objectSize + sizeof(objectSize);
    } while (relativePosition < pageSize);
}

ObjectReader::~ObjectReader() {
    delete[] pageBuffer;
    delete[] pageIndex;
    delete[] objectIndex;
    delete[] objectLength;
}

void ObjectReader::readAllPages(char **pages) {
    for (int i = 0; i < networkPageCount; ++i) {
        int pageSize = NETWORK_PAGESIZE;
        if (fileSize - (i+1) * NETWORK_PAGESIZE < 0)
            pageSize = (int) (fileSize - i * NETWORK_PAGESIZE);
        pages[i] = new char[pageSize + sizeof(int)];
        memcpy(pages[i], &pageSize, sizeof(int));
        long newPosition = (long) i * pageSize;
        inStreamRegularFile.clear();
        inStreamRegularFile.seekg(newPosition, std::ifstream::beg);
        inStreamRegularFile.read(pages[i] + sizeof(int), pageSize);
    }
}

int ObjectReader::getNetworkPageCount() const {
    return networkPageCount;
}


