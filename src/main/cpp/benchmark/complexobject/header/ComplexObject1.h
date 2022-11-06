#ifndef CPP_COMPLEXOBJECT1_H
#define CPP_COMPLEXOBJECT1_H

#include "ComplexObject2.h"

using namespace std;
class ComplexObject1 : public RootData {

private:
    string var_string;
    ComplexObject2 *complexObject;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:

    ComplexObject1();

    explicit ComplexObject1(const string &varString);

    virtual ~ComplexObject1();

    char *serializeBoost(char *buffer, int &objectSize);

    ComplexObject1 *deserializeBoost(char *buffer, int bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject1, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT1_H
