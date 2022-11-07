#ifndef CPP_COMPLEXOBJECT8_H
#define CPP_COMPLEXOBJECT8_H

#include "ComplexObject9.h"

class ComplexObject8 : public RootData {

private:

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject9 *complexObject;
    ComplexObject8();

    ComplexObject9 *getComplexObject() const;

    void setComplexObject(ComplexObject9 *complexObject);

    explicit ComplexObject8(const string &varString);

    virtual ~ComplexObject8();

    char *serializeBoost(char *buffer, int &objectSize);

    ComplexObject8 *deserializeBoost(char *buffer, int bytesRead);

    char *serializeHandcoded(char *buffer, int &objectSize);

    ComplexObject8 *deserializeHandcoded(char *buffer, int &bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject8, boost::serialization::track_never)

#endif //CPP_COMPLEXOBJECT8_H
