#ifndef CPP_COMPLEXOBJECT1_H
#define CPP_COMPLEXOBJECT1_H


#include "RootData.h"
#include "ComplexObject2.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

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

    explicit ComplexObject1(const string &varString);

    virtual ~ComplexObject1();

    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject1, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT1_H
