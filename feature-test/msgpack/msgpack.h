#ifndef CPP_SERIALIZERS_MSGPACK_H
#define CPP_SERIALIZERS_MSGPACK_H

#include "../feature-test-obj.h"

class MsgPackTest : public FeatureTestObject
{
public:
    MsgPackTest();

    bool check_missing_field();
    bool check_new_field();
    bool check_types_inheritance();
    bool check_field_names();
};


#endif //CPP_SERIALIZERS_MSGPACK_H
