#ifndef CPP_EXTERNALSORT_H
#define CPP_EXTERNALSORT_H

#include <iostream>
#include <queue>
#include <cmath>
#include "ObjectWriter.h"
#include "ObjectReader.h"

using namespace std;

//ObjectFileIndex
template<class T>
struct ObjectFileIndex {
    T *myObject;
    int fileIndex;

    virtual ~ObjectFileIndex() { }
};

//Ascending Sorter:
template<class T>
struct UniversalPointerComparatorAscending {
    bool operator()(T *a, T *b) {
        return *a < *b;
    }
};

//Descending Sorter:
template<class T>
struct UniversalPointerComparatorDescending {
    bool operator()(ObjectFileIndex<T> *a, ObjectFileIndex<T> *b) {
        if (*a->myObject < *b->myObject)
            return false;
        return true;
    }
};


template<class T>
class ExternalSort {

private:
    string inDataPath;
    string outDataPath;
    string method;
    int chunkSize;
    int methodID;

public:
    ExternalSort();

    ExternalSort(const string &inDataPath, const string &outDataPath, const string &method, int chunkSize);

    virtual ~ExternalSort();

    void runExternalSort();
};

template<class T>
ExternalSort<T>::ExternalSort() {}

template<class T>
ExternalSort<T>::~ExternalSort() {}

template<class T>
void ExternalSort<T>::runExternalSort() {

    priority_queue<ObjectFileIndex<T> *, vector < ObjectFileIndex<T> *>, UniversalPointerComparatorDescending<T> > queue;
    ObjectReader *reader = new ObjectReader(inDataPath, method);
    int fileCount = (int) ceil((double) reader->getRlen() / chunkSize);
    long *pageObjectCounter = new long[fileCount];
    long *readFileObject = new long[fileCount];
    methodID = reader->getMethod();

    int *pageCounter = new int[fileCount];
    // set all positions to the beginning of files - zero.
    for (int i = 0; i < fileCount; i++) {
        pageCounter[i] = 0;
    }

    for (int i = 0; i < fileCount && i * chunkSize < reader->getRlen(); i++) {
        T **list = new T *[chunkSize];
        int listSize = reader->readObjects((long) i * chunkSize, chunkSize, list);
        sort(list, list + listSize, UniversalPointerComparatorAscending<T>());

        ObjectWriter *writer = new ObjectWriter(outDataPath + "/" + method + "CPP-sorted-" + to_string(i) + ".bin",
                                                method, listSize);
        for (int j = 0; j < listSize; ++j) {
            writer->writeObjectToFile(list[j]);
        }
        writer->flush();
        delete writer;
        //free memory:
        for (int k = 0; k < listSize; ++k) {
            if (reader->getMethod() != INPLACE) {
                delete list[k];
            } else {
                char *tbuffer = (char *) list[k];
                delete[] tbuffer;
            }
        }
        delete[] list;
    }

    // open all of data files and keep them open to read partially.
    vector<ObjectReader *> readerArray;
    for (int i = 0; i < fileCount; ++i) {
        string sortedFileName = outDataPath + "/" + method + "CPP-sorted-" + to_string(i) + ".bin";
        ObjectReader *tmpReader = new ObjectReader(sortedFileName, method);
        readerArray.push_back(tmpReader);
    }

    // reading objects from the first pages and adding them to a priority queue
    for (int i = 0; i < fileCount; i++) {
        int n = readerArray[i]->getObjectInEachPage()[0];
        T **list = new T *[n];
        readerArray[i]->readObjects(0, n, list);
        pageObjectCounter[i] = n;
        readFileObject[i] = n;
        for (int j = 0; j < n; ++j) {
            ObjectFileIndex<T> *objectFileIndex = new ObjectFileIndex<T>();
            objectFileIndex->myObject = list[j];
            objectFileIndex->fileIndex = i;
            queue.push(objectFileIndex);
        }
        delete[] list;
    }
    ObjectWriter *writer = new ObjectWriter(outDataPath + "/" + method + "CPP-sorted.bin", method, reader->getRlen());

    while (!queue.empty()) {
        ObjectFileIndex<T> *tmpObjectFileIndex = queue.top();
        queue.pop();
        int fileNumber = tmpObjectFileIndex->fileIndex;

        // reduce the number of objects read from that file.
        pageObjectCounter[fileNumber] = pageObjectCounter[fileNumber] - 1;

        // If needed load more objects from files.
        // if zero load the next page from file and add objects.
        if (pageObjectCounter[fileNumber] == 0 &&
            pageCounter[fileNumber] < readerArray[fileNumber]->getObjectInEachPage().size() - 1) {

            // add page counter
            pageCounter[fileNumber] = pageCounter[fileNumber] + 1;
            pageObjectCounter[fileNumber] = readerArray.at(fileNumber)->getObjectInEachPage()[pageCounter[fileNumber]];

            T **list = new T *[(int) pageObjectCounter[fileNumber]];
            int listSize = readerArray.at(fileNumber)->readObjects(readFileObject[fileNumber],
                                                                   (int) pageObjectCounter[fileNumber], list);
            readFileObject[fileNumber] += listSize;

            for (int j = 0; j < listSize; ++j) {
                ObjectFileIndex<T> *objectFileIndex = new ObjectFileIndex<T>();
                objectFileIndex->myObject = list[j];
                objectFileIndex->fileIndex = fileNumber;
                queue.push(objectFileIndex);
            }
            delete[] list;
        }
        writer->writeObjectToFile(tmpObjectFileIndex->myObject);

        if (methodID != INPLACE) {
            delete tmpObjectFileIndex->myObject;
        } else {
            char *tbuffer = (char *) tmpObjectFileIndex->myObject;
            delete[] tbuffer;
        }
        delete tmpObjectFileIndex;
    }
    writer->flush();
    delete writer;
    delete reader;
    delete[] pageObjectCounter;
    delete[] readFileObject;
    delete[] pageCounter;

    for (int i = 0; i < fileCount; ++i) {
       delete readerArray.at(i);
    }
}

template<class T>
ExternalSort<T>::ExternalSort(const string &inDataPath, const string &outDataPath, const string &method, int chunkSize)
        :inDataPath(inDataPath), outDataPath(outDataPath), method(method), chunkSize(chunkSize) {}

#endif //CPP_EXTERNALSORT_H
