#ifndef TWITTER_USERMENTIONENTITYIP_H
#define TWITTER_USERMENTIONENTITYIP_H

#include <iostream>
#include <vector>
#include "UserMentionEntity.h"
#include "Object.h"

using namespace std;

class UserMentionEntityIP : public Object {

private:
	long id;
	offset_ptr<char> idStr;
	vector<int> indices;
	offset_ptr<char> name;
	offset_ptr<char> screenName;

public:
	UserMentionEntityIP();

	virtual ~UserMentionEntityIP();

	//In place serialization:
	UserMentionEntityIP(UserMentionEntity *userMentionEntity);

	void serialize(UserMentionEntity *userMentionEntity);
};


#endif //TWITTER_USERMENTIONENTITYIP_H
