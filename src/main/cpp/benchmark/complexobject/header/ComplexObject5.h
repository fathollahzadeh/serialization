//
// Created by saeed on 05.11.22.
//

#ifndef CPP_COMPLEXOBJECT5_H
#define CPP_COMPLEXOBJECT5_H

#include "RootData.h"
#include "ComplexObject6.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class ComplexObject5 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject6 complexObject;

    explicit ComplexObject5(const string &varString);

    virtual ~ComplexObject5();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject5, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT5_H