#include <iostream>
#include "ObjectWriter.h"
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"

using namespace std;

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string method = argv[2];
    string seqRand = argv[3];
    int nrow = atoi(argv[4]);

    ObjectReader *reader = new ObjectReader(inDataPath,method);
    if (strcasecmp(seqRand.c_str(), "sequential") == 0) {
        reader->readIO(0, nrow);
    }
    else{
        string randomDataPath = argv[5];
        ifstream infile;
        infile.open(randomDataPath);
        if (!infile.is_open()) {
            throw runtime_error("cannot find random list file!!.");
        }

        string line;
        while (getline(infile, line)) {
            int id = atoi(line.c_str());
            reader->readIO(id);
        }
    }
}



