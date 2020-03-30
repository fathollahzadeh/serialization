
#include "Place.h"

using namespace std;

//Default constructor:
Place::Place() {
}

//Constructor with arguments:
Place::Place(string name, string countryCode, string id, string country, string placeType, string url,
                 string fullName,
                 BoundingBoxCoordinate *boundingBoxCoordinates) {
    this->name = name;
    this->countryCode = countryCode;
    this->id = id;
    this->country = country;
    this->placeType = placeType;
    this->url = url;
    this->fullName = fullName;
    this->boundingBoxCoordinates = boundingBoxCoordinates;
}

//C++: Explicit call needed for printing content:
string Place::toJSON() {
    string stringS = "{" +
                     getStringKeyValue("Name", this->name) + " , " +
                     getStringKeyValue("CountryCode", this->countryCode) + " , " +
                     getStringKeyValue("Id", this->id) + " , " +
                     getStringKeyValue("Country", this->country) + " , " +
                     getStringKeyValue("PlaceType", this->placeType) + " , " +
                     getStringKeyValue("Url", this->url) + " , " +
                     getStringKeyValue("FullName", this->fullName) + " , " +
                     "\"BoundingBoxCoordinates\":" + this->boundingBoxCoordinates->toJSON() + "}";
    return stringS;
}


//Hand Coded C++ serialization:
char *Place::serializeHandcoded(char *buffer, int &objectSize) {

    //Serialize the object.
    //Copy Strings:
    buffer = copyString(buffer, this->name, objectSize);
    buffer = copyString(buffer, this->countryCode, objectSize);
    buffer = copyString(buffer, this->id, objectSize);
    buffer = copyString(buffer, this->country, objectSize);
    buffer = copyString(buffer, this->placeType, objectSize);
    buffer = copyString(buffer, this->url, objectSize);
    buffer = copyString(buffer, this->fullName, objectSize);

    if (this->boundingBoxCoordinates != nullptr) {
        buffer = copyBool(buffer, false, objectSize);
        buffer = this->boundingBoxCoordinates->serializeHandcoded(buffer, objectSize);
    } else
        buffer = copyBool(buffer, true, objectSize);

    return buffer;
}


Place *Place::deserializeHandcoded(char *buffer, int &bytesRead) {

    //Parse Strings:
    parseString(buffer + bytesRead, this->name);
    bytesRead += (sizeof(int) + this->name.length());
    parseString(buffer + bytesRead, this->countryCode);
    bytesRead += (sizeof(int) + this->countryCode.length());
    parseString(buffer + bytesRead, this->id);
    bytesRead += (sizeof(int) + this->id.length());
    parseString(buffer + bytesRead, this->country);
    bytesRead += (sizeof(int) + this->country.length());
    parseString(buffer + bytesRead, this->placeType);
    bytesRead += (sizeof(int) + this->placeType.length());
    parseString(buffer + bytesRead, this->url);
    bytesRead += (sizeof(int) + this->url.length());
    parseString(buffer + bytesRead, this->fullName);
    bytesRead += (sizeof(int) + this->fullName.length());

    bool checknullptr;
    //BoundingBoxCoordinate:
    checknullptr = parseBool(buffer + bytesRead);
    bytesRead += sizeof(checknullptr);
    if (!checknullptr) {
        this->boundingBoxCoordinates =new BoundingBoxCoordinate();
        this->boundingBoxCoordinates->deserializeHandcoded(buffer, bytesRead);

    } else
        this->boundingBoxCoordinates = nullptr;
    return this;
}

bsoncxx::document::value Place::serializeBSON() {

    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;

    document doc=document{};
    doc<<"name"<<this->name<<
    "country_code"<<this->countryCode<<
    "id"<<this->id<<
    "country"<<this->country<<
    "place_type"<<this->placeType<<
    "url"<<this->url<<
    "full_name"<<this->fullName;

    if (this->boundingBoxCoordinates!= nullptr){
        doc<<"bounding_box" << bsoncxx::types::b_document{this->boundingBoxCoordinates->serializeBSON().view()} ;
    }
   return doc<<finalize;
}

Place::~Place() {
    if (boundingBoxCoordinates != nullptr) {
        delete boundingBoxCoordinates;
    }
}
