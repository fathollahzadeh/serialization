
#ifndef CPP_COMPLEXOBJECT15_H
#define CPP_COMPLEXOBJECT15_H

#include "ComplexObject16.h"

class ComplexObject15 : public RootData {

private:
    string var_string;
    ComplexObject16 *complexObject;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:

    explicit ComplexObject15(const string &varString);

    virtual ~ComplexObject15();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject15, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT15_H
