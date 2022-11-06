#ifndef CPP_COMPLEXOBJECT4_H
#define CPP_COMPLEXOBJECT4_H

#include "ComplexObject5.h"

class ComplexObject4 : public RootData {

private:
    string var_string;
    ComplexObject5 *complexObject;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:

    ComplexObject4();

    ComplexObject5 *getComplexObject() const;

    void setComplexObject(ComplexObject5 *complexObject);

    explicit ComplexObject4(const string &varString);

    virtual ~ComplexObject4();

    char *serializeBoost(char *buffer, int &objectSize);

    ComplexObject4 *deserializeBoost(char *buffer, int bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject4, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT4_H
