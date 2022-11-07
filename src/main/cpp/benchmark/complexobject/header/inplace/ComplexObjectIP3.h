#ifndef CPP_COMPLEXOBJECTIP3_H
#define CPP_COMPLEXOBJECTIP3_H


#include <Object.h>
#include "ComplexObjectIP4.h"
#include "ComplexObject3.h"

class ComplexObjectIP3 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP4> complexObject;

    ComplexObjectIP3();

    ComplexObjectIP3(ComplexObject3 *object);

    void serialize(ComplexObject3 *complexObject);
};


#endif //CPP_COMPLEXOBJECTIP3_H
