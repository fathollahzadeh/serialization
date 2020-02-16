#ifndef ROOTDATA_H
#define ROOTDATA_H

#include <iostream>
#include <chrono>
#include <regex>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>

using namespace std;

// Declaration of the "base" class.
class RootData {
private:
    bool deleted;
public:

    //char * copyBuffer(char * buffer, char * copyThis, int size);
    char *copyInt(char *buffer, int copyThis, int &objectSize);

    char *copyLong(char *buffer, long copyThis, int &objectSize);

    char *copyDouble(char *buffer, double copyThis, int &objectSize);

    char *copyBool(char *buffer, bool copyThis, int &objectSize);

    char *copyString(char *buffer, string copyThis, int &objectSize);

    //string parseString (char * buffer);
    int parseInt(char *buffer);

    long parseLong(char *buffer);

    double parseDouble(char *buffer);

    bool parseBool(char *buffer);

    //int to string
    static string itos(int element);

    //double to string
    static string dtos(double element);

    //long to string
    static string ltos(long element);

    //boolean to string
    static string btos(bool element);


    //Efficient parseString:
    void parseString(char *buffer, string &s);

    //Unimplemented Functions:
    long serializeInPlace(char *fileStart);

    void freePointedObjects();

    boost::archive::text_iarchive *getArchive();

    stringstream *getStream();

    //Get JSON Key-Value:
    string getStringKeyValue(string key, string value);

    string getIntKeyValue(string key, int value);

    string getDoubleKeyValue(string key, double value);

    string getLongKeyValue(string key, long value);

    string getBoolKeyValue(string key, bool value);

    bool isDeleted() const;

    void setDeleted(bool deleted);


    //InPlace serialization:
    char * copyInPlaceInt(char * buffer, int copyThis);
    char * copyInPlaceLong(char * buffer, long copyThis);
    char * copyInPlaceDouble(char * buffer, double copyThis);

    int parseInPlaceInt(char * buffer);
    long parseInPlaceLong(char * buffer);
    double parseInPlaceDouble(char * buffer);



};


#endif
