#ifndef CPP_COMPLEXOBJECT11_H
#define CPP_COMPLEXOBJECT11_H

#include "ComplexObject12.h"

class ComplexObject11 : public RootData {

private:


    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject12 *complexObject;

    ComplexObject11();

    ComplexObject12 *getComplexObject() const;

    void setComplexObject(ComplexObject12 *complexObject);

    explicit ComplexObject11(const string &varString);

    virtual ~ComplexObject11();

    char *serializeBoost(char *buffer, int &objectSize);

    ComplexObject11 *deserializeBoost(char *buffer, int bytesRead);

    char *serializeBoostBinary(char *buffer, int &objectSize);

    ComplexObject11 *deserializeBoostBinary(char *buffer, int bytesRead);

    char *serializeHandcoded(char *buffer, int &objectSize);

    ComplexObject11 *deserializeHandcoded(char *buffer, int &bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject11, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT11_H
