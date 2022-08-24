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

bsoncxx::document::value URLEntity::serializeBSON() {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;
    using bsoncxx::builder::stream::array;

    auto arrindices = array{};
    for (int i = 0; i < this->indices.size(); ++i) {
        arrindices << this->indices[i];
    }
    document doc=document{};
    doc<<"display_url"<<this->displayURL<<
    "expanded_url"<<this->expandedURL<<
    "url"<<this->url<<
    "indices"<<arrindices;

    return doc<<finalize;
}

URLEntity *URLEntity::deserializeBSON(bsoncxx::document::view doc) {

    bsoncxx::document::element element = doc["display_url"];
    this->displayURL=bsoncxx::string::to_string(element.get_utf8().value);

    element = doc["expanded_url"];
    this->expandedURL=bsoncxx::string::to_string(element.get_utf8().value);

    element = doc["url"];
    this->url=bsoncxx::string::to_string(element.get_utf8().value);

    element = doc["indices"];
    if (element && element.type()==bsoncxx::type::k_array) {
        for (auto ele : element.get_array().value) {
            this->indices.push_back(ele.get_int32());
        }
    }

    return this;
}
