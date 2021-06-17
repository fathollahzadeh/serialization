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

	void
	addLog(bool read, int serializationType, bool seq, string datatype, double iotime, double totaltime, bool taskset);

	void flushLogFile();

};


#endif //TWITTER_LOGFILEHANDLER_H
