#ifndef CPP_COMPLEXOBJECTIP2_H
#define CPP_COMPLEXOBJECTIP2_H


#include <Object.h>
#include "ComplexObjectIP3.h"
#include "ComplexObject2.h"

class ComplexObjectIP2 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP3> complexObject;

    ComplexObjectIP2();

    ComplexObjectIP2(ComplexObject2 *object);

    void serialize(ComplexObject2 *complexObject);
};


#endif //CPP_COMPLEXOBJECTIP2_H
