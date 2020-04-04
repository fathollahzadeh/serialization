
#include "ExtendedEntities.h"


using namespace std;

//Default constructor:
ExtendedEntities::ExtendedEntities() {
}

//Constructor with arguments:
ExtendedEntities::ExtendedEntities(vector<MediaEntity *> media) {
    this->media = media;
}

//C++: Explicit call needed for printing content:
string ExtendedEntities::toJSON() {
    string stringS = "\"Media\":[";
    //All media:
    for (int i = 0; i < media.size() - 1; i++) {
        stringS += media[i]->toJSON() + ",";
    }
    stringS += media[media.size() - 1]->toJSON();
    stringS += "]";

    return stringS;
}

//Hand Coded C++ serialization:
char *ExtendedEntities::serializeHandcoded(char *buffer, int &objectSize) {
    //Serialize the object.
    //Copy encapsulated objects:
    int numOfMedia = this->media.size();
    buffer = copyInt(buffer, numOfMedia, objectSize);

    for (int i = 0; i < this->media.size(); i++) {
        buffer =this->media.at(i)->serializeHandcoded(buffer, objectSize);
    }
    return buffer;
}


ExtendedEntities *ExtendedEntities::deserializeHandcoded(char *buffer, int &bytesRead) {
    //Encapsulated objects:
    int numOfMedia = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfMedia);

    for (int i = 0; i < numOfMedia; i++) {
        this->media.push_back(new MediaEntity());
        this->media.at(i)->deserializeHandcoded(buffer, bytesRead);
    }
    return this;
}

ExtendedEntities::~ExtendedEntities() {
    //free memory
    for (int i = 0; i < media.size(); ++i) {
        delete media.at(i);
    }
    media.shrink_to_fit();
}

bsoncxx::document::value ExtendedEntities::serializeBSON() {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;
    using bsoncxx::builder::stream::array;

    auto arrmedia = array{};
    for (int i = 0; i < this->media.size(); ++i) {
        arrmedia<< bsoncxx::types::b_document{this->media[i]->serializeBSON().view()};
    }
    document doc=document{};
    doc<<"media"<<arrmedia;

    return doc<<finalize;
}

ExtendedEntities *ExtendedEntities::deserializeBSON(bsoncxx::document::view doc) {
    bsoncxx::document::element element = doc["media"];
    if (element && element.type()==bsoncxx::type::k_array) {
        for (auto ele : element.get_array().value) {
            MediaEntity * mediaEntity=new MediaEntity();
            mediaEntity->deserializeBSON(ele.get_document().view());
            this->media.push_back(mediaEntity);
        }
    }
    return this;
}
