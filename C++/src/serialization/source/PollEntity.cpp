//
// Created by saeed on 11/8/19.
//

#include "PollEntity.h"

PollEntity::PollEntity() {}

PollEntity::~PollEntity() {

    for (int i = 0; i <options.size() ; ++i) {
        delete options.at(i);
    }
    options.shrink_to_fit();
}

PollEntity::PollEntity(const vector<OptionEntity *> &options, const string &endDatetime,
                           const string &durationMinutes) : options(options), endDatetime(endDatetime),
                                                            durationMinutes(durationMinutes) {}


//C++: Explicit call needed for printing content:
string PollEntity::toJSON() {
    string stringS = "{";
    stringS += "\"Options\":[";
    if (options.size() > 0) {
        for (int i = 0; i < options.size() - 1; i++) {
            stringS += options[i]->toJSON() + " , ";
        }
        stringS += options[options.size() - 1]->toJSON();
    }
    stringS += "]," +
               getStringKeyValue("EndDatetime", this->endDatetime) + " , " +
               getStringKeyValue("DurationMinutes", this->durationMinutes) + "}";
    return stringS;
}


//Hand Coded C++ serialization:
char *PollEntity::serializeHandcoded(char *buffer, int &objectSize) {
    //Serialize the object.

    int numOfoptions = this->options.size();
    buffer = copyInt(buffer, numOfoptions, objectSize);
    for (int i = 0; i < numOfoptions; i++) {
        buffer =this->options.at(i)->serializeHandcoded(buffer, objectSize);
    }
    //Copy Strings:
    buffer = copyString(buffer, this->endDatetime, objectSize);
    buffer = copyString(buffer, this->durationMinutes, objectSize);

    return buffer;
}


PollEntity* PollEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

    int numOfoptions = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfoptions);
    for (int i = 0; i < numOfoptions; i++) {
        this->options.push_back(new OptionEntity());
        this->options.at(i)->deserializeHandcoded(buffer, bytesRead);

    }
    //Parse Strings:
    parseString(buffer + bytesRead, this->endDatetime);
    bytesRead += (sizeof(int) + this->endDatetime.length());
    parseString(buffer + bytesRead, this->durationMinutes);
    bytesRead += (sizeof(int) + this->durationMinutes.length());

    return this;
}
