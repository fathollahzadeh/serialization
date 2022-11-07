#include "ComplexObjectIP11.h"

void ComplexObjectIP11::serialize(ComplexObject11 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP12[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP11::ComplexObjectIP11(ComplexObject11 *object) {
    this->serialize(object);
}

ComplexObjectIP11::ComplexObjectIP11() {

}
