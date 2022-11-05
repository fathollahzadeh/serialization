#ifndef CPP_COMPLEXOBJECT4_H
#define CPP_COMPLEXOBJECT4_H


#include "RootData.h"
#include "ComplexObject5.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class ComplexObject4 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject5 complexObject;

    explicit ComplexObject4(const string &varString);

    virtual ~ComplexObject4();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject4, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT4_H
