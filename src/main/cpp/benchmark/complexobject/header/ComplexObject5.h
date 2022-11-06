#ifndef CPP_COMPLEXOBJECT5_H
#define CPP_COMPLEXOBJECT5_H

#include "ComplexObject6.h"

class ComplexObject5 : public RootData {

private:
    string var_string;
    ComplexObject6 *complexObject;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:

    explicit ComplexObject5(const string &varString);

    virtual ~ComplexObject5();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject5, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT5_H
