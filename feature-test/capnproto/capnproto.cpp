//
// Created by myrddin on 07/11/16.
//

#include "capnproto.h"
#include <string>

using namespace std;

CapNProtoTest::CapNProtoTest() : FeatureTestObject(string("CapNProto")) {

}

bool CapNProtoTest::check_missing_field() {
    return false;
}

bool CapNProtoTest::check_new_field() {
    return false;
}

bool CapNProtoTest::check_types_inheritance() {
    return false;
}

bool CapNProtoTest::check_field_names() {
    return false;
}