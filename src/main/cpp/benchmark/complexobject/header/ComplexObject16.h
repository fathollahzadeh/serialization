#ifndef CPP_COMPLEXOBJECT16_H
#define CPP_COMPLEXOBJECT16_H

#include "RootData.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class ComplexObject16 : public RootData {

private:
    string var_string;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
    }

public:
    ComplexObject16();

    explicit ComplexObject16(const string &varString);

    virtual ~ComplexObject16();

    char *serializeBoost(char *buffer, int &objectSize);

    ComplexObject16 *deserializeBoost(char *buffer, int bytesRead);

    char *serializeHandcoded(char *buffer, int &objectSize);

    ComplexObject16 *deserializeHandcoded(char *buffer, int &bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject16, boost::serialization::track_never)

#endif //CPP_COMPLEXOBJECT16_H
