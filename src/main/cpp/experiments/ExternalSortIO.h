#ifndef CPP_EXTERNALSORTIO_H
#define CPP_EXTERNALSORTIO_H

#include <iostream>
#include <queue>
#include <cmath>
#include "ObjectWriter.h"
#include "ObjectReader.h"

using namespace std;

template<class T>
class ExternalSortIO {

private:
    string inDataPath;
    string outDataPath;
    string method;
    int chunkSize;

public:
    ExternalSortIO();

    ExternalSortIO(const string &inDataPath, const string &outDataPath, const string &method, int chunkSize);

    virtual ~ExternalSortIO();

    void runExternalSort();
};

template<class T>
ExternalSortIO<T>::ExternalSortIO() {}

template<class T>
ExternalSortIO<T>::~ExternalSortIO() {}

template<class T>
void ExternalSortIO<T>::runExternalSort() {

    ObjectReader *reader = new ObjectReader(inDataPath, method);
    int fileCount = (int) ceil((double) reader->getRlen() / chunkSize);
    long *readFileObject = new long[fileCount];

    for (int i = 0; i < fileCount & i * chunkSize < reader->getRlen(); i++) {
        vector<char *> listBytes;
        vector<int> listBytesLength;
        int *pIndex = new int[chunkSize];
        int *oindex = new int[chunkSize];
        int *oLength = new int[chunkSize];
        int listSize = reader->readIO((long) i * chunkSize, chunkSize, listBytes, listBytesLength, pIndex, oindex, oLength);
        ObjectWriter *writer = new ObjectWriter(outDataPath + "/" + method + "CPP-sorted-" + to_string(i) + ".bin",
                                                method, listSize);
        for (int j = 0; j < listBytes.size(); ++j) {
            writer->writeBufferToFile(listBytes[j], listBytesLength[j]);
            delete[] listBytes[j];
        }
        writer->flush(pIndex, oindex, oLength);
        delete writer;
        delete[] pIndex;
        delete[] oindex;
        delete[] oLength;
    }

    // open all of data files and keep them open to read partially.
    ObjectWriter *writer = new ObjectWriter(outDataPath + "/" + method + "CPP-sorted.bin", method, reader->getRlen());
    for (int i = 0; i < fileCount; ++i) {
        string sortedFileName = outDataPath + "/" + method + "CPP-sorted-" + to_string(i) + ".bin";
        ObjectReader *tmpReader = new ObjectReader(sortedFileName, method);
        vector<char *> listBytes;
        vector<int> listBytesLength;
        int *pIndex = new int[tmpReader->getRlen()];
        int *oIndex = new int[tmpReader->getRlen()];
        int *oLength = new int[tmpReader->getRlen()];
        tmpReader->readIO(0, tmpReader->getRlen(), listBytes, listBytesLength, pIndex, oIndex, oLength);
        for (int j = 0; j < listBytes.size(); ++j) {
            writer->writeBufferToFile(listBytes[j], listBytesLength[j]);
            delete[] listBytes[j];
        }
        delete[] pIndex;
        delete[] oIndex;
        delete[] oLength;
        delete tmpReader;
    }
    writer->flush();
    delete writer;
    delete reader;
    delete[] readFileObject;
}

template<class T>
ExternalSortIO<T>::ExternalSortIO(const string &inDataPath, const string &outDataPath, const string &method,
                                  int chunkSize)
        :inDataPath(inDataPath), outDataPath(outDataPath), method(method), chunkSize(chunkSize) {}

#endif //CPP_EXTERNALSORTIO_H
