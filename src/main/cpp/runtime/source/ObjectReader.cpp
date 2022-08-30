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
        this->readObject(j);
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
            object->setBsonDoc(bsonObj);
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
}

void ObjectReader::readAllPages(char **pages) {
    for (int i = 0; i < networkPageCount; ++i) {
        int pageSize = NETWORK_PAGESIZE;
        if (fileSize - i * NETWORK_PAGESIZE < 0)
            pageSize = (int) (fileSize - (i - 1) * NETWORK_PAGESIZE);
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
