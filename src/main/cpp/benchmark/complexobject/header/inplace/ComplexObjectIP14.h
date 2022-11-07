#ifndef CPP_COMPLEXOBJECTIP14_H
#define CPP_COMPLEXOBJECTIP14_H


#include <Object.h>
#include "ComplexObjectIP15.h"
#include "ComplexObject14.h"

class ComplexObjectIP14 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP15> complexObject;

    ComplexObjectIP14();

    ComplexObjectIP14(ComplexObject14 *object);

    void serialize(ComplexObject14 *complexObject);
};

#endif //CPP_COMPLEXOBJECTIP14_H
