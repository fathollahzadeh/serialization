#ifndef CPP_COMPLEXOBJECT12_H
#define CPP_COMPLEXOBJECT12_H

#include "ComplexObject13.h"

class ComplexObject12 : public RootData {

private:
    string var_string;
    ComplexObject13 *complexObject;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:

    ComplexObject12();

    explicit ComplexObject12(const string &varString);

    virtual ~ComplexObject12();

    char *serializeBoost(char *buffer, int &objectSize);

    ComplexObject12 *deserializeBoost(char *buffer, int bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject12, boost::serialization::track_never)

#endif //CPP_COMPLEXOBJECT12_H
