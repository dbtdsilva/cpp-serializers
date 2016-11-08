#include "flatbuffers.h"
#include <string>

using namespace std;

FlatBuffersTest::FlatBuffersTest() : FeatureTestObject(string("FlatBuffers")) {

}

bool FlatBuffersTest::check_missing_field() {
    return false;
}

bool FlatBuffersTest::check_new_field() {
    return false;
}

bool FlatBuffersTest::check_types_inheritance() {
    return false;
}

bool FlatBuffersTest::check_field_names() {
    return false;
}