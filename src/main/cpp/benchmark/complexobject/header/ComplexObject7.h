#ifndef CPP_COMPLEXOBJECT7_H
#define CPP_COMPLEXOBJECT7_H

#include "RootData.h"
#include "ComplexObject8.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class ComplexObject7 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject8 complexObject;
};


#endif //CPP_COMPLEXOBJECT7_H
