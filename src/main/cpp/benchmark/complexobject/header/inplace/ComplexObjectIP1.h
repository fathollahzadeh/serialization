#ifndef CPP_COMPLEXOBJECTIP1_H
#define CPP_COMPLEXOBJECTIP1_H

#include <Object.h>
#include "ComplexObjectIP2.h"
#include "ComplexObject1.h"

class ComplexObjectIP1 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP2> complexObject;

    ComplexObjectIP1();

    ComplexObjectIP1(ComplexObject1 *object);

    void serialize(ComplexObject1 *complexObject);
};


#endif //CPP_COMPLEXOBJECTIP1_H
