//
// Created by saeed on 11/29/19.
//

#include "OptionEntityIP.h"

OptionEntityIP::OptionEntityIP() {}

OptionEntityIP::~OptionEntityIP() {}

OptionEntityIP::OptionEntityIP(OptionEntity *optionEntity) {

   this->serialize(optionEntity);
}

void OptionEntityIP::serialize(OptionEntity *optionEntity) {
    this->position=optionEntity->position;

    this->text = malloc <char> (strlen (optionEntity->text.c_str ()) + 1);
    strcpy (this->text, optionEntity->text.c_str ());
}
