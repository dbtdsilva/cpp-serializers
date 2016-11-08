#ifndef CPP_SERIALIZERS_CEREAL_H
#define CPP_SERIALIZERS_CEREAL_H

#include "../feature-test-obj.h"

class CerealTest : public FeatureTestObject
{
public:
    CerealTest();

    bool check_missing_field();
    bool check_new_field();
    bool check_types_inheritance();
    bool check_field_names();
};


#endif //CPP_SERIALIZERS_CEREAL_H
