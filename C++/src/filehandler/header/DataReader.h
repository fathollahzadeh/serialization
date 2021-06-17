#ifndef C_DATAREADER_H
#define C_DATAREADER_H

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include <vector>
#include <map>
#include "../../serialization/header/Entities.h"
#include "../../serialization/header/User.h"
#include "../../serialization/header/Coordinates.h"
#include "../../serialization/header/Place.h"
#include "../../serialization/header/MatchingRulesEntity.h"
#include "../../serialization/header/TweetStatus.h"

using namespace rapidjson;
using namespace std;

class DataReader {

private:
	Entities *getEntities(Value &d);

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
