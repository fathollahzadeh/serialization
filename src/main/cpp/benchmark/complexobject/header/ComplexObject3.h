//
// Created by saeed on 05.11.22.
//

#ifndef CPP_COMPLEXOBJECT3_H
#define CPP_COMPLEXOBJECT3_H

#include "RootData.h"
#include "ComplexObject4.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class ComplexObject3 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject4 complexObject;

    explicit ComplexObject3(const string &varString);

    virtual ~ComplexObject3();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject3, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT3_H
