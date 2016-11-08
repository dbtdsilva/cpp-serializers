#ifndef CPP_SERIALIZERS_FLATBUFFERS_H
#define CPP_SERIALIZERS_FLATBUFFERS_H

#include "../feature-test-obj.h"

class FlatBuffersTest : public FeatureTestObject
{
public:
    FlatBuffersTest();

    bool check_missing_field();
    bool check_new_field();
    bool check_types_inheritance();
    bool check_field_names();
};


#endif //CPP_SERIALIZERS_FLATBUFFERS_H
