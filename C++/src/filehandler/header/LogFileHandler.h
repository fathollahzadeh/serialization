//
// Created by saeed on 12/19/19.
//

#ifndef TWITTER_LOGFILEHANDLER_H
#define TWITTER_LOGFILEHANDLER_H

#include <iostream>
#include <fstream>
using namespace std;

class LogFileHandler {
    string fileName;

    ofstream logFile;
public:
    LogFileHandler();

    virtual ~LogFileHandler();

    LogFileHandler(string fileName);

    void addLog(string log);
    //language#method#seq#datatype#iotime#totaltime
    void addLog(int serializationType, bool seq,string datatype, double iotime, double totaltime);

    void flushLogFile();

};


#endif //TWITTER_LOGFILEHANDLER_H
