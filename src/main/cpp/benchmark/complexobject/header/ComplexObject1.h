#ifndef CPP_COMPLEXOBJECT1_H
#define CPP_COMPLEXOBJECT1_H

#include "ComplexObject2.h"

using namespace std;
class ComplexObject1 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject2 *complexObject;

    ComplexObject1();

    ComplexObject2 *getComplexObject() const;

    void setComplexObject(ComplexObject2 *complexObject);

    explicit ComplexObject1(const string &varString);

    virtual ~ComplexObject1();

    char *serializeBoost(char *buffer, int &objectSize);

    ComplexObject1 *deserializeBoost(char *buffer, int bytesRead);

    char *serializeHandcoded(char *buffer, int &objectSize);

    ComplexObject1 *deserializeHandcoded(char *buffer, int &bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject1, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT1_H
