#include "ObjectReader.h"

ObjectReader::ObjectReader(const string &method) {
    this->method = method;
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

    if (strcasecmp(this->method.c_str(), "inplace") == 0)
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
        throw runtime_error("cannot find index file!!.");
    }

    //Find index file size:
    inIndexFile.seekg(0, inIndexFile.end);
    indexFileSize = inIndexFile.tellg();
    inIndexFile.seekg(0, inIndexFile.beg);

    //Define a buffer for read index file:
    char *buffer = new char[indexFileSize];

    //Read data from file to buffer:
    inIndexFile.read(buffer, indexFileSize);

    int bytesRead = 0;
    //Read PageIndex size:
    int pageIndexVectorSize = this->rootData.parseInPlaceInt(buffer + bytesRead);
    bytesRead += sizeof(pageIndexVectorSize);

    int value;

    //Read PageIndex vector from buffer:
    this->pageIndex = new int[pageIndexVectorSize];
    for (long i = 0; i < pageIndexVectorSize; i++) {
        value = this->rootData.parseInPlaceInt(buffer + bytesRead);
        bytesRead += sizeof(value);
        pageIndex[i] = value;
    }
    //Read ObjectIndex size:
    int objectIndexVectorSize = this->rootData.parseInPlaceInt(buffer + bytesRead);
    bytesRead += sizeof(objectIndexVectorSize);

    //Read ObjectIndex vector from buffer:
    this->objectIndex = new int[objectIndexVectorSize];
    for (long i = 0; i < objectIndexVectorSize; i++) {
        value = this->rootData.parseInPlaceInt(buffer + bytesRead);
        bytesRead += sizeof(value);
        objectIndex[i] = value;
    }
    //Free for memory leak:
    delete[] buffer;

    //Close time index file:
    inIndexFile.close();

    this->rlen = objectIndexVectorSize;
}
