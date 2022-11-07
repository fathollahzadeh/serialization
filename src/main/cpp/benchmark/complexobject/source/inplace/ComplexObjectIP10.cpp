#include "ComplexObjectIP10.h"

void ComplexObjectIP10::serialize(ComplexObject10 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP11[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP10::ComplexObjectIP10(ComplexObject10 *object) {
    this->serialize(object);
}

ComplexObjectIP10::ComplexObjectIP10() {

}
