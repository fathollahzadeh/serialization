
#include "UserMentionEntity.h"

using namespace std;

//Default constructor:
UserMentionEntity::UserMentionEntity() {
}

//Constructor with arguments:
UserMentionEntity::UserMentionEntity(long id, string idStr, vector<int> indices, string name, string screenName) {
    this->id = id;
    this->idStr = idStr;
    this->indices = indices;
    this->name = name;
    this->screenName = screenName;
}
//Hand Coded C++ serialization:
char *UserMentionEntity::serializeHandcoded(char *buffer, int &objectSize) {
    //Serialize the object.
    //Copy Long Elements:
    buffer = copyLong(buffer, this->id, objectSize);
    //Copy Integers:
    buffer = copyInt(buffer, this->indices.size(), objectSize);
    for (int i = 0; i < this->indices.size(); ++i) {
        buffer = copyInt(buffer, this->indices[i], objectSize);
    }

    //Copy Strings:
    buffer = copyString(buffer, this->idStr, objectSize);

    buffer = copyString(buffer, this->name, objectSize);
    buffer = copyString(buffer, this->screenName, objectSize);

    return buffer;
}


UserMentionEntity * UserMentionEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

    this->id = parseLong(buffer + bytesRead);
    bytesRead += sizeof(this->id);

    int numOfIndices = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfIndices);
    for (int i = 0; i < numOfIndices; ++i) {
        this->indices.push_back(parseInt(buffer + bytesRead));
        bytesRead += sizeof(int);
    }

    //Parse Strings:
    parseString(buffer + bytesRead, this->idStr);
    bytesRead += (sizeof(int) + this->idStr.length());

    parseString(buffer + bytesRead, this->name);
    bytesRead += (sizeof(int) + this->name.length());

    parseString(buffer + bytesRead, this->screenName);
    bytesRead += (sizeof(int) + this->screenName.length());

    return this;
}


//C++: Explicit call needed for printing content:
string UserMentionEntity::toJSON() {
    string stringS = "{" +
                     getIntKeyValue("Id", this->id) + " , " +
                     getStringKeyValue("IdStr", this->idStr) + " , ";
    stringS += "\"indices\":[";
    if (indices.size() > 0) {
        for (int j = 0; j < indices.size() - 1; ++j) {
            stringS += itos(indices[j]) + ",";
        }
        stringS += itos(indices[indices.size() - 1]);
    }
    stringS += "]," +
               getStringKeyValue("Name", this->name) + " , " +
               getStringKeyValue("ScreenName", this->screenName) + "}";
    return stringS;
}

UserMentionEntity::~UserMentionEntity() {
    //free memory:
    indices.shrink_to_fit();
}

bsoncxx::document::value UserMentionEntity::serializeBSON() {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;
    using bsoncxx::builder::stream::array;

    auto arrindices = array{};
    for (int i = 0; i < this->indices.size(); ++i) {
        arrindices << this->indices[i];
    }
    document doc=document{};
    doc<<"id"<<this->id<<
    "id_str"<<this->idStr<<
    "name"<<this->name<<
    "screen_name"<<this->screenName<<
    "indices"<<arrindices;

    return doc<<finalize;
}
