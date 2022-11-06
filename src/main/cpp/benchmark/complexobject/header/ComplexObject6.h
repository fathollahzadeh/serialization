#ifndef CPP_COMPLEXOBJECT6_H
#define CPP_COMPLEXOBJECT6_H

#include "ComplexObject7.h"

class ComplexObject6 : public RootData {

private:
    string var_string;
    ComplexObject7 *complexObject;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:

    explicit ComplexObject6(const string &varString);

    virtual ~ComplexObject6();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject6, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT6_H
