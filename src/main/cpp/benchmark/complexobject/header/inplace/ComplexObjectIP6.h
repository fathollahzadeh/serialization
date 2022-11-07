#ifndef CPP_COMPLEXOBJECTIP6_H
#define CPP_COMPLEXOBJECTIP6_H

#include <Object.h>
#include "ComplexObjectIP7.h"
#include "ComplexObject6.h"

class ComplexObjectIP6 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP7> complexObject;

    ComplexObjectIP6();

    ComplexObjectIP6(ComplexObject6 *object);

    void serialize(ComplexObject6 *complexObject);
};

#endif //CPP_COMPLEXOBJECTIP6_H
