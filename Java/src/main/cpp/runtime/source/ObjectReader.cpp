#include "ObjectReader.h"

ObjectReader::ObjectReader(const string &method) {
    if (strcasecmp(method.c_str(), "HandCoded") == 0) {
        this->method = HANDCODED;
    } else if (strcasecmp(method.c_str(), "InPlace") == 0) {
        this->method = INPLACE;
    } else if (strcasecmp(method.c_str(), "Boost") == 0) {
        this->method = BOOST;
    } else if (strcasecmp(method.c_str(), "ProtoBuf") == 0) {
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

    if (this->method == INPLACE)
        Object::allocator.setUp(this->pageBuffer, 2 * PAGESIZE);
}

void ObjectReader::readIndexesFromFile(const string &fname) {

    //Start to open index file for reade page index and object index maps:
    ifstream inIndexFile;
    inIndexFile.open((fname + ".index").c_str(), ifstream::binary);

    // Define a variable for index file size:
    long indexFileSize;

    //Check index file available:
    if (!inIndexFile.is_open()) {
        throw runtime_error("cannot find index file!!");
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
    for (int j = i; j < listSize; j++) {
        objectList[index++] = this->readObject(j);
    }
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
    } else if (this->method == BSON) {
        object = new TweetStatus();
        memcpy(&tempObjectSize, curBuffer + objectIndex[i], sizeof(int));
        //keep data in heap
        char *tBuffer = new char[tempObjectSize + 1];
        memcpy(tBuffer, curBuffer + objectIndex[i] + sizeof(int), tempObjectSize);
        memcpy(tBuffer + tempObjectSize, "\0", 1);

        bsoncxx::document::value bsonObj = bsoncxx::from_json(tBuffer);
        bsoncxx::document::view doc = bsonObj.view();
        object->deserializeBSON(doc);
        object->setBsonDoc(bsonObj);
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

void ObjectReader::readIO(long i, int n) {

    int listSize = (i + n) > this->rlen ? this->rlen : (i + n);
    //Iterate over all objects that you aspire to read.
    for (int j = i; j < listSize; j++)
        this->readPageFromFile(j);
}

void ObjectReader::readIO(long i) {
    //Initialize the buffer with the existing page:
    char *curBuffer = readPageFromFile(pageIndex[i]);

    //Read the object using a object index.
    //Deserialize object based on preference:
    int tempObjectSize = 0;

    //keep data in heap
    memcpy(&tempObjectSize, curBuffer + objectIndex[i], sizeof(int));
    char *tBuffer = new char[tempObjectSize];
    memcpy(tBuffer, curBuffer + objectIndex[i] + sizeof(tempObjectSize), tempObjectSize);
    delete[] tBuffer;
}


