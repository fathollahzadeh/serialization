#ifndef CPP_COMPLEXOBJECTIP13_H
#define CPP_COMPLEXOBJECTIP13_H


#include <Object.h>
#include "ComplexObjectIP14.h"
#include "ComplexObject13.h"

class ComplexObjectIP13 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP14> complexObject;

    ComplexObjectIP13();

    ComplexObjectIP13(ComplexObject13 *object);

    void serialize(ComplexObject13 *complexObject);
};


#endif //CPP_COMPLEXOBJECTIP13_H
