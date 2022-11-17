#ifndef CPP_COMPLEXOBJECT9_H
#define CPP_COMPLEXOBJECT9_H

#include "ComplexObject10.h"

class ComplexObject9 : public RootData {

private:

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject10 *complexObject;

    ComplexObject9();

    ComplexObject10 *getComplexObject() const;

    void setComplexObject(ComplexObject10 *complexObject);

    explicit ComplexObject9(const string &varString);

    virtual ~ComplexObject9();

    char *serializeBoost(char *buffer, int &objectSize);

    char *serializeBoostBinary(char *buffer, int &objectSize);

    ComplexObject9 *deserializeBoostBinary(char *buffer, int bytesRead);

    ComplexObject9 *deserializeBoost(char *buffer, int bytesRead);

    char *serializeHandcoded(char *buffer, int &objectSize);

    ComplexObject9 *deserializeHandcoded(char *buffer, int &bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject9, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT9_H
