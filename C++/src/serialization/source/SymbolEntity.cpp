
#include "SymbolEntity.h"

using namespace std;

//Default constructor:
SymbolEntity::SymbolEntity() {
}

//Constructor with arguments:
SymbolEntity::SymbolEntity(vector<int> indices, string text) {
    this->indices = indices;
    this->text = text;
}

//C++: Explicit call needed for printing content:

string SymbolEntity::toJSON() {
    string stringS = "{";

    stringS += "\"indices\":[";
    if (indices.size() > 0) {
        for (int j = 0; j < indices.size() - 1; ++j) {
            stringS += itos(indices[j]) + ",";
        }

        stringS += itos(indices[indices.size() - 1]);
    }
    stringS += "],";
    getStringKeyValue("Text", this->text) + "}";
    return stringS;
}

//Hand Coded C++ serialization:
char *SymbolEntity::serializeHandcoded(char *buffer, int &objectSize) {
    //Serialize the object.
    //Copy Integers:
    buffer = copyInt(buffer, this->indices.size(), objectSize);
    for (int i = 0; i < this->indices.size(); ++i) {
        buffer = copyInt(buffer, this->indices[i], objectSize);
    }
    //Copy Strings:
    buffer = copyString(buffer, this->text, objectSize);

    return buffer;
}


SymbolEntity * SymbolEntity::deserializeHandcoded(char *buffer, int &bytesRead) {
    int numOfIndices = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfIndices);
    for (int i = 0; i < numOfIndices; ++i) {
        this->indices.push_back(parseInt(buffer + bytesRead));
        bytesRead += sizeof(int);
    }
    //Parse Strings:
    parseString(buffer + bytesRead, this->text);
    bytesRead += (sizeof(int) + this->text.length());
    return this;
}

SymbolEntity::~SymbolEntity() {

    //free memory:
    indices.shrink_to_fit();
}
