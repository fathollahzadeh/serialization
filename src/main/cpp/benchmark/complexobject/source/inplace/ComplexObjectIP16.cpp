#include "ComplexObjectIP16.h"

void ComplexObjectIP16::serialize(ComplexObject16 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());
}

ComplexObjectIP16::ComplexObjectIP16(ComplexObject16 *object) {
    this->serialize(object);
}

ComplexObjectIP16::ComplexObjectIP16() {}
