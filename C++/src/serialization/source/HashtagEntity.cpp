
#include "HashtagEntity.h"

using namespace std;

//Default constructor:
HashtagEntity::HashtagEntity() {
}

//Constructor with arguments:
HashtagEntity::HashtagEntity(vector<int> indices, string text) {
    this->indices = indices;
    this->text = text;
}


//C++: Explicit call needed for printing content:
string HashtagEntity::toJSON() {
    string stringS = "{\"indices\":[";
    for (int i = 0; i < indices.size() - 1; i++) {
        stringS +=itos( indices[i] )+ ",";
    }
    if (indices.size() > 0) {
        stringS += itos(indices[indices.size() - 1]);
    }
    stringS += "],";

    getStringKeyValue("Text", this->text) + "}";
    return stringS;
}

//Hand Coded C++ serialization:
char *HashtagEntity::serializeHandcoded(char *buffer, int &objectSize) {
    //Serialize the object.
    //Copy Integers:
    buffer = copyInt(buffer, this->indices.size(), objectSize);
    for (int i = 0; i <this->indices.size() ; ++i) {
        buffer = copyInt(buffer, this->indices[i], objectSize);
    }
    //Copy Strings:
    buffer = copyString(buffer, this->text, objectSize);
    return buffer;
}


HashtagEntity* HashtagEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

    int numOfIndices = parseInt(buffer+bytesRead);
    bytesRead += sizeof(numOfIndices);

    for (int i = 0; i <numOfIndices ; ++i) {
        this->indices.push_back(parseInt(buffer+bytesRead));
        bytesRead+= sizeof(int);
    }
    //Parse Strings:
    parseString(buffer + bytesRead, this->text);
    bytesRead += (sizeof(int) + this->text.length());
    return this;
}

HashtagEntity::~HashtagEntity() {
    //free memory
    indices.shrink_to_fit();
}

bsoncxx::document::value HashtagEntity::serializeBSON() {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;
    using bsoncxx::builder::stream::array;
    using bsoncxx::builder::stream::open_array;
    using bsoncxx::builder::stream::close_array;

    document doc=document{};
    doc<<"text"<< this->text;

    auto arrindices = array{};
    for (int i = 0; i < this->indices.size(); ++i) {
        arrindices<< this->indices[i];
    }
    doc<<"indices"<<arrindices;
    return doc<<finalize;
}

HashtagEntity *HashtagEntity::deserializeBSON(bsoncxx::document::view doc) {
    bsoncxx::document::element element = doc["text"];
    this->text =bsoncxx::string::to_string(element.get_utf8().value);

    element = doc["indices"];
    if (element && element.type()==bsoncxx::type::k_array) {
        for (auto ele : element.get_array().value) {
            this->indices.push_back(ele.get_int32());
        }
    }

    return this;
}
