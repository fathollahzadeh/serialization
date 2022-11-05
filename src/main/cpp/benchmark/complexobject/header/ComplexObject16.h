#ifndef CPP_COMPLEXOBJECT16_H
#define CPP_COMPLEXOBJECT16_H

#include "RootData.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class ComplexObject16 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
    }

public:
    string var_string;

    ComplexObject16();

    virtual ~ComplexObject16();
};

#endif //CPP_COMPLEXOBJECT16_H
