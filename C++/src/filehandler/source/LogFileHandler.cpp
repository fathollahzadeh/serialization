//
// Created by saeed on 12/19/19.
//

#include "LogFileHandler.h"

LogFileHandler::LogFileHandler() {}

LogFileHandler::~LogFileHandler() {

}

LogFileHandler::LogFileHandler(string fileName) {
    logFile.open (fileName, ios::out | ios::app );
}

void LogFileHandler::addLog(string log) {

    logFile << log<<"\n";
}

void LogFileHandler::addLog(bool read,int serializationType, bool seq, string datatype, double iotime, double totaltime, bool taskset) {

    if (read) {
        logFile << "[ReadTimeCPP]#";
    } else
        logFile << "[WriteTimeCPP]#";

    if (taskset){
        logFile<<"true#";
    } else
        logFile<<"false#";

    string method="";
    switch (serializationType){
        case 1:
            method="C++ HandCoded";
            break;
        case 2:
            method="C++ inPlace";
            break;
        case 3:
            method="C++ Boost";
            break;
        case 4:
            method="C++ ProtoBuf";
            break;
        case 5:
            method="C++ Bson";
            break;
        case 6:
            method="C++ FlatBuffers";
            break;

    }
    string seqString="true";
    if (!seq)
        seqString="false";

    logFile<<method<<"#";
    logFile<<seqString<<"#";
    logFile<<datatype<<"#";
    logFile<<iotime<<"#";
    logFile<<totaltime<<"\n";
}

void LogFileHandler::flushLogFile() {
    logFile.close();
}
