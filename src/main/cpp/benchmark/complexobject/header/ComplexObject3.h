#ifndef CPP_COMPLEXOBJECT3_H
#define CPP_COMPLEXOBJECT3_H

#include "ComplexObject4.h"

class ComplexObject3 : public RootData {

private:
    string var_string;
    ComplexObject4 *complexObject;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:

    ComplexObject3();

    ComplexObject4 *getComplexObject() const;

    void setComplexObject(ComplexObject4 *complexObject);

    explicit ComplexObject3(const string &varString);

    virtual ~ComplexObject3();

    char *serializeBoost(char *buffer, int &objectSize);

    ComplexObject3 *deserializeBoost(char *buffer, int bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject3, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT3_H
