#include "ComplexObjectIP7.h"

void ComplexObjectIP7::serialize(ComplexObject7 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP8[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP7::ComplexObjectIP7(ComplexObject7 *object) {
    this->serialize(object);
}

ComplexObjectIP7::ComplexObjectIP7() {

}
