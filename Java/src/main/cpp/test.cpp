#include <iostream>
#include "ObjectReader.h"
#include "ObjectWriter.h"
#include "DataReader.h"

using namespace std;

int main(int argc, char *argv[]) {

    DataReader dataReader;
    ObjectWriter *writer = new ObjectWriter("inplace", 5, PAGESIZE);
    ifstream infile;
    string inputFileName = "/home/saeed/Documents/Github/serialization/Experiments/data/tweets.txt";

    infile.open(inputFileName);
    int l = 0;
    string line;
    while (getline(infile, line)) {
        Document d;
        d.Parse(line.c_str());
        TweetStatus *tweet = dataReader.generateTweetObject(d);

        writer->serializeObject(tweet);

        l++;
        if (l>5)
            break;

        //Free memory:
        delete tweet;
    }
    infile.close();
    infile.clear();

    delete writer;

    return 0;
}
