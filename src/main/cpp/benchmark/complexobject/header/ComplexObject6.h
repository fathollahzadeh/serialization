//
// Created by saeed on 05.11.22.
//

#ifndef CPP_COMPLEXOBJECT6_H
#define CPP_COMPLEXOBJECT6_H


#include "RootData.h"
#include "ComplexObject7.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class ComplexObject6 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject7 complexObject;
};


#endif //CPP_COMPLEXOBJECT6_H
