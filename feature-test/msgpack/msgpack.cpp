#include "msgpack.h"
#include <string>

using namespace std;

MsgPackTest::MsgPackTest() : FeatureTestObject(string("MsgPack")) {

}

bool MsgPackTest::check_missing_field() {
    return false;
}

bool MsgPackTest::check_new_field() {
    return false;
}

bool MsgPackTest::check_types_inheritance() {
    return false;
}

bool MsgPackTest::check_field_names() {
    return false;
}