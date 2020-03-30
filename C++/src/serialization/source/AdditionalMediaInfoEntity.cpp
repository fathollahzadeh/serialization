//
// Created by saeed on 11/9/19.
//

#include "AdditionalMediaInfoEntity.h"

AdditionalMediaInfoEntity::AdditionalMediaInfoEntity() {}

AdditionalMediaInfoEntity::~AdditionalMediaInfoEntity() {}

AdditionalMediaInfoEntity::AdditionalMediaInfoEntity(const string &title, const string &description,
                                                         bool embeddable, bool monetizable) : title(title),
                                                                                              description(description),
                                                                                              embeddable(embeddable),
                                                                                              monetizable(
                                                                                                      monetizable) {}


string AdditionalMediaInfoEntity::toJSON() {
    string stringS = "{";
    stringS += getStringKeyValue("title", title) + "," +
               getStringKeyValue("description", description) + "," +
               getBoolKeyValue("embeddable",embeddable)+","+
               getBoolKeyValue("monetizable",monetizable)+"}";

    return stringS;
}

//Hand Coded C++ serialization:
char *AdditionalMediaInfoEntity::serializeHandcoded(char *buffer, int &objectSize) {
    //Copy Strings:
    buffer = copyString(buffer, this->title, objectSize);
    buffer = copyString(buffer, this->description, objectSize);
    //Copy Booleans:
    buffer = copyBool(buffer, this->embeddable, objectSize);
    buffer = copyBool(buffer, this->monetizable, objectSize);
    return buffer;
}

//Hand Coded C++ de-serialization:
AdditionalMediaInfoEntity *AdditionalMediaInfoEntity::deserializeHandcoded(char *buffer, int &bytesRead) {
    //Parse Strings:
    parseString(buffer + bytesRead, this->title);
    bytesRead += (sizeof(int) + this->title.length());

    parseString(buffer + bytesRead, this->description);
    bytesRead += (sizeof(int) + this->description.length());

    // Boolean elements
    this->embeddable = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->embeddable);
    this->monetizable = parseBool(buffer + bytesRead);
    bytesRead += sizeof(this->monetizable);
    return this;
}

bsoncxx::document::value AdditionalMediaInfoEntity::serializeBSON() {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;

    document doc=document{};
    doc<<"title"<<this->title<<
    "description"<<this->description<<
    "embeddable"<<this->embeddable<<
    "monetizable"<<this->monetizable;

    return doc<<finalize;

}


