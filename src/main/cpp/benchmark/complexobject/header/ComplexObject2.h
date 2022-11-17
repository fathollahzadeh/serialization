#ifndef CPP_COMPLEXOBJECT2_H
#define CPP_COMPLEXOBJECT2_H

#include "ComplexObject3.h"

class ComplexObject2 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject3 *complexObject;

    ComplexObject2();

    ComplexObject3 *getComplexObject() const;

    void setComplexObject(ComplexObject3 *complexObject);

    explicit ComplexObject2(const string &varString);

    virtual ~ComplexObject2();

    char *serializeBoost(char *buffer, int &objectSize);

    char *serializeBoostBinary(char *buffer, int &objectSize);

    ComplexObject2 *deserializeBoostBinary(char *buffer, int bytesRead);

    ComplexObject2 *deserializeBoost(char *buffer, int bytesRead);

    char *serializeHandcoded(char *buffer, int &objectSize);

    ComplexObject2 *deserializeHandcoded(char *buffer, int &bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject2, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT2_H
