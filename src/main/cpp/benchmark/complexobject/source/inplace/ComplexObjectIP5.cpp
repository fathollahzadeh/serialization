#include "ComplexObjectIP5.h"

void ComplexObjectIP5::serialize(ComplexObject5 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP6[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP5::ComplexObjectIP5(ComplexObject5 *object) {
    this->serialize(object);
}

ComplexObjectIP5::ComplexObjectIP5() {

}
