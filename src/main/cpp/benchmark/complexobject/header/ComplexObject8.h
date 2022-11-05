#ifndef CPP_COMPLEXOBJECT8_H
#define CPP_COMPLEXOBJECT8_H

#include "RootData.h"
#include "ComplexObject9.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class ComplexObject8 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject9 complexObject;

    ComplexObject8();

    virtual ~ComplexObject8();
};

#endif //CPP_COMPLEXOBJECT8_H
