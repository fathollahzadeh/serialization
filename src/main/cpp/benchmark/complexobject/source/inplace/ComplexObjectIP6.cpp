#include "ComplexObjectIP6.h"

void ComplexObjectIP6::serialize(ComplexObject6 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP7[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP6::ComplexObjectIP6(ComplexObject6 *object) {
    this->serialize(object);
}

ComplexObjectIP6::ComplexObjectIP6() {

}
