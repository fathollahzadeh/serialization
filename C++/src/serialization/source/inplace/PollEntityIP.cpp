//
// Created by saeed on 11/29/19.
//

#include "PollEntityIP.h"

PollEntityIP::PollEntityIP() {}

PollEntityIP::~PollEntityIP() {}

PollEntityIP::PollEntityIP(PollEntity *pollEntity) {
    this->serialize(pollEntity);
}

void PollEntityIP::serialize(PollEntity *pollEntity) {
    this->numOfOptionEntity=pollEntity->options.size();
    this->options=new OptionEntityIP[this->numOfOptionEntity];
    for (int i = 0; i <this->numOfOptionEntity ; ++i) {
        this->options[i].serialize(pollEntity->options.at(i));
    }

    this->endDatetime = malloc <char> (strlen (pollEntity->endDatetime.c_str ()) + 1);
    strcpy (this->endDatetime, pollEntity->endDatetime.c_str ());

    this->durationMinutes = malloc <char> (strlen (pollEntity->durationMinutes.c_str ()) + 1);
    strcpy (this->durationMinutes, pollEntity->durationMinutes.c_str ());
}
