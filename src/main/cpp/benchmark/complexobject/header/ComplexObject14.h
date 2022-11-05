#ifndef CPP_COMPLEXOBJECT14_H
#define CPP_COMPLEXOBJECT14_H


#include "RootData.h"
#include "ComplexObject15.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class ComplexObject14 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject15 complexObject;

    explicit ComplexObject14(const string &varString);

    virtual ~ComplexObject14();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject14, boost::serialization::track_never)

#endif //CPP_COMPLEXOBJECT14_H
