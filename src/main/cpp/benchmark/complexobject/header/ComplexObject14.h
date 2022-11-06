#ifndef CPP_COMPLEXOBJECT14_H
#define CPP_COMPLEXOBJECT14_H

#include "ComplexObject15.h"

class ComplexObject14 : public RootData {

private:
    string var_string;
    ComplexObject15 *complexObject;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    ComplexObject14();

    ComplexObject15 *getComplexObject() const;

    void setComplexObject(ComplexObject15 *complexObject);

    explicit ComplexObject14(const string &varString);

    virtual ~ComplexObject14();

    char *serializeBoost(char *buffer, int &objectSize);

    ComplexObject14 *deserializeBoost(char *buffer, int bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject14, boost::serialization::track_never)

#endif //CPP_COMPLEXOBJECT14_H
