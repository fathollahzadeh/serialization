#ifndef CPP_COMPLEXOBJECT10_H
#define CPP_COMPLEXOBJECT10_H

#include "ComplexObject11.h"

class ComplexObject10 : public RootData {

private:
    string var_string;
    ComplexObject11 *complexObject;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:

    explicit ComplexObject10(const string &varString);

    virtual ~ComplexObject10();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject10, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT10_H
