#ifndef CPP_COMPLEXOBJECTIP10_H
#define CPP_COMPLEXOBJECTIP10_H


#include <Object.h>
#include "ComplexObjectIP11.h"
#include "ComplexObject10.h"

class ComplexObjectIP10 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP11> complexObject;

    ComplexObjectIP10();

    ComplexObjectIP10(ComplexObject10 *object);

    void serialize(ComplexObject10 *complexObject);
};


#endif //CPP_COMPLEXOBJECTIP10_H
