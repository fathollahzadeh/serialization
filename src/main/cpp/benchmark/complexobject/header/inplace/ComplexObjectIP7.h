
#ifndef CPP_COMPLEXOBJECTIP7_H
#define CPP_COMPLEXOBJECTIP7_H


#include <Object.h>
#include "ComplexObjectIP8.h"
#include "ComplexObject7.h"

class ComplexObjectIP7 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP8> complexObject;

    ComplexObjectIP7();

    ComplexObjectIP7(ComplexObject7 *object);

    void serialize(ComplexObject7 *complexObject);
};

#endif //CPP_COMPLEXOBJECTIP7_H
