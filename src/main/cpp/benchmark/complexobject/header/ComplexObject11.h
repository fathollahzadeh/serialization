#ifndef CPP_COMPLEXOBJECT11_H
#define CPP_COMPLEXOBJECT11_H

#include "ComplexObject12.h"

class ComplexObject11 : public RootData {

private:
    string var_string;
    ComplexObject12 *complexObject;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:

    explicit ComplexObject11(const string &varString);

    virtual ~ComplexObject11();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject11, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT11_H
