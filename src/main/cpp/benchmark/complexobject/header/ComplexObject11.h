#ifndef CPP_COMPLEXOBJECT11_H
#define CPP_COMPLEXOBJECT11_H


#include "RootData.h"
#include "ComplexObject12.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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
    ComplexObject12 complexObject;

    explicit ComplexObject11(const string &varString);

    virtual ~ComplexObject11();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject11, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT11_H