#ifndef CPP_COMPLEXOBJECTIP5_H
#define CPP_COMPLEXOBJECTIP5_H


#include <Object.h>
#include "ComplexObjectIP6.h"
#include "ComplexObject5.h"

class ComplexObjectIP5 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP6> complexObject;

    ComplexObjectIP5();

    ComplexObjectIP5(ComplexObject5 *object);

    void serialize(ComplexObject5 *complexObject);
};


#endif //CPP_COMPLEXOBJECTIP5_H
