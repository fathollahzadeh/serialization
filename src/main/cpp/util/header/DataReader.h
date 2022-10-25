#ifndef C_DATAREADER_H
#define C_DATAREADER_H

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include <vector>
#include <map>
#include "Entities.h"
#include "User.h"
#include "Coordinates.h"
#include "Place.h"
#include "MatchingRulesEntity.h"
#include "TweetStatus.h"

using namespace rapidjson;
using namespace std;

class DataReader {

private:
	Entities *getEntities(Value &d);

    ExtendedTweet *getExtendedTweet(Value &d);

	User *getUser(Value &d);

	Coordinates *getCoordinates(Value &d);

	Place *getPlace(Value &d);

	vector<MediaEntity *> getMedia(Value &d);

	vector<MatchingRulesEntity *> getMatchingRulesEntity(Value &d);


public:
	DataReader();

	virtual ~DataReader();

	TweetStatus *generateTweetObject(Document &d);


};

#endif //C_DATAREADER_H
