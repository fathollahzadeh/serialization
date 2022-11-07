#ifndef CPP_COMPLEXOBJECT13_H
#define CPP_COMPLEXOBJECT13_H

#include "ComplexObject14.h"

class ComplexObject13 : public RootData {

private:


    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject14 *complexObject;

    ComplexObject13();

    ComplexObject14 *getComplexObject() const;

    void setComplexObject(ComplexObject14 *complexObject);

    explicit ComplexObject13(const string &varString);

    virtual ~ComplexObject13();

    char *serializeBoost(char *buffer, int &objectSize);

    ComplexObject13 *deserializeBoost(char *buffer, int bytesRead);

    char *serializeHandcoded(char *buffer, int &objectSize);

    ComplexObject13 *deserializeHandcoded(char *buffer, int &bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject13, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT13_H
