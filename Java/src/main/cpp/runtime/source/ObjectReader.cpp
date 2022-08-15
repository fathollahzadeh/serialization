#include "ObjectReader.h"

ObjectReader::ObjectReader(const string &method) {
    if (strcasecmp(method.c_str(), "HandCoded") == 0){
        this->method = HANDCODED;
    } else if (strcasecmp(method.c_str(), "InPlace") == 0){
        this->method = INPLACE;
    } else if (strcasecmp(method.c_str(), "Boost") == 0){
        this->method = BOOST;
    }else if (strcasecmp(method.c_str(), "ProtoBuf") == 0){
        this->method = PROTOBUF;
    }else if (strcasecmp(method.c_str(), "Bson") == 0){
        this->method = BSON;
    }else if (strcasecmp(method.c_str(), "FlatBuf") == 0){
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
    int tempObjectSize;
    //Initialize the buffer with the existing page:
    char *curBuffer = nullptr;

    // tem TweetStatus object:
    TweetStatus *object;

    int listSize = (i + n) > this->rlen ? this->rlen : (i + n);
    //Iterate over all objects that you aspire to read.
    int index = 0;
    for (int j = i; j < listSize; j++) {
        curBuffer = readPageFromFile(pageIndex[j]);

        //Read the object using a object index.
        //Deserialize object based on preference:
        tempObjectSize = 0;

        if (this->method == HANDCODED) {
            object = new TweetStatus();
            object->deserializeHandcoded(curBuffer + objectIndex[j], tempObjectSize);
        } else if (this->method == BOOST) {
            object = TweetStatus(false).deserializeBoost(curBuffer + objectIndex[j], tempObjectSize);
        } else if (this->method == BSON) {
            object = new TweetStatus();
            memcpy(&tempObjectSize, curBuffer + objectIndex[j], sizeof(int));
            //keep data in heap
            char *tBuffer = new char[tempObjectSize + 1];
            memcpy(tBuffer, curBuffer + objectIndex[j] + sizeof(int), tempObjectSize);
            memcpy(tBuffer + tempObjectSize, "\0", 1);

            bsoncxx::document::value bsonObj = bsoncxx::from_json(tBuffer);
            bsoncxx::document::view doc = bsonObj.view();
            object->deserializeBSON(doc);
            object->setBsonDoc(bsonObj);
            delete[] tBuffer;
        }
        objectList[index++] = object;
    }
    return index;
}

int ObjectReader::readObjects(int i, int n, TweetStatusIP **objectList) {

     //Initialize the buffer with the existing page:
    char *curBuffer = nullptr;

    // tem TweetStatus object:
    TweetStatusIP *object;

    int listSize = (i + n) > this->rlen ? this->rlen : (i + n);
    //Iterate over all objects that you aspire to read.
    int index = 0;
    for (int j = i; j < listSize; j++) {
        curBuffer = readPageFromFile(pageIndex[j]);

         int objectSize = 0;
        //Read object size:
        objectSize = this->rootData.parseInPlaceInt(curBuffer + objectIndex[j]);

        //keep data in heap
        char *tBuffer = new char[objectSize];
        memcpy(tBuffer, curBuffer + objectIndex[j] + sizeof(objectSize), objectSize);

        object = (TweetStatusIP *) tBuffer;
        object->objectsize = objectSize;
        objectList[index++] = object;
    }

    return index;
}

int ObjectReader::readObjects(int i, int n, TweetStatusProto **objectList) {

    int tempObjectSize;
    //Initialize the buffer with the existing page:
    char *curBuffer = nullptr;

    // tem TweetStatus object:
    TweetStatusProto *object;

    int listSize = (i + n) > this->rlen ? this->rlen : (i + n);
    //Iterate over all objects that you aspire to read.
    int index = 0;
    for (int j = i; j < listSize; j++) {
        curBuffer = readPageFromFile(pageIndex[j]);

        //Read the object using a object index.
        //Deserialize object based on preference:
        tempObjectSize = 0;

        object = new TweetStatusProto();
        object->deserializeProto(curBuffer + objectIndex[j], tempObjectSize);
        objectList[index++] = object;
    }

    return index;
}

int ObjectReader::readObjects(int i, int n, TweetStatusFlatBuffers **objectList) {
    int tempObjectSize;
    //Initialize the buffer with the existing page:
    char *curBuffer = nullptr;

    // tem TweetStatus object:
    TweetStatusFlatBuffers *object;

    int listSize = (i + n) > this->rlen ? this->rlen : (i + n);
    //Iterate over all objects that you aspire to read.
    int index = 0;
    for (int j = i; j < listSize; j++) {
        curBuffer = readPageFromFile(pageIndex[j]);

        //Read the object using a object index.
        //Deserialize object based on preference:
        tempObjectSize = 0;

        //keep data in heap
        memcpy(&tempObjectSize, curBuffer + objectIndex[j], sizeof(int));
        char *tBuffer = new char[tempObjectSize];
        memcpy(tBuffer, curBuffer + objectIndex[j] + sizeof(tempObjectSize), tempObjectSize);

        object = new TweetStatusFlatBuffers();
        object->deserializeFlatBuffers(tBuffer, tempObjectSize);
        delete[] tBuffer;
        objectList[index++] = object;
    }
    return index;
}


char *ObjectReader::readPageFromFile(int id) {
    //If page is already in RAM: Use from RAM:
    if (currentPageNumber == id) {
        return pageBuffer;
    }
        //Page not in RAM: Disk IO:
    else {
        long newPosition = id * PAGESIZE;
        inStreamRegularFile.clear();
        inStreamRegularFile.seekg(newPosition, std::ifstream::beg);
        currentPageNumber = id;
        inStreamRegularFile.read(pageBuffer, PAGESIZE);
        return pageBuffer;
    }
}