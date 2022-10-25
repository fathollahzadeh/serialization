#include "ExtendedTweet.h"

ExtendedTweet::~ExtendedTweet() {
    //free memory
    delete entities;
    delete extendedEntities;
    displayTextRange.shrink_to_fit();
}

ExtendedTweet::ExtendedTweet() {}

ExtendedTweet::ExtendedTweet(const string &fullText, const vector<int> &displayTextRange, Entities *entities,
                             ExtendedEntities *extendedEntities) : fullText(fullText),
                                                                   displayTextRange(displayTextRange),
                                                                   entities(entities),
                                                                   extendedEntities(extendedEntities) {}



char *ExtendedTweet::serializeHandcoded(char *buffer, int &objectSize) {

    //Copy Strings:
    buffer = copyString(buffer, this->fullText, objectSize);

    //Copy Integers:
    buffer = copyInt(buffer, this->displayTextRange.size(), objectSize);
    for (int i = 0; i < this->displayTextRange.size(); ++i) {
        buffer = copyInt(buffer, this->displayTextRange[i], objectSize);
    }

    if (this->entities != nullptr) {
        buffer = copyBool(buffer, false, objectSize);
        buffer = this->entities->serializeHandcoded(buffer, objectSize);
    } else
        buffer = copyBool(buffer, true, objectSize);

    if (this->extendedEntities != nullptr) {
        buffer = copyBool(buffer, false, objectSize);
        buffer = this->extendedEntities->serializeHandcoded(buffer, objectSize);
    } else
        buffer = copyBool(buffer, true, objectSize);

    return buffer;
}

ExtendedTweet *ExtendedTweet::deserializeHandcoded(char *buffer, int &bytesRead) {
    //Parse Strings:
    parseString(buffer + bytesRead, this->fullText);
    bytesRead += (sizeof(int) + this->fullText.length());

    //Parse Integers:
    int numOfDisplayTextRanges = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfDisplayTextRanges);

    for (int i = 0; i < numOfDisplayTextRanges; ++i) {
        this->displayTextRange.push_back(parseInt(buffer + bytesRead));
        bytesRead += sizeof(int);
    }

    bool checknullptr;
    //EntitiesHC:
    checknullptr = parseBool(buffer + bytesRead);
    bytesRead += sizeof(checknullptr);
    if (!checknullptr) {
        this->entities = new Entities();
        this->entities->deserializeHandcoded(buffer, bytesRead);
    } else
        this->entities = nullptr;

    //ExtendedEntitiesHC:
    checknullptr = parseBool(buffer + bytesRead);
    bytesRead += sizeof(checknullptr);
    if (!checknullptr) {
        this->extendedEntities = new ExtendedEntities();
        this->extendedEntities->deserializeHandcoded(buffer, bytesRead);
    } else
        this->extendedEntities = nullptr;

    return this;
}

bsoncxx::document::value ExtendedTweet::serializeBSON() {
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;
    using bsoncxx::builder::stream::array;
    using bsoncxx::builder::stream::open_array;
    using bsoncxx::builder::stream::close_array;

    document doc = document{};
    doc << "full_text" << this->fullText;

    auto arrDisplayTextRanges = array{};
    for (int i = 0; i < this->displayTextRange.size(); ++i) {
        arrDisplayTextRanges << this->displayTextRange[i];
    }
    doc << "display_text_range" << arrDisplayTextRanges;

    doc <<"entities" << bsoncxx::types::b_document{this->entities->serializeBSON().view()};
    if (this->extendedEntities != nullptr) {
        doc << "extended_entities" << bsoncxx::types::b_document{this->extendedEntities->serializeBSON().view()};
    }
    return doc << finalize;
}

ExtendedTweet *ExtendedTweet::deserializeBSON(bsoncxx::document::view doc) {
    bsoncxx::document::element element = doc["full_text"];
    this->fullText = bsoncxx::string::to_string(element.get_utf8().value);

    element = doc["display_text_range"];
    if (element && element.type() == bsoncxx::type::k_array) {
        for (auto ele : element.get_array().value) {
            this->displayTextRange.push_back(ele.get_int32());
        }
    }

    element = doc["entities"];
    this->entities = new Entities();
    this->entities->deserializeBSON(element.get_document().view());

    element = doc["extended_entities"];
    if (element) {
        this->extendedEntities = new ExtendedEntities();
        this->extendedEntities->deserializeBSON(element.get_document().view());
    } else
        this->extendedEntities = nullptr;

    return this;
}






