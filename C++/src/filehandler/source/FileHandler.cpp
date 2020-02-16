//
// Created by saeed on 11/4/19.
//

#include "FileHandler.h"

template<class T>
FileHandler<T>::FileHandler() {}

template<class T>
FileHandler<T>::~FileHandler() {}


template<class T>
FileHandler<T>::FileHandler(string fileName, int serializationType) {

    this->serializationType = serializationType;

    this->currentOffset = 0;

    this->pageSize = 256 * 1024; // 256K write page buffer size

    //Allocates write page buffer:
    this->pageBuffer = new char[2 * this->pageSize];

    //Set Default Values:
    memset(pageBuffer, '\0', 2 * this->pageSize);

    this->fileName = fileName;

    if (this->serializationType == 2) {
        char *tPageBuffer = pageBuffer;
        Object::allocator.setUp(tPageBuffer, 2 * this->pageSize);
    }

}

template<class T>
void FileHandler<T>::prepareToWrite() {
    //Opening the write file and keeping it open:
    this->outStreamRegularFile.open(fileName.c_str(), ofstream::binary | ofstream::trunc);

    //Opening the index file and keeping it open
    this->outIndexFile.open((fileName + ".index").c_str(), ofstream::binary | ofstream::trunc);

    this->currentPageNumber = 0;

    //reset io time:
    this->ioTime = 0;
    this->indexTime = 0;
}

template<class T>
void FileHandler<T>::prepareToRead() {
    //Opening serialized file and keeping it open
    this->inStreamRegularFile.open(fileName.c_str(), ofstream::binary | ios::in);

    //reset io time:
    this->ioTime = 0;
    this->indexTime = 0;

    //Read the page and object map data from file
    readIndexesFromFile();

    this->currentPageNumber = -1;

    this->totalOfObjects = this->objectIndex.size();

    //calculate object in each page:
    for (long i = 0; i<pageIndex.size(); ++i) {
        if (objectInEachPage.find(pageIndex.at(i)) == objectInEachPage.end())
            objectInEachPage[pageIndex.at(i)] = 0;
        objectInEachPage[pageIndex.at(i)] = objectInEachPage[pageIndex.at(i)] + 1;
    }

}

template<class T>
void FileHandler<T>::appendObjectToFile(TweetStatus *object) {

    //if serialization type is InPlace:
    if (this->serializationType == 2) {
        this->appendInPlaceObjectToFile(object);
    } else {
        char *buffer = pageBuffer;
        int objectSize = 0;

        // if serialization type is Handcoded:
        if (serializationType == 1) {
            object->serializeHandcoded(buffer + currentOffset, objectSize);
        }
            // if serialization type is Boost:
        else if (serializationType == 3) {
            object->serializeBoost(buffer + currentOffset, objectSize);
        }
            // if serialization type is ProtoBuf:
        else if (serializationType == 4) {
            TweetStatusProto *tweetStatusProto = new TweetStatusProto(object);
            tweetStatusProto->serializeProto(buffer + currentOffset, objectSize);
            delete tweetStatusProto;
        }


        //check capacity of the current page size
        //if current page is full should be write to the file and then reset the page
        if ((currentOffset + objectSize) > pageSize) {

            //Write in file:
            auto tmpTime = chrono::steady_clock::now();
            outStreamRegularFile.write(pageBuffer, pageSize);
            ioTime += chrono::duration<double>(chrono::steady_clock::now() - tmpTime).count();

            //At this point, previous page is written in file.
            //All you need is to write this object in the new current page.
            //Re-write the last object again at correct place:
            memmove(pageBuffer, pageBuffer + currentOffset, objectSize);

            currentPageNumber++;
            currentOffset = 0;
        }
        pageIndex.push_back(currentPageNumber);
        objectIndex.push_back(currentOffset);
        currentOffset += objectSize;
        countObject++;

    }
}

template<class T>
void FileHandler<T>::appendObjectToFile(TweetStatusIP *object) {
    char *buffer = pageBuffer;
    int objectSize = object->objectsize;
    int sizeofObject = sizeof(objectSize);

    //Set object size in the reserved place:
    this->copyInPlaceInt(buffer + currentOffset, objectSize);

    //copy object to page:
    memcpy(buffer + currentOffset + sizeofObject, (char *) object, objectSize);

    //check capacity of the current page size
    //if current page is full should be write to the file and then reset the page
    if ((currentOffset + objectSize + sizeofObject) > pageSize) {

        //Write in file:
        auto tmpTime = chrono::steady_clock::now();
        outStreamRegularFile.write(pageBuffer, pageSize);
        ioTime += chrono::duration<double>(chrono::steady_clock::now() - tmpTime).count();

        //At this point, previous page is written in file.
        //All you need is to write this object in the new current page.
        //Re-write the last object again at correct place:
        memmove(pageBuffer, pageBuffer + currentOffset, objectSize + sizeofObject);

        currentPageNumber++;
        currentOffset = 0;
    }
    pageIndex.push_back(currentPageNumber);
    objectIndex.push_back(currentOffset);
    currentOffset += objectSize + sizeofObject;
    countObject++;
}

template<class T>
void FileHandler<T>::appendObjectToFile(TweetStatusProto *object) {

    char *buffer = pageBuffer;
    int objectSize = 0;
    object->serializeProto(buffer + currentOffset, objectSize);

    //check capacity of the current page size
    //if current page is full should be write to the file and then reset the page
    if ((currentOffset + objectSize) > pageSize) {

        //Write in file:
        auto tmpTime = chrono::steady_clock::now();
        outStreamRegularFile.write(pageBuffer, pageSize);
        ioTime += chrono::duration<double>(chrono::steady_clock::now() - tmpTime).count();

        //At this point, previous page is written in file.
        //All you need is to write this object in the new current page.
        //Re-write the last object again at correct place:
        memmove(pageBuffer, pageBuffer + currentOffset, objectSize);

        currentPageNumber++;
        currentOffset = 0;
    }
    pageIndex.push_back(currentPageNumber);
    objectIndex.push_back(currentOffset);
    currentOffset += objectSize;
    countObject++;

}

template<class T>
void FileHandler<T>::appendInPlaceObjectToFile(TweetStatus *object) {

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
    this->copyInPlaceInt(tPoint, objectSize);

    //Violated page boundary?
    if (this->currentOffset + sizeofObject + objectSize >= this->pageSize) {

        //Write in file:
        auto tmpTime = chrono::steady_clock::now();
        this->outStreamRegularFile.write(pageBuffer, pageSize);
        ioTime += chrono::duration<double>(chrono::steady_clock::now() - tmpTime).count();

        //At this point, previous page is written in file.
        //All you need is to write this object in the new current page.

        //Re-write the last object again at correct place:
        memmove(pageBuffer, pageBuffer + currentOffset, objectSize + sizeofObject);
        Object::allocator.setBytesUsed(objectSize + sizeofObject);
        currentPageNumber++;
        currentOffset = 0;
    }

    pageIndex.push_back(currentPageNumber);
    objectIndex.push_back(currentOffset);
    currentOffset += sizeofObject + objectSize;
    countObject++;
}

template<class T>
void FileHandler<T>::writeIndexToFile(vector<long> indexVector) {

    //Set Default Values to the PageBuffer:

    long buffersize = (indexVector.size() + 1) * sizeof(long);
    //Write indexes in file
    char *buffer = new char[buffersize];
    char *tbuffer = buffer;

    int tempItemSize = 0;
    //write page index size to the buffer:
    buffer = this->copyLong(buffer, indexVector.size(), tempItemSize);

    //write index vector to buffer:
    for (long i = 0; i<indexVector.size(); ++i) {

        buffer = this->copyLong(buffer, indexVector.at(i), tempItemSize);
    }
    auto tmpTime = chrono::steady_clock::now();
    this->outIndexFile.write(tbuffer, tempItemSize);
    ioTime += chrono::duration<double>(chrono::steady_clock::now() - tmpTime).count();

    indexVector.clear();
    indexVector.shrink_to_fit();
    delete[] tbuffer;
}

template<class T>
void FileHandler<T>::appendObjectToFileFlush() {

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

template<class T>
void FileHandler<T>::getObjectsFromFileFlush() {

    //Free memory:
    delete[] pageBuffer;
}

template<class T>
void FileHandler<T>::readIndexesFromFile() {

    //Start to open index file for reade page index and object index maps:
    ifstream inIndexFile;
    inIndexFile.open((fileName + ".index").c_str(), ifstream::binary);

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

    long bytesRead = 0;
    //Read PageIndex size:
    long pageIndexVectorSize = this->parseLong(buffer + bytesRead);
    bytesRead += sizeof(pageIndexVectorSize);

    long value;

    //Read PageIndex vector from buffer:
    for (long i = 0; i < pageIndexVectorSize; i++) {

        value = this->parseLong(buffer + bytesRead);
        bytesRead += sizeof(value);
        pageIndex.push_back(value);
    }
    //Read ObjectIndex size:
    long objectIndexVectorSize = this->parseLong(buffer + bytesRead);
    bytesRead += sizeof(objectIndexVectorSize);

    //Read ObjectIndex vector from buffer:
    for (long i = 0; i < objectIndexVectorSize; i++) {

        value = this->parseLong(buffer + bytesRead);
        bytesRead += sizeof(value);
        objectIndex.push_back(value);
    }
    //Free for memory leak:
    delete[] buffer;

    //Close time index file:
    inIndexFile.close();

}

template<class T>
char *FileHandler<T>::readPageFromFile(long id) {
    //If page is already in RAM: Use from RAM:
    if (currentPageNumber == id) {
        return pageBuffer;
    }
        //Page not in RAM: Disk IO:
    else {
        long newPosition = id * pageSize;
        inStreamRegularFile.clear();
        auto tmpTime = chrono::steady_clock::now();
        inStreamRegularFile.seekg(newPosition, inStreamRegularFile.beg);
        currentPageNumber = id;
        inStreamRegularFile.read(pageBuffer, pageSize);
        ioTime += chrono::duration<double>(chrono::steady_clock::now() - tmpTime).count();
        return pageBuffer;
    }
}

template<class T>
void FileHandler<T>::getObjectsFromFile(long i, long n, vector<T *> &objectList) {

    int tempObjectSize;
    //Initialize the buffer with the existing page:
    char *curBuffer = nullptr;

    // tem TweetStatus object:
    T *object;

    long listSize = (i + n) > this->totalOfObjects ? this->totalOfObjects : (i + n);
    //Iterate over all objects that you aspire to read.
    for (long j = i; j < listSize; j++) {

        curBuffer = readPageFromFile(pageIndex[j]);

        //Read the object using a object index.
        //Deserialize object based on preference:
        tempObjectSize = 0;

        switch (this->serializationType) {
            // de-serialize handcoded object from file:
            case 1: {
                object = new T();
                object->deserializeHandcoded(curBuffer + objectIndex[j], tempObjectSize);
                break;
            }
                // de-serialize InPlace object from file:
            case 2: {

                int objectSize = 0;
                //Read object size:
                objectSize = parseInPlaceInt(curBuffer);

                //keep data in heap
                auto tmpTime = chrono::steady_clock::now();
                char * tBuffer=new char[objectSize];
                memcpy(tBuffer,curBuffer + sizeof(objectSize),objectSize);
                ioTime += chrono::duration<double>(chrono::steady_clock::now() - tmpTime).count();

                T *inPlaceObject = (T *) tBuffer;
                inPlaceObject->objectsize=objectSize;
                object = inPlaceObject;
                break;
            }
                // de-serialize boost object from file:
            case 3: {
                object = T(false).deserializeBoost(curBuffer + objectIndex[j], tempObjectSize);
                break;
            }
                // de-serialize poroto object from file:
            case 4: {
                object = new T();
                object->deserializeProto(curBuffer + objectIndex[j], tempObjectSize);
                break;
            }
        }

        objectList.push_back(object);
    }
}
//Simply reads the next network page from file:
template<class T>
long FileHandler<T>::getNextNetworkPage(char * networkBuffer) {
    //PROTOBUF, BOOST, HANDCODED, INPLACE:
    if (this->pageIndex.size() > 0) {
        long pageSize=inStreamRegularFile.read(networkBuffer+ sizeof(long), this->networkPageSize- sizeof(long)).gcount();

        //write network page size in page:
        cout<<"curNetworkPageSize= "<<pageSize<<endl;
        memcpy(networkBuffer, &pageSize, sizeof(long));
        return pageSize;
    } else
        return 0;
}

// define a method for get network page count from RAM object list
template<class T>
int FileHandler<T>::getNextNetworkPage(vector<T *> &objectList, int startIndex, int numObjects, char *networkBuffer) {

    //Other serialization techniques:
    int curObjectSize;
    int currentOffset;

    // Empty Buffer;
    currentOffset = 0;
    char *tempBuffer = networkBuffer;

    //Need to copy network page size in page
    currentOffset+= sizeof(long);

    //Need to copy number of objects in page at beginning:
    currentOffset += sizeof(int);

    //int previousOffset = 0;
    long curNetworkPageSize=0;

    int i = 0;
    for (i = startIndex; i < numObjects; i++) {
        //InPlace:
        if (this->serializationType == 2) {

            curObjectSize = objectList.at(i)->objectsize;

            //Copy object size:
            this->copyInPlaceInt(tempBuffer + currentOffset, curObjectSize);
            currentOffset += sizeof(int);

            //Copy object:
            memcpy(tempBuffer + currentOffset, (char *)objectList.at(i), curObjectSize);
            currentOffset += curObjectSize;
        } else {

             curObjectSize = 0;
            // objectList.at(i)->serialize(tempBuffer + currentOffset, curObjectSize);
            // if serialization type is Handcoded:
            if (serializationType == 1) {
                objectList.at(i)->serializeHandcoded(tempBuffer + currentOffset, curObjectSize);
            }
                // if serialization type is Boost:
            else if (serializationType == 3) {
                objectList.at(i)->serializeBoost(tempBuffer + currentOffset, curObjectSize);
            }
                // if serialization type is ProtoBuf:
            else if (serializationType == 4) {
                objectList.at(i)->serializeProto(tempBuffer + currentOffset, curObjectSize);
            }
            currentOffset += curObjectSize;
        }
        //Violated page boundary?
        if (currentOffset > networkPageSize) {
            break;
        }
        curNetworkPageSize=currentOffset;
        //Else, object fits in current page:
    }

    //write network page size in page:
    cout<<"curNetworkPageSize= "<<curNetworkPageSize<<endl;
    memcpy(networkBuffer, &curNetworkPageSize, sizeof(long));

    // Write total number of objects in page:
    //int totalObjectInPage = i - startIndex;
    //memcpy(networkBuffer+ sizeof(long), &totalObjectInPage, sizeof(int));

    //This is the index to be read next:
    return i;
}

template<class T>
int FileHandler<T>::parseNetworkPage(vector <T *>& objectList, char * networkBuffer) {

    char *tempBuffer = networkBuffer;
    int bytesRead = 0;

    // Total number of objects in this page:
    int numObjects = parseInt(tempBuffer+bytesRead); bytesRead += sizeof(int);
    int currentObjectSize = 0;

    //DELETE:
    cout << "parseNetworkPage:: " << objectList.size() << endl;

    T * object = NULL;

    for (int j = 0; j < numObjects; j++) {

        switch (this->serializationType) {
            // de-serialize handcoded object from buffer:
            case 1: {
                object = new T();
                object->deserializeHandcoded(tempBuffer + bytesRead, currentObjectSize);
                break;
            }
                // de-serialize InPlace object from buffer:
            case 2: {
                object = T().deserializeInPlace(tempBuffer + bytesRead);
                currentObjectSize = object->objectsize;
                break;
            }
                // de-serialize boost object from buffer:
            case 3: {
                object = T(false).deserializeBoost(tempBuffer + bytesRead, currentObjectSize);
                break;
            }
                // de-serialize poroto object from buffer:
            case 4: {
                object = new T();
                object->deserializeProto(tempBuffer + bytesRead, currentObjectSize);
                break;
            }
        }
        // Skip "currentObjectSize" bytes:
        bytesRead += currentObjectSize;
        cout << "Total Objects Parsed: " << objectList.size() << endl;
        objectList.push_back(object);
    }
}
//Number of network pages to be sent from disk:
template<class T>
long FileHandler<T>::getNetworkPageCount(int numObjects) {
    long contentSize = 0;

    // network page without page size
    long tmpNetworkPageSize=this->networkPageSize- sizeof(long);

    //PROTOBUF, BOOST, HANDCODED, INPLACE:
    if (pageIndex.size() > numObjects) {
        contentSize = (1 + pageIndex.at(numObjects - 1)) * (long)this->pageSize;
    } else {
        contentSize = (1 + pageIndex.at(pageIndex.size() - 1)) * (long) this->pageSize;
    }

    //Return pagecount:
    if (contentSize % tmpNetworkPageSize == 0) {
        return (contentSize/tmpNetworkPageSize);
    }
    else {
        return (1 + (contentSize/tmpNetworkPageSize));
    }
}

template<class T>
long FileHandler<T>::getNumberOfObjects() {
    return this->totalOfObjects;
}

template<class T>
map<long, long> FileHandler<T>::getEachPageObjectCount() {
    return objectInEachPage;
}

template<class T>
double FileHandler<T>::getIoTime() const {
    return this->ioTime;
}

template<class T>
void FileHandler<T>::setNetworkPageSize(long networkPageSize) {
    FileHandler::networkPageSize = networkPageSize;
}
