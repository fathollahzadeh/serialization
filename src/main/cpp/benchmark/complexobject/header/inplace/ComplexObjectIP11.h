#ifndef CPP_COMPLEXOBJECTIP11_H
#define CPP_COMPLEXOBJECTIP11_H

#include <Object.h>
#include "ComplexObjectIP12.h"
#include "ComplexObject11.h"

class ComplexObjectIP11 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP12> complexObject;

    ComplexObjectIP11();

    ComplexObjectIP11(ComplexObject11 *object);

    void serialize(ComplexObject11 *complexObject);
};

#endif //CPP_COMPLEXOBJECTIP11_H
