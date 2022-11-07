#include "ComplexObjectIP12.h"

void ComplexObjectIP12::serialize(ComplexObject12 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP13[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP12::ComplexObjectIP12(ComplexObject12 *object) {
    this->serialize(object);
}

ComplexObjectIP12::ComplexObjectIP12() {

}
