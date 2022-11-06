#ifndef CPP_COMPLEXOBJECT10_H
#define CPP_COMPLEXOBJECT10_H

#include "ComplexObject11.h"

class ComplexObject10 : public RootData {

private:
    string var_string;
    ComplexObject11 *complexObject;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:

    ComplexObject10();

    ComplexObject11 *getComplexObject() const;

    void setComplexObject(ComplexObject11 *complexObject);

    explicit ComplexObject10(const string &varString);

    virtual ~ComplexObject10();

    char *serializeBoost(char *buffer, int &objectSize);

    ComplexObject10 *deserializeBoost(char *buffer, int bytesRead);

    char *serializeHandcoded(char *buffer, int &objectSize);

    ComplexObject10 *deserializeHandcoded(char *buffer, int &bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject10, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT10_H
