
#include "Entities.h"


using namespace std;

//Default constructor:
Entities::Entities() {
}

//Constructor with arguments:
Entities::Entities(vector<HashtagEntity *> hashtags, vector<MediaEntity *> media, vector<URLEntity *> urls,
                       vector<UserMentionEntity *> userMentions, vector<SymbolEntity *> symbols,
                       vector<PollEntity *> polls) {
    this->hashtags = hashtags;
    this->media = media;
    this->urls = urls;
    this->userMentions = userMentions;
    this->symbols = symbols;
    this->polls = polls;
}

string Entities::toJSON() {

    //All hashtags:
    string stringS = "{\"Hashtags\":[";
    if (hashtags.size() > 0) {
        for (int i = 0; i < hashtags.size() - 1; i++) {
            stringS += hashtags[i]->toJSON() + " , ";
        }
        stringS += hashtags[hashtags.size() - 1]->toJSON();
    }
    stringS += "],";

    //All media:
    stringS += "\"Media\":[";
    if (media.size() > 0) {
        for (int i = 0; i < media.size() - 1; i++) {
            stringS += media[i]->toJSON() + " , ";
        }
        stringS += media[media.size() - 1]->toJSON();
    }
    stringS += "],";

    //All urls:
    stringS += "\"Urls\":[";
    if (urls.size() > 0) {
        for (int i = 0; i < urls.size() - 1; i++) {
            stringS += urls[i]->toJSON() + " , ";
        }
        stringS += urls[urls.size() - 1]->toJSON();
    }
    stringS += "],";

    //All userMentions:
    stringS += "\"UserMentions\":[";
    if (userMentions.size() > 0) {
        for (int i = 0; i < userMentions.size() - 1; i++) {
            stringS += userMentions[i]->toJSON() + " , ";
        }
        stringS += userMentions[userMentions.size() - 1]->toJSON();
    }
    stringS += "],";

    //All symbols:
    stringS += "\"Symbols\":[";
    if (symbols.size() > 0) {
        for (int i = 0; i < symbols.size() - 1; i++) {
            stringS += symbols[i]->toJSON() + " , ";
        }
        stringS += symbols[symbols.size() - 1]->toJSON();

    }
    stringS += "],";

    //All polls:
    stringS += "\"Polls\":[";
    if (polls.size() > 0) {
        for (int i = 0; i < polls.size() - 1; i++) {
            stringS += polls[i]->toJSON() + " , ";
        }
        stringS += polls[polls.size() - 1]->toJSON();

    }
    stringS += "]}";
    return stringS;
}

//Hand Coded C++ serialization:
char *Entities::serializeHandcoded(char *buffer, int &objectSize) {

    //Serialize the object.
    //Copy encapsulated objects:
    int numOfHashtags = this->hashtags.size();
    buffer = copyInt(buffer, numOfHashtags, objectSize);

    for (int i = 0; i < this->hashtags.size(); i++) {
        buffer = this->hashtags.at(i)->serializeHandcoded(buffer, objectSize);
    }

    int numOfMedia = this->media.size();
    buffer = copyInt(buffer, numOfMedia, objectSize);

    for (int i = 0; i < this->media.size(); i++) {
        buffer = this->media.at(i)->serializeHandcoded(buffer, objectSize);
    }

    int numOfUrls = this->urls.size();
    buffer = copyInt(buffer, numOfUrls, objectSize);

    for (int i = 0; i < this->urls.size(); i++) {
        buffer = this->urls.at(i)->serializeHandcoded(buffer, objectSize);
    }

    int numOfUserMentions = this->userMentions.size();
    buffer = copyInt(buffer, numOfUserMentions, objectSize);

    for (int i = 0; i < this->userMentions.size(); i++) {
        buffer = this->userMentions.at(i)->serializeHandcoded(buffer, objectSize);
    }

    int numOfSymbols = this->symbols.size();
    buffer = copyInt(buffer, numOfSymbols, objectSize);

    for (int i = 0; i < this->symbols.size(); i++) {
        buffer =this->symbols.at(i)->serializeHandcoded(buffer, objectSize);
    }

    int numOfPollss = this->polls.size();
    buffer = copyInt(buffer, numOfPollss, objectSize);

    for (int i = 0; i < this->polls.size(); i++) {
        buffer = this->polls.at(i)->serializeHandcoded(buffer, objectSize);
    }

    return buffer;
}


Entities *Entities::deserializeHandcoded(char *buffer, int &bytesRead) {

    //Encapsulated objects:
    int numOfHashtags = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfHashtags);
    for (int i = 0; i < numOfHashtags; i++) {
        this->hashtags.push_back(new HashtagEntity());
        this->hashtags.at(i)->deserializeHandcoded(buffer, bytesRead);
    }

    int numOfMedia = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfMedia);
    for (int i = 0; i < numOfMedia; i++) {
        this->media.push_back(new MediaEntity());
        this->media.at(i)->deserializeHandcoded(buffer, bytesRead);
    }

    int numOfUrls = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfUrls);
    for (int i = 0; i < numOfUrls; i++) {
        this->urls.push_back(new URLEntity());
        this->urls.at(i)->deserializeHandcoded(buffer, bytesRead);
    }

    int numOfUserMentions = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfUserMentions);
    for (int i = 0; i < numOfUserMentions; i++) {
        this->userMentions.push_back(new UserMentionEntity());
        this->userMentions.at(i)->deserializeHandcoded(buffer, bytesRead);
    }

    int numOfSymbols = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfSymbols);
    for (int i = 0; i < numOfSymbols; i++) {
        this->symbols.push_back(new SymbolEntity());
        this->symbols.at(i)->deserializeHandcoded(buffer, bytesRead);
    }

    int numOfPollss = parseInt(buffer + bytesRead);
    bytesRead += sizeof(numOfPollss);
    for (int i = 0; i < numOfPollss; i++) {
        this->polls.push_back(new PollEntity());
        this->polls.at(i)->deserializeHandcoded(buffer, bytesRead);
    }
    return this;
}

Entities::~Entities() {

    //free memory:
    for (int i = 0; i <hashtags.size() ; ++i) {
        delete hashtags.at(i);
    }
    hashtags.shrink_to_fit();

    for (int i = 0; i <media.size() ; ++i) {
        delete media.at(i);
    }
    media.shrink_to_fit();

    for (int i = 0; i <urls.size() ; ++i) {
        delete urls.at(i);
    }
    urls.shrink_to_fit();

    for (int i = 0; i <userMentions.size() ; ++i) {
        delete userMentions.at(i);
    }
    userMentions.shrink_to_fit();

    for (int i = 0; i <symbols.size() ; ++i) {
        delete symbols.at(i);
    }
    symbols.shrink_to_fit();

    for (int i = 0; i <polls.size() ; ++i) {
        delete polls.at(i);
    }
    polls.shrink_to_fit();

}


