#include <iostream>
#include "ObjectWriter.h"
#include "DataReader.h"

using namespace std;

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string outDataPath = argv[2];
    int nrow = atoi(argv[3]);

    DataReader dataReader;
    ObjectWriter *writer = new ObjectWriter(outDataPath, "HandCoded", nrow);
    ifstream infile;
    infile.open(inDataPath);
    string line;
    int l=0;
    while (getline(infile, line)) {
        Document d;
        d.Parse(line.c_str());
        TweetStatus *tweet = dataReader.generateTweetObject(d);
        writer->writeObjectToFile(tweet);

        //Free memory:
        delete tweet;

        if (++l>=nrow)
            break;
    }
    writer->flush();
    infile.close();
    infile.clear();

    delete writer;
    return 0;
}

