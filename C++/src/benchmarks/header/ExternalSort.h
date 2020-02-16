//
// Created by saeed on 12/13/19.
//

#ifndef TWITTER_EXTERNALSORT_H
#define TWITTER_EXTERNALSORT_H

#include <iostream>
#include <chrono>
#include <boost/serialization/vector.hpp>
#include <FileHandler.h>
#include <FileHandler.cpp>
#include <queue>
#include <LogFileHandler.h>

using namespace std;

//ObjectFileIndex
template<class T>
struct ObjectFileIndex {
    T *myObject;
    int fileIndex;

    virtual ~ObjectFileIndex() {
        delete myObject;
    }
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
    string fileName;
    int numberOfFiles;
    long numberOfObjectsInEachFiles;
    int serializationType;

    void writeToFiles(vector<T *> list, string filename);

    LogFileHandler *logFileHandler;

    // define variables for calculate bench time:
    double ioTime = 0;

public:
    ExternalSort();

    virtual ~ExternalSort();

    ExternalSort(string fileName, int numberOfFiles, int serializationType,int round);

    void runTheExternalSort();


};

template<class T>
ExternalSort<T>::ExternalSort() {

}

template<class T>
ExternalSort<T>::~ExternalSort() {
    delete logFileHandler;
}

template<class T>
void ExternalSort<T>::runTheExternalSort() {

    cout << "Start Reading part of the file into RAM" << endl;

    FileHandler<T> *fileHandler = new FileHandler<T>(fileName, serializationType);
    fileHandler->prepareToRead();

    //get number of objects in file:
    long totalObjectsCount = fileHandler->getNumberOfObjects();


    double sortTime = 0;

    // start of time calculation
    auto startTime = chrono::steady_clock::now();

    //define start position of objects in each file:
    long startIndexInEachFile = 0;
    numberOfObjectsInEachFiles = totalObjectsCount / numberOfFiles;
    for (int i = 0; i < numberOfFiles; i++) {
        cout << "Reading for file number " << i << endl;

        startIndexInEachFile = i * numberOfObjectsInEachFiles;

        // define a vector to store read objects from each file:
        vector<T *> m_list_read_from_file;

        // read objects from file:
        fileHandler->getObjectsFromFile(startIndexInEachFile, numberOfObjectsInEachFiles, m_list_read_from_file);
        // Sort the data
        auto tmpTime = chrono::steady_clock::now();

        //Sort:
        sort(m_list_read_from_file.begin(), m_list_read_from_file.end(), UniversalPointerComparatorAscending<T>());

        // Sort Time Calculation
        sortTime += chrono::duration<double>(chrono::steady_clock::now() - tmpTime).count();

        // write the sorted list back to files.
        string tmpStoreFileName = "bin/tmp/sorted-" + to_string(i) + "-" + to_string(serializationType);
        writeToFiles(m_list_read_from_file, tmpStoreFileName);

        //free memory:
        for (long i = 0; i < m_list_read_from_file.size(); ++i) {
            if (serializationType!=2){
                delete m_list_read_from_file.at(i);
            } else{
                char * tbuffer=(char *)m_list_read_from_file.at(i);
                delete[] tbuffer;
            }
        }

        m_list_read_from_file.shrink_to_fit();
    }

    cout << "First stage done! " << endl;
    // ///////////////////////////////////////////////////
    //
    // External Sort - Second stage //
    //
    // //////////////////////////////////////////////////
    cout << "Second Stage ... " << endl;

    // open all of data files and keep them open to read partially.
    vector<FileHandler<T> *> fileArray;
    for (int i = 0; i < numberOfFiles; ++i) {
        string sortedFileName = "bin/tmp/sorted-" + to_string(i) + "-" + to_string(serializationType);
        FileHandler<T> *tmpFileHandler = new FileHandler<T>(sortedFileName, serializationType);
        tmpFileHandler->prepareToRead();
        fileArray.push_back(tmpFileHandler);
    }

    int *pageCounter = new int[numberOfFiles];
    // set all positions to the beginning of files - zero.
    for (int i = 0; i < numberOfFiles; i++) {
        pageCounter[i] = 0;
    }

    long pageObjectCounter[numberOfFiles];

    long readFileObject[numberOfFiles];

    priority_queue<ObjectFileIndex<T> *, vector<ObjectFileIndex<T> *>, UniversalPointerComparatorDescending<T> > queue;

    // reading objects from the first pages and adding them to a priority queue
    for (int i = 0; i < numberOfFiles; i++) {

        //get number of objects in the first page
        long n = fileArray.at(i)->getEachPageObjectCount()[0];

        pageObjectCounter[i] = n;

        readFileObject[i] = n;

        vector<T *> m_list_read_from_file;
        fileArray.at(i)->getObjectsFromFile(0, n, m_list_read_from_file);

        for (int j = 0; j < m_list_read_from_file.size(); ++j) {
            ObjectFileIndex<T> *objectFileIndex = new ObjectFileIndex<T>();
            objectFileIndex->myObject = m_list_read_from_file.at(j);
            objectFileIndex->fileIndex = i;
            queue.push(objectFileIndex);
        }

    }// End of loop over files

    cout << "First page reading is done! " << endl;

    vector<T *> dataToWrite;

    // reading next pages
    // ###################################################################
    // open final output file.
    FileHandler<T> *objectFileOutput = new FileHandler<T>("bin/tmp/finalSortedFile-" + to_string(serializationType),
                                                          serializationType);
    objectFileOutput->prepareToWrite();

    while (!queue.empty()) {

        ObjectFileIndex<T> *tmpObjectFileIndex = queue.top();
        queue.pop();
        int fileNumber = tmpObjectFileIndex->fileIndex;

        // reduce the number of objects read from that file.
        pageObjectCounter[fileNumber] = pageObjectCounter[fileNumber] - 1;

        // If needed load more objects from files.
        // if zero load the next page from file and add objects.
        if (pageObjectCounter[fileNumber] == 0 &&
            pageCounter[fileNumber] < fileArray.at(fileNumber)->getEachPageObjectCount().size() - 1) {

            // add page counter
            pageCounter[fileNumber] = pageCounter[fileNumber] + 1;

            pageObjectCounter[fileNumber] = fileArray.at(fileNumber)->getEachPageObjectCount()[pageCounter[fileNumber]];

            vector<T *> m_list_read_from_file;

            fileArray.at(fileNumber)->getObjectsFromFile(readFileObject[fileNumber], pageObjectCounter[fileNumber],
                                                         m_list_read_from_file);

            readFileObject[fileNumber] += m_list_read_from_file.size();

            for (int j = 0; j < m_list_read_from_file.size(); ++j) {
                ObjectFileIndex<T> *objectFileIndex = new ObjectFileIndex<T>();
                objectFileIndex->myObject = m_list_read_from_file.at(j);
                objectFileIndex->fileIndex = fileNumber;
                queue.push(objectFileIndex);
            }
        }
        dataToWrite.push_back(tmpObjectFileIndex->myObject);

        // Write only of we collected more than 10000 objects
        if (dataToWrite.size() > 10000) {

            for (int i = 0; i < dataToWrite.size(); ++i) {
                //Serialize the TweetStatus object and then write to file:
                objectFileOutput->appendObjectToFile(dataToWrite.at(i));
                if (serializationType!=2){
                    delete dataToWrite.at(i);
                } else{
                    char * tbuffer=(char *)dataToWrite.at(i);
                    delete[] tbuffer;
                }
            }
            //dataToWrite.shrink_to_fit();
            dataToWrite.clear();
        }
    }

    for (int i = 0; i < dataToWrite.size(); ++i) {
        //Serialize the TweetStatus object and then write to file:
        objectFileOutput->appendObjectToFile(dataToWrite.at(i));
        if (serializationType!=2){
            delete dataToWrite.at(i);
        } else{
            char * tbuffer=(char *)dataToWrite.at(i);
            delete[] tbuffer;
        }
    }
    dataToWrite.shrink_to_fit();

    objectFileOutput->appendObjectToFileFlush();

    cout << "Done!" << endl;

    // Close object files.
    for (int k = 0; k < numberOfFiles; ++k) {
        fileArray.at(k)->getObjectsFromFileFlush();
        this->ioTime += fileArray.at(k)->getIoTime();
        delete fileArray.at(k);
    }
    // end of time calculation
    auto endTime = chrono::steady_clock::now();
    double elapsedSeconds = chrono::duration<double>(endTime - startTime).count();

    // add times to the log file
    this->logFileHandler->addLog(serializationType, true, "TweetStatus", ioTime, elapsedSeconds);
    this->logFileHandler->flushLogFile();
}

template<class T>
void ExternalSort<T>::writeToFiles(vector<T *> list, string filename) {

    // Define file handler for each serialization type:
    FileHandler<T> *fileHandler = new FileHandler<T>(filename, serializationType);
    fileHandler->prepareToWrite();
    for (int i = 0; i < list.size(); ++i) {
        //Serialize the TweetStatus object and then write to file:
        fileHandler->appendObjectToFile(list.at(i));
    }
    fileHandler->appendObjectToFileFlush();
    this->ioTime+=fileHandler->getIoTime();
}

template<class T>
ExternalSort<T>::ExternalSort(string fileName, int numberOfFiles, int serializationType,int round){
    this->fileName=fileName;
    this->numberOfFiles=numberOfFiles;
    this->serializationType=serializationType;
    this->logFileHandler=new LogFileHandler("bin/benchmark/externalsort/result_cpp_externalsort_"+to_string(round)+".txt");
}

#endif //TWITTER_EXTERNALSORT_H
