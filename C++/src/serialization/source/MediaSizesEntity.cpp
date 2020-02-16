
#include "MediaSizesEntity.h"

using namespace std;

//Default constructor:
MediaSizesEntity::MediaSizesEntity() {
}


MediaSizesEntity::MediaSizesEntity(SizeEntity *thumb, SizeEntity *large, SizeEntity *medium,
                                       SizeEntity *small) {
    this->thumb = thumb;
    this->large = large;
    this->medium = medium;
    this->small = small;
}


//C++: Explicit call needed for printing content:
string MediaSizesEntity::toJSON() {
    string stringS = "{\"0\":" + this->thumb->toJSON() + " , " +
                     "\"1\":" + this->large->toJSON() + " , " +
                     "\"2\":" + this->medium->toJSON() + "," +
                     "\"3\":" + this->small->toJSON() +
                     "}";

    return stringS;
}

//Hand Coded C++ serialization:
char *MediaSizesEntity::serializeHandcoded(char *buffer, int &objectSize) {

    buffer =this->thumb->serializeHandcoded(buffer, objectSize);

    buffer =this->large->serializeHandcoded(buffer, objectSize);

    buffer =this->medium->serializeHandcoded(buffer, objectSize);

    buffer =this->small->serializeHandcoded(buffer, objectSize);

    return buffer;
}


MediaSizesEntity * MediaSizesEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

    this->thumb=new SizeEntity();
    this->thumb->deserializeHandcoded(buffer, bytesRead);

    this->large=new SizeEntity();
    this->large->deserializeHandcoded(buffer, bytesRead);

    this->medium=new SizeEntity();
    this->medium->deserializeHandcoded(buffer, bytesRead);

    this->small=new SizeEntity();
    this->small->deserializeHandcoded(buffer, bytesRead);

    return this;
}


MediaSizesEntity::~MediaSizesEntity() {

    //free memory:
    if (thumb != nullptr)
        delete thumb;
    if (large != nullptr)
        delete large;
    if (medium != nullptr)
        delete medium;
    if (small != nullptr)
        delete small;
}

