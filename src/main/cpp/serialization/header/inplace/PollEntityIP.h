#ifndef TWITTER_POLLENTITYIP_H
#define TWITTER_POLLENTITYIP_H

#include <iostream>
#include "OptionEntity.h"
#include "PollEntity.h"
#include "Object.h"
#include "OptionEntityIP.h"

using namespace std;

class PollEntityIP : public Object {

private:
	offset_ptr<OptionEntityIP> options;
	int numOfOptionEntity;
	offset_ptr<char> endDatetime;
	offset_ptr<char> durationMinutes;

public:

	PollEntityIP();

	virtual ~PollEntityIP();

	//In place object:
	PollEntityIP(PollEntity *pollEntity);

	void serialize(PollEntity *pollEntity);
};


#endif //TWITTER_POLLENTITYIP_H
