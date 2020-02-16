#include "Coordinates.h"

using namespace std;


//Default constructor:
Coordinates::Coordinates() {
}

//Constructor with arguments:
Coordinates::Coordinates(string type, double *coordinates) {
    this->type = type;
    this->coordinates[0] = *coordinates;
    this->coordinates[1] = *(coordinates+1);
}


//C++: Explicit call needed for printing content:
string Coordinates::toJSON() {
    string stringS = "{" + getStringKeyValue("Type", this->type) + "," +
                     "\"coordinates\":[" +
                     dtos(this->coordinates[0]) + "," + dtos(this->coordinates[1]) + "]"

                             "}";
    return stringS;
}

//Hand Coded C++ serialization:
char *Coordinates::serializeHandcoded(char *buffer, int &objectSize) {
    //Serialize the object.
    //Copy Strings:
    buffer = copyString(buffer, this->type, objectSize);

    //Copy Double:
    buffer = copyDouble(buffer, *this->coordinates, objectSize); // 8 bytes for latitudes
    buffer = copyDouble(buffer, *(this->coordinates+1), objectSize); // 8 bytes for longitudes
    return buffer;
}


Coordinates *Coordinates::deserializeHandcoded(char *buffer, int &bytesRead) {

    //Parse Strings:
    parseString(buffer + bytesRead, this->type);
    bytesRead += (sizeof(int) + this->type.length());

    //Read 8 bytes for latitudes:
    this->coordinates[0]= parseDouble(buffer + bytesRead);
    bytesRead += sizeof(double);

    //Read 8 bytes for longitudes
    this->coordinates[1] = parseDouble(buffer + bytesRead);
    bytesRead += sizeof(double);

    return this;
}

Coordinates::~Coordinates() {
    // delete coordinates;
}



