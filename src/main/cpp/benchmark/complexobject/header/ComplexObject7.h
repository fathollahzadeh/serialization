#ifndef CPP_COMPLEXOBJECT7_H
#define CPP_COMPLEXOBJECT7_H

#include "ComplexObject8.h"

class ComplexObject7 : public RootData {

private:
    string var_string;
    ComplexObject8 *complexObject;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:

    explicit ComplexObject7(const string &varString);

    virtual ~ComplexObject7();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject7, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT7_H
