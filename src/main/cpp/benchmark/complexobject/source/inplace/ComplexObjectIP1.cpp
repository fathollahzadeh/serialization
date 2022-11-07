#include "ComplexObjectIP1.h"

void ComplexObjectIP1::serialize(ComplexObject1 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP2[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP1::ComplexObjectIP1(ComplexObject1 *object) {
    this->serialize(object);
}

ComplexObjectIP1::ComplexObjectIP1() {

}
