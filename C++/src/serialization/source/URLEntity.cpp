
#include "URLEntity.h"

using namespace std;


//Copy constructor:
URLEntity::URLEntity(const URLEntity &obj) {
    throw invalid_argument("URLEntity: Not copy constructible.");
}


URLEntity::~URLEntity() {
}


//Default constructor:
URLEntity::URLEntity() {
}

//Constructor with arguments:
URLEntity::URLEntity(vector<int> indices, string displayURL, string expandedURL, string url) {
    this->indices = indices;
    this->displayURL = displayURL;
    this->expandedURL = expandedURL;
    this->url = url;
}


//C++: Explicit call needed for printing content:

string URLEntity::toJSON() {
    string stringS = "{";
    stringS += "\"indices\":[";
    if (indices.size() > 0) {
        for (int j = 0; j < indices.size() - 1; ++j) {
            stringS += itos(indices[j]) + ",";
        }
        stringS += itos(indices[indices.size() - 1]);
    }
    stringS += "]," +
               getStringKeyValue("DisplayURL", this->displayURL) + " , " +
               getStringKeyValue("ExpandedURL", this->expandedURL) + " , " +
               getStringKeyValue("Url", this->url) + "}";
    return stringS;
}

//Hand Coded C++ serialization:
char *URLEntity::serializeHandcoded(char *buffer, int &objectSize) {
    //Serialize the object.
    //Copy Integers:
    buffer = copyInt(buffer, this->indices.size(), objectSize);
    for (int i = 0; i < this->indices.size(); ++i) {
        buffer = copyInt(buffer, this->indices[i], objectSize);
    }
    //Copy Strings:
    buffer = copyString(buffer, this->displayURL, objectSize);
    buffer = copyString(buffer, this->expandedURL, objectSize);
    buffer = copyString(buffer, this->url, objectSize);

    return buffer;
}


URLEntity *URLEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

    int numOfIndices = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfIndices);
    for (int i = 0; i < numOfIndices; ++i) {
        this->indices.push_back(parseInt(buffer + bytesRead));
        bytesRead += sizeof(int);
    }
    //Parse Strings:
    parseString(buffer + bytesRead, this->displayURL);
    bytesRead += (sizeof(int) + this->displayURL.length());
    parseString(buffer + bytesRead, this->expandedURL);
    bytesRead += (sizeof(int) + this->expandedURL.length());
    parseString(buffer + bytesRead, this->url);
    bytesRead += (sizeof(int) + this->url.length());

    return this;
}
