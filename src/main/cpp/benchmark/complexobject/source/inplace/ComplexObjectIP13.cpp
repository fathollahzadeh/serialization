#include "ComplexObjectIP13.h"

void ComplexObjectIP13::serialize(ComplexObject13 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP14[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP13::ComplexObjectIP13(ComplexObject13 *object) {
    this->serialize(object);
}

ComplexObjectIP13::ComplexObjectIP13() {

}
