#include "ComplexObjectIP3.h"

void ComplexObjectIP3::serialize(ComplexObject3 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP4[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP3::ComplexObjectIP3(ComplexObject3 *object) {
    this->serialize(object);
}

ComplexObjectIP3::ComplexObjectIP3() {

}
