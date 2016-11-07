#include <string>
#include <set>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <chrono>
#include <sstream>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include "schema/test.pb.h"

#include "protobuf.h"
#include "schema/test.pb.h"

using namespace std;

ProtobufTest::ProtobufTest() : FeatureTestObject(string("Protobuf")) {

}
// This function checks if a protocol is still able to handle missing fields
bool ProtobufTest::check_missing_field() {
    return false;
}
// This function checks if a protocol is able to ignore a new field in the schema
bool ProtobufTest::check_new_field() {
    return false;
}
// This function checks for types change (e.g. int should be able to change to float)
bool ProtobufTest::check_types_inheritance() {
    return false;
}
// This function checks for if a field is able to change it's name or not
bool ProtobufTest::check_field_names() {
    return false;
}
