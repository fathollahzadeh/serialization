#include "ComplexObjectIP15.h"

void ComplexObjectIP15::serialize(ComplexObject15 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP16[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP15::ComplexObjectIP15(ComplexObject15 *object) {
    this->serialize(object);
}

ComplexObjectIP15::ComplexObjectIP15() {}
