#include "ComplexObjectIP4.h"

void ComplexObjectIP4::serialize(ComplexObject4 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP5[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP4::ComplexObjectIP4(ComplexObject4 *object) {
    this->serialize(object);
}

ComplexObjectIP4::ComplexObjectIP4() {

}
