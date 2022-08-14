#ifndef TWITTER_HASHTAGENTITYIP_H
#define TWITTER_HASHTAGENTITYIP_H

#include <vector>
#include <iostream>
#include "HashtagEntity.h"
#include "Object.h"

using namespace std;

class HashtagEntityIP : public Object {

private:
	vector<int> indices;
	offset_ptr<char> text;

public:

	HashtagEntityIP();

	virtual ~HashtagEntityIP();

	HashtagEntityIP(HashtagEntity *hashtagEntity);

	void serialize(HashtagEntity *hashtagEntity);
};


#endif //TWITTER_HASHTAGENTITYIP_H
