#include "ComplexObjectIP14.h"

void ComplexObjectIP14::serialize(ComplexObject14 *complexObject) {
    this->var_string = malloc<char>(strlen(complexObject->var_string.c_str()) + 1);
    strcpy(this->var_string, complexObject->var_string.c_str());

    this->complexObject = new ComplexObjectIP15[1];
    this->complexObject[0].serialize(complexObject->complexObject);
}

ComplexObjectIP14::ComplexObjectIP14(ComplexObject14 *object) {
    this->serialize(object);
}

ComplexObjectIP14::ComplexObjectIP14() {

}
