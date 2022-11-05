//
// Created by saeed on 05.11.22.
//

#ifndef CPP_COMPLEXOBJECT10_H
#define CPP_COMPLEXOBJECT10_H


#include "RootData.h"
#include "ComplexObject11.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class ComplexObject10 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject11 complexObject;

    explicit ComplexObject10(const string &varString);

    virtual ~ComplexObject10();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject10, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT10_H
