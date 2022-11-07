#ifndef CPP_COMPLEXOBJECTIP9_H
#define CPP_COMPLEXOBJECTIP9_H


#include <Object.h>
#include "ComplexObjectIP10.h"
#include "ComplexObject9.h"

class ComplexObjectIP9 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP10> complexObject;

    ComplexObjectIP9();

    ComplexObjectIP9(ComplexObject9 *object);

    void serialize(ComplexObject9 *complexObject);
};

#endif //CPP_COMPLEXOBJECTIP9_H
