#ifndef CPP_COMPLEXOBJECTIP12_H
#define CPP_COMPLEXOBJECTIP12_H

#include <Object.h>
#include "ComplexObjectIP13.h"
#include "ComplexObject12.h"

class ComplexObjectIP12 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP13> complexObject;

    ComplexObjectIP12();

    ComplexObjectIP12(ComplexObject12 *object);

    void serialize(ComplexObject12 *complexObject);
};

#endif //CPP_COMPLEXOBJECTIP12_H
