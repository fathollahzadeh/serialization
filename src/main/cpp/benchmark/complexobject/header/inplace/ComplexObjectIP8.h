#ifndef CPP_COMPLEXOBJECTIP8_H
#define CPP_COMPLEXOBJECTIP8_H


#include <Object.h>
#include "ComplexObjectIP9.h"
#include "ComplexObject8.h"

class ComplexObjectIP8 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP9> complexObject;

    ComplexObjectIP8();

    ComplexObjectIP8(ComplexObject8 *object);

    void serialize(ComplexObject8 *complexObject);
};


#endif //CPP_COMPLEXOBJECTIP8_H
