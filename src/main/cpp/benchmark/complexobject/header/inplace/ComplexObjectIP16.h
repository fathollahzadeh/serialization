#ifndef CPP_COMPLEXOBJECTIP16_H
#define CPP_COMPLEXOBJECTIP16_H

#include <Object.h>
#include "ComplexObject16.h"

class ComplexObjectIP16 : public Object {

public:
    offset_ptr<char> var_string;

    ComplexObjectIP16();

    ComplexObjectIP16(ComplexObject16 *object);

    void serialize(ComplexObject16 *complexObject);
};


#endif //CPP_COMPLEXOBJECTIP16_H
