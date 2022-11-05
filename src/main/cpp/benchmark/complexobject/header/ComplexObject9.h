#ifndef CPP_COMPLEXOBJECT9_H
#define CPP_COMPLEXOBJECT9_H


#include "RootData.h"
#include "ComplexObject10.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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
    ComplexObject10 complexObject;

    explicit ComplexObject9(const string &varString);

    virtual ~ComplexObject9();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject9, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT9_H
