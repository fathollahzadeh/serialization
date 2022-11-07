#ifndef CPP_COMPLEXOBJECTIP4_H
#define CPP_COMPLEXOBJECTIP4_H

#include <Object.h>
#include "ComplexObjectIP5.h"
#include "ComplexObject4.h"

class ComplexObjectIP4 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP5> complexObject;

    ComplexObjectIP4();

    ComplexObjectIP4(ComplexObject4 *object);

    void serialize(ComplexObject4 *complexObject);
};


#endif //CPP_COMPLEXOBJECTIP4_H
