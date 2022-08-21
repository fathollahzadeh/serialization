#include "ObjectWriter.h"

ObjectWriter::~ObjectWriter() {}

ObjectWriter::ObjectWriter(const string &fname, const string &method, int rlen) : ObjectWriter(method, rlen, PAGESIZE) {
    this->outStreamRegularFile.open(fname.c_str(), ofstream::binary | ofstream::trunc);
    this->outIndexFile.open((fname + ".index").c_str(), ofstream::binary | ofstream::trunc);
}

ObjectWriter::ObjectWriter(const string &method, int rlen, int pageSize) {
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

    this->currentPageNumber = 0;
    this->currentOffset = 0;
    this->pageBuffer = new char[2 * pageSize]; // this is our page
    memset(pageBuffer, '\0', 2 * PAGESIZE);

    this->rlen = rlen;
    this->row = 0;
    this->pageIndex = new int[rlen];
    this->objectIndex = new int[rlen];

    if (this->method == INPLACE) {
        thread::id this_id = this_thread::get_id();
        Allocator allocator;
        allocator.setUp(this->pageBuffer, 2 * PAGESIZE);
        Object::allocator[this_id] = allocator;
    }
}

void ObjectWriter::writeObjectToFile(TweetStatus *object) {
    //if serialization type is InPlace:
    if (this->method == INPLACE) {
        this->writeInPlaceObjectToFile(object);
    } else {
        char *buffer = pageBuffer;
        int objectSize = 0;

        // if serialization type is Handcoded:
        if (this->method == HANDCODED) {
            object->serializeHandcoded(buffer + currentOffset, objectSize);
        }
            // if serialization type is Boost:
        else if (this->method == BOOST) {
            object->serializeBoost(buffer + currentOffset, objectSize);
        }
            // if serialization type is ProtoBuf:
        else if (this->method == PROTOBUF) {
            TweetStatusProto *tweetStatusProto = new TweetStatusProto(object);
            tweetStatusProto->serializeProto(buffer + currentOffset, objectSize);
            delete tweetStatusProto;
        }

            // if serialization type is Bson:
        else if (this->method == BSON) {
            string jsonString = bsoncxx::to_json(object->serializeBSON());
            objectSize = jsonString.size();

            // insert json size to the first 4 byte of buffer
            memcpy(buffer + currentOffset, &objectSize, sizeof(int));

            // add json string to the buffer:
            strcpy(buffer + currentOffset + sizeof(objectSize), jsonString.c_str());

            // add json size to the object size:
            objectSize += sizeof(objectSize);
        }

            // if serialization type is FlatBuffers:
        else if (this->method == FLATBUF) {
            TweetStatusFlatBuffers *tweetStatusFlatBuffers = new TweetStatusFlatBuffers(object);
            tweetStatusFlatBuffers->serializeFlatBuffersIO(buffer + currentOffset, objectSize);
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
    thread::id this_id = this_thread::get_id();

    //Define a pointer for size of object:
    char *tPoint;

    // reserve space for object size:
    tPoint = this->pageBuffer + Object::allocator[this_id].getBytesUsed();
    Object::allocator[this_id].setBytesUsed(this->currentOffset + sizeofObject);


    //Serialize object:
    new TweetStatusIP(object);
    objectSize = Object::allocator[this_id].getBytesUsed() - (this->currentOffset + sizeofObject);

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
        Object::allocator[this_id].setBytesUsed(objectSize + sizeofObject);
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
    if (this->method == INPLACE) {
        thread::id this_id = this_thread::get_id();
        Object::allocator[this_id].setBytesUsed(0);
        new TweetStatusIP(object);
    } else {
        char *buffer = pageBuffer;
        int objectSize = 0;

        // if serialization type is Handcoded:
        if (this->method == HANDCODED) {
            object->serializeHandcoded(buffer, objectSize);
        }
            // if serialization type is Boost:
        else if (this->method == BOOST) {
            object->serializeBoost(buffer, objectSize);
        }
            // if serialization type is ProtoBuf:
        else if (this->method == PROTOBUF) {
            TweetStatusProto *tweetStatusProto = new TweetStatusProto(object);
            tweetStatusProto->serializeProto(buffer, objectSize);
            delete tweetStatusProto;
        }

            // if serialization type is Bson:
        else if (this->method == BSON) {
            bsoncxx::to_json(object->serializeBSON());
        }

            // if serialization type is FlatBuffers:
        else if (this->method == FLATBUF) {
            TweetStatusFlatBuffers *tweetStatusFlatBuffers = new TweetStatusFlatBuffers(object);
            tweetStatusFlatBuffers->serializeFlatBuffers(buffer, objectSize);
        }
    }
}

void ObjectWriter::writeObjectToFile(TweetStatusIP *object) {
    char *buffer = pageBuffer;
    int objectSize = object->objectsize;
    int sizeofObject = sizeof(objectSize);

    //Set object size in the reserved place:
    this->rootData.copyInPlaceInt(buffer + currentOffset, objectSize);

    //copy object to page:
    memcpy(buffer + currentOffset + sizeofObject, (char *) object, objectSize);

    //check capacity of the current page size
    //if current page is full should be write to the file and then reset the page
    if ((currentOffset + objectSize + sizeofObject) > PAGESIZE) {

        //Write in file:
        outStreamRegularFile.write(pageBuffer, PAGESIZE);

        //At this point, previous page is written in file.
        //All you need is to write this object in the new current page.
        //Re-write the last object again at correct place:
        memmove(pageBuffer, pageBuffer + currentOffset, objectSize + sizeofObject);

        currentPageNumber++;
        currentOffset = 0;
    }
    pageIndex[row] = currentPageNumber;
    objectIndex[row] = currentOffset;
    currentOffset += objectSize + sizeofObject;
    row++;
}

void ObjectWriter::writeObjectToFile(TweetStatusProto *object) {
    char *buffer = pageBuffer;
    int objectSize = 0;
    object->serializeProto(buffer + currentOffset, objectSize);

    //check capacity of the current page size
    //if current page is full should be write to the file and then reset the page
    if ((currentOffset + objectSize) > PAGESIZE) {

        //Write in file:
        auto tmpTime = chrono::steady_clock::now();
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

void ObjectWriter::writeObjectToFile(TweetStatusFlatBuffers *object) {
    char *buffer = pageBuffer;
    int objectSize = 0;

    object->serializeFlatBuffers(buffer + currentOffset, objectSize);

    if ((currentOffset + objectSize) > PAGESIZE) {

        //Write in file:
        auto tmpTime = chrono::steady_clock::now();
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

void ObjectWriter::writeObjectToNetworkPage(TweetStatus *object, int mSocket) {
    char *buffer = pageBuffer;
    int objectSize = 0;
    char *tPoint = pageBuffer;

    // reserve buffer for object size
    pageBuffer = pageBuffer + sizeof(objectSize);

    // if serialization type is Handcoded:
    if (this->method == HANDCODED) {
        object->serializeHandcoded(buffer + currentOffset + sizeof(objectSize), objectSize);
    }
        // if serialization type is Boost:
    else if (this->method == BOOST) {
        object->serializeBoost(buffer + currentOffset + sizeof(objectSize), objectSize);
    } else if (this->method == BSON) {
        string jsonString = bsoncxx::to_json(object->serializeBSON());
        objectSize = jsonString.size();

        // insert json size to the first 4 byte of buffer
        memcpy(buffer + currentOffset + sizeof(objectSize), &objectSize, sizeof(int));

        // add json string to the buffer:
        strcpy(buffer + currentOffset + 2 * sizeof(objectSize), jsonString.c_str());

        // add json size to the object size:
        objectSize += sizeof(objectSize);
    }

    memcpy(tPoint, &objectSize, sizeof(objectSize));
    objectSize += sizeof(objectSize);

    //check capacity of the current page size
    //if current page is full should write to the socket and then reset the page
    if ((currentOffset + objectSize) > NETWORK_PAGESIZE) {
        readACKFromSocket(mSocket);
        writeToSocket(mSocket, pageBuffer, currentOffset);
        memmove(pageBuffer, pageBuffer + currentOffset, objectSize);
        currentOffset = 0;
    }
    currentOffset += objectSize + sizeof(objectSize);
}

long ObjectWriter::readFromSocket(int mSocket, char *buffer, long contentSize) {
    //New Code:
    long bytesRead = 0;
    long status = 0;
    while (bytesRead < contentSize) {
        status = ::read(mSocket, buffer + bytesRead, contentSize - bytesRead);
        bytesRead += status;

        //Error Handling:
        if (!status)
            throw std::runtime_error("Can't read from socket");
    }
    return bytesRead;
}

long ObjectWriter::writeToSocket(int mSocket, char *buffer, long contentSize) {
    long bytesWritten = 0;
    long status = 0;
    while (bytesWritten < contentSize) {
        status = ::write(mSocket, buffer + bytesWritten, contentSize - bytesWritten);
        bytesWritten += status;

        //Error Handling:
        if (!status) std::runtime_error("Can't write to socket");
    }
    return bytesWritten;
}

bool ObjectWriter::readACKFromSocket(int mSocket) {
    char *ack = new char[1];
    long ackSize = readFromSocket(mSocket, ack, 1);
    if (ackSize != 1 && ack[0] != '1') {
        throw std::runtime_error("Can't read correct ACK from socket !");
    }
    return true;
}

bool ObjectWriter::writeACKToSocket(int mSocket) {

    return false;
}
