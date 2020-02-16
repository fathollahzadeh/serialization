
#include "VariantEntity.h"

using namespace std;


//Copy constructor:
VariantEntity::VariantEntity(const VariantEntity &obj) {
    throw invalid_argument("VariantEntity: Not copy constructible.");
}


//Default constructor:
VariantEntity::VariantEntity() {
}

//Constructor with arguments:
VariantEntity::VariantEntity(long bitrate, string contentType, string url) {
    this->bitrate = bitrate;
    this->contentType = contentType;
    this->url = url;
}
//Hand Coded C++ serialization:
char *VariantEntity::serializeHandcoded(char *buffer, int &objectSize) {
    //Serialize the object.
    //Copy Long elements:
    buffer = copyLong(buffer, this->bitrate, objectSize);
    //Copy Strings:
    buffer = copyString(buffer, this->contentType, objectSize);
    buffer = copyString(buffer, this->url, objectSize);

    return buffer;
}


VariantEntity * VariantEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

    this->bitrate = parseLong(buffer + bytesRead);
    bytesRead += sizeof(this->bitrate);

    //Parse Strings:
    parseString(buffer + bytesRead, this->contentType);
    bytesRead += (sizeof(int) + this->contentType.length());
    parseString(buffer + bytesRead, this->url);
    bytesRead += (sizeof(int) + this->url.length());

    return this;
}

//C++: Explicit call needed for printing content:
string VariantEntity::toJSON() {
    string stringS = "{" +
                     getLongKeyValue("Bitrate", this->bitrate) + " , " +
                     getStringKeyValue("ContentType", this->contentType) + ", " +
                     getStringKeyValue("Url", this->url) + "}";
    return stringS;
}

VariantEntity::~VariantEntity() {

}
