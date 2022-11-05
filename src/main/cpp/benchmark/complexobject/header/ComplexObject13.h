#ifndef CPP_COMPLEXOBJECT13_H
#define CPP_COMPLEXOBJECT13_H

#include "RootData.h"
#include "ComplexObject13.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class ComplexObject13 : public RootData {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject12 complexObject;

    explicit ComplexObject13(const string &varString);

    virtual ~ComplexObject13();
    char *serializeBoost(char *buffer, int &objectSize);
};

BOOST_CLASS_TRACKING(ComplexObject13, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT13_H
