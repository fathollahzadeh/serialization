#include "ComplexObjectIP2.h"

void ComplexObjectIP2::serialize(ComplexObject2 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP3[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP2::ComplexObjectIP2(ComplexObject2 *object) {
    this->serialize(object);
}

ComplexObjectIP2::ComplexObjectIP2() {

}
