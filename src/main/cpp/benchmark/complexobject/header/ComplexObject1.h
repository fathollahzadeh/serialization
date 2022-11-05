#ifndef CPP_COMPLEXOBJECT1_H
#define CPP_COMPLEXOBJECT1_H


#include "RootData.h"
#include "ComplexObject2.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class ComplexObject1 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject2 complexObject;
};


#endif //CPP_COMPLEXOBJECT1_H
