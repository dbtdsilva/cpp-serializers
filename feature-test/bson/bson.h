#ifndef CPP_SERIALIZERS_BSON_H
#define CPP_SERIALIZERS_BSON_H

#include "../feature-test-obj.h"

class BsonTest : public FeatureTestObject
{
public:
    BsonTest();

    bool check_missing_field();
    bool check_new_field();
    bool check_types_inheritance();
    bool check_field_names();
};


#endif //CPP_SERIALIZERS_BSON_H
