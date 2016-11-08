#ifndef CPP_SERIALIZERS_AVRO_H
#define CPP_SERIALIZERS_AVRO_H

#include "../feature-test-obj.h"

class AvroTest : public FeatureTestObject
{
public:
    AvroTest();

    bool check_missing_field();
    bool check_new_field();
    bool check_types_inheritance();
    bool check_field_names();
};


#endif //CPP_SERIALIZERS_AVRO_H
