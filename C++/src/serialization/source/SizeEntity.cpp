
#include "SizeEntity.h"

using namespace std;


//Copy constructor:
SizeEntity::SizeEntity(const SizeEntity &obj) {
    throw invalid_argument("SizeEntity: Not copy constructible.");
}


//Default constructor:
SizeEntity::SizeEntity() {
}

//Constructor with arguments:
SizeEntity::SizeEntity(int width, int height, string resize) {
    this->width = width;
    this->height = height;
    this->resize = resize;
}

//C++: Explicit call needed for printing content:
string SizeEntity::toJSON() {
    string stringS = "{" +
                     getIntKeyValue("w", this->width) + " , " +
                     getIntKeyValue("h", this->height) + " , " +
                     getStringKeyValue("Resize", this->resize) + "}";
    return stringS;
}

//Hand Coded C++ serialization:
char *SizeEntity::serializeHandcoded(char *buffer, int &objectSize) {
    //Serialize the object.
    //Copy Integers:
    buffer = copyInt(buffer,this-> width, objectSize);
    buffer = copyInt(buffer,this-> height, objectSize);

    //Copy string
    buffer = copyString(buffer, this->resize, objectSize);

    return buffer;
}


SizeEntity * SizeEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

    this->width = parseInt(buffer + bytesRead);
    bytesRead += sizeof(this->width);

    this->height = parseInt(buffer + bytesRead);
    bytesRead += sizeof(this->height);

    parseString(buffer + bytesRead, this->resize);
    bytesRead += (sizeof(int) + this->resize.length());

    return this;
}


SizeEntity::~SizeEntity() {}

bsoncxx::document::value SizeEntity::serializeBSON() {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;
    using bsoncxx::builder::stream::array;

    document doc=document{};
    doc<<"width"<<this->width<<
    "height"<<this->height<<
    "resize"<<this->resize;

    return doc<<finalize;
}

SizeEntity *SizeEntity::deserializeBSON(bsoncxx::document::view doc) {

    bsoncxx::document::element element = doc["width"];
    this->width=element.get_int32();

    element = doc["height"];
    this->height=element.get_int32();

    element = doc["resize"];
    this->resize=bsoncxx::string::to_string(element.get_utf8().value);

    return this;
}
