#ifndef CPP_COMPLEXOBJECT3_H
#define CPP_COMPLEXOBJECT3_H

#include "ComplexObject4.h"

class ComplexObject3 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject4 *complexObject;

    ComplexObject3();

    ComplexObject4 *getComplexObject() const;

    void setComplexObject(ComplexObject4 *complexObject);

    explicit ComplexObject3(const string &varString);

    virtual ~ComplexObject3();

    char *serializeBoost(char *buffer, int &objectSize);

    ComplexObject3 *deserializeBoost(char *buffer, int bytesRead);

    char *serializeBoostBinary(char *buffer, int &objectSize);

    ComplexObject3 *deserializeBoostBinary(char *buffer, int bytesRead);

    char *serializeHandcoded(char *buffer, int &objectSize);

    ComplexObject3 *deserializeHandcoded(char *buffer, int &bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject3, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT3_H
