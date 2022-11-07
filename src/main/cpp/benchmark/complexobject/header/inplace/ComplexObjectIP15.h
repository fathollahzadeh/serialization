#ifndef CPP_COMPLEXOBJECTIP15_H
#define CPP_COMPLEXOBJECTIP15_H


#include <Object.h>
#include "ComplexObjectIP16.h"
#include "ComplexObject15.h"

class ComplexObjectIP15 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP16> complexObject;

    ComplexObjectIP15();

    ComplexObjectIP15(ComplexObject15 *object);

    void serialize(ComplexObject15 *complexObject);
};


#endif //CPP_COMPLEXOBJECTIP15_H
