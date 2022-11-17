#ifndef CPP_COMPLEXOBJECT7_H
#define CPP_COMPLEXOBJECT7_H

#include "ComplexObject8.h"

class ComplexObject7 : public RootData {

private:

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject8 *complexObject;

    ComplexObject7();

    ComplexObject8 *getComplexObject() const;

    void setComplexObject(ComplexObject8 *complexObject);

    explicit ComplexObject7(const string &varString);

    virtual ~ComplexObject7();

    char *serializeBoost(char *buffer, int &objectSize);

    char *serializeBoostBinary(char *buffer, int &objectSize);

    ComplexObject7 *deserializeBoostBinary(char *buffer, int bytesRead);

    ComplexObject7 *deserializeBoost(char *buffer, int bytesRead);

    char *serializeHandcoded(char *buffer, int &objectSize);

    ComplexObject7 *deserializeHandcoded(char *buffer, int &bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject7, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT7_H
