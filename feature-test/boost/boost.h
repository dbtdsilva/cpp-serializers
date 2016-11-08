#ifndef CPP_SERIALIZERS_BOOST_H
#define CPP_SERIALIZERS_BOOST_H

#include "../feature-test-obj.h"

class BoostTest : public FeatureTestObject
{
public:
    BoostTest();

    bool check_missing_field();
    bool check_new_field();
    bool check_types_inheritance();
    bool check_field_names();
};


#endif //CPP_SERIALIZERS_BOOST_H
