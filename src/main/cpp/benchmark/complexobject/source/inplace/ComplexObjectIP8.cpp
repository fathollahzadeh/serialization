#include "ComplexObjectIP8.h"

void ComplexObjectIP8::serialize(ComplexObject8 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP9[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP8::ComplexObjectIP8(ComplexObject8 *object) {
    this->serialize(object);
}

ComplexObjectIP8::ComplexObjectIP8() {

}
