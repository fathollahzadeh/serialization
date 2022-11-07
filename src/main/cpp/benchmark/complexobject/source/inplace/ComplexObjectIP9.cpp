#include "ComplexObjectIP9.h"

void ComplexObjectIP9::serialize(ComplexObject9 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP10[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP9::ComplexObjectIP9(ComplexObject9 *object) {
    this->serialize(object);
}

ComplexObjectIP9::ComplexObjectIP9() {

}
