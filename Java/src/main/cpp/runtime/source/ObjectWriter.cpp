#include "ObjectWriter.h"

ObjectWriter::~ObjectWriter() {}

ObjectWriter::ObjectWriter(const string &fname, const string &method, int rlen) : ObjectWriter(method, rlen, PAGESIZE) {
    this->outStreamRegularFile.open(fname.c_str(), ofstream::binary | ofstream::trunc);
    this->outIndexFile.open((fname + ".index").c_str(), ofstream::binary | ofstream::trunc);
}

ObjectWriter::ObjectWriter(const string &method, int rlen, int pageSize) {
    this->currentPageNumber = 0;
    this->currentOffset = 0;
    this->method = method;
    this->pageBuffer = new char[2 * pageSize]; // this is our page
    memset(pageBuffer, '\0', 2 * PAGESIZE);

    this->rlen = rlen;
    this->row = 0;
    this->pageIndex = new int[rlen];
    this->objectIndex = new int[rlen];

    if (strcasecmp(this->method.c_str(), "inplace") == 0)
        Object::allocator.setUp(this->pageBuffer, 2 * PAGESIZE);
}

void ObjectWriter::writeObjectToFile(TweetStatus *object) {
    //if serialization type is InPlace:
    if (strcasecmp(this->method.c_str(), "inPlace") == 0) {
        this->writeInPlaceObjectToFile(object);
    } else {
        char *buffer = pageBuffer;
        int objectSize = 0;

        // if serialization type is Handcoded:
        if (strcasecmp(this->method.c_str(), "HandCoded") == 0) {
            object->serializeHandcoded(buffer + currentOffset, objectSize);
        }
            // if serialization type is Boost:
        else if (strcasecmp(this->method.c_str(), "Boost") == 0) {
            object->serializeBoost(buffer + currentOffset, objectSize);
        }
            // if serialization type is ProtoBuf:
        else if (strcasecmp(this->method.c_str(), "ProtoBuf") == 0) {
            TweetStatusProto *tweetStatusProto = new TweetStatusProto(object);
            tweetStatusProto->serializeProto(buffer + currentOffset, objectSize);
            delete tweetStatusProto;
        }

            // if serialization type is Bson:
        else if (strcasecmp(this->method.c_str(), "Bson") == 0) {
            string jsonString = bsoncxx::to_json(object->serializeBSON());
            objectSize = jsonString.size();

            auto tmpTime = chrono::steady_clock::now();
            // insert json size to the first 4 byte of buffer
            memcpy(buffer + currentOffset, &objectSize, sizeof(int));

            // add json string to the buffer:
            strcpy(buffer + currentOffset + sizeof(objectSize), jsonString.c_str());

            // add json size to the object size:
            objectSize += sizeof(objectSize);
        }

            // if serialization type is FlatBuffers:
        else if (strcasecmp(this->method.c_str(), "FlatBuf") == 0) {
            TweetStatusFlatBuffers *tweetStatusFlatBuffers = new TweetStatusFlatBuffers(object);
            tweetStatusFlatBuffers->serializeFlatBuffers(buffer + currentOffset, objectSize);
        }

        //check capacity of the current page size
        //if current page is full should be write to the file and then reset the page
        if ((currentOffset + objectSize) > PAGESIZE) {

            //Write in file:
            outStreamRegularFile.write(pageBuffer, PAGESIZE);

            //At this point, previous page is written in file.
            //All you need is to write this object in the new current page.
            //Re-write the last object again at correct place:
            memmove(pageBuffer, pageBuffer + currentOffset, objectSize);
            currentPageNumber++;
            currentOffset = 0;
        }
        pageIndex[row] = currentPageNumber;
        objectIndex[row] = currentOffset;
        currentOffset += objectSize;
        row++;
    }
}

void ObjectWriter::flush() {
    //Write last page in file:
    this->outStreamRegularFile.write(pageBuffer, currentOffset);

    //Close Serialized Data file:
    this->outStreamRegularFile.close();

    //Write PageIndex Vector to the File:
    this->writeIndexToFile(pageIndex);

    //Write objectIndex Vector to the File:
    this->writeIndexToFile(objectIndex);

    //Close Index file:
    this->outIndexFile.close();

    //free memory:
    delete[] pageBuffer;
}

void ObjectWriter::writeInPlaceObjectToFile(TweetStatus *object) {
    int objectSize;
    int sizeofObject = sizeof(objectSize);

    //Define a pointer for size of object:
    char *tPoint;

    // reserve space for object size:
    tPoint = this->pageBuffer + Object::allocator.getBytesUsed();
    Object::allocator.setBytesUsed(this->currentOffset + sizeofObject);


    //Serialize object:
    new TweetStatusIP(object);
    objectSize = Object::allocator.getBytesUsed() - (this->currentOffset + sizeofObject);

    //Set object size in the reserved place:
    this->rootData.copyInPlaceInt(tPoint, objectSize);

    //Violated page boundary?
    if (this->currentOffset + sizeofObject + objectSize >= PAGESIZE) {

        //Write in file:
        auto tmpTime = chrono::steady_clock::now();
        this->outStreamRegularFile.write(pageBuffer, PAGESIZE);

        //At this point, previous page is written in file.
        //All you need is to write this object in the new current page.

        //Re-write the last object again at correct place:
        memmove(pageBuffer, pageBuffer + currentOffset, objectSize + sizeofObject);
        Object::allocator.setBytesUsed(objectSize + sizeofObject);
        currentPageNumber++;
        currentOffset = 0;
    }

    pageIndex[row] = currentPageNumber;
    objectIndex[row] = currentOffset;
    currentOffset += sizeofObject + objectSize;
    row++;
}

void ObjectWriter::writeIndexToFile(int *indexVector) {

    //Set Default Values to the PageBuffer:
    int buffersize = (this->rlen + 1) * sizeof(int);
    //Write indexes in file
    char *buffer = new char[buffersize];
    char *tbuffer = buffer;

    int tempItemSize = 0;
    //write page index size to the buffer:
    buffer = this->rootData.copyInt(buffer, this->rlen, tempItemSize);

    //write index vector to buffer:
    for (int i = 0; i < this->rlen; i++) {
        buffer = this->rootData.copyInt(buffer, indexVector[i], tempItemSize);
    }
    this->outIndexFile.write(tbuffer, tempItemSize);

    delete[] indexVector;
    delete[] tbuffer;
}

void ObjectWriter::serializeObject(TweetStatus *object) {

    //if serialization type is InPlace:
    if (strcasecmp(this->method.c_str(), "inPlace") == 0) {
        Object::allocator.setBytesUsed(0);
        new TweetStatusIP(object);
    } else {
        char *buffer = pageBuffer;
        int objectSize = 0;

        // if serialization type is Handcoded:
        if (strcasecmp(this->method.c_str(), "Handcoded") == 0) {
            object->serializeHandcoded(buffer, objectSize);
        }
            // if serialization type is Boost:
        else if (strcasecmp(this->method.c_str(), "Boost") == 0) {
            object->serializeBoost(buffer, objectSize);
        }
            // if serialization type is ProtoBuf:
        else if (strcasecmp(this->method.c_str(), "ProtoBuf") == 0) {
            TweetStatusProto *tweetStatusProto = new TweetStatusProto(object);
            tweetStatusProto->serializeProto(buffer, objectSize);
            delete tweetStatusProto;
        }

            // if serialization type is Bson:
        else if (strcasecmp(this->method.c_str(), "Bson") == 0) {
            bsoncxx::to_json(object->serializeBSON());
        }

            // if serialization type is FlatBuffers:
        else if (strcasecmp(this->method.c_str(), "FlatBuf") == 0) {
            TweetStatusFlatBuffers *tweetStatusFlatBuffers = new TweetStatusFlatBuffers(object);
            tweetStatusFlatBuffers->serializeFlatBuffers(buffer, objectSize);
        }
    }
}