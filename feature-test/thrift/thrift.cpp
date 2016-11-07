#include <string>
#include <set>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <chrono>
#include <sstream>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "gen-cpp/test_types.h"
#include "gen-cpp/test_constants.h"

#include "thrift.h"
#include "../data.hpp"

using namespace std;
using apache::thrift::transport::TMemoryBuffer;
using apache::thrift::protocol::TBinaryProtocol;
using apache::thrift::protocol::TBinaryProtocolT;

using namespace thrift_test;

ThriftTest::ThriftTest() : FeatureTestObject(string("Thrift")) {

}
// This function checks if a protocol is still able to handle missing fields
bool ThriftTest::check_missing_field() {
    return false;
}
// This function checks if a protocol is able to ignore a new field in the schema
bool ThriftTest::check_new_field() {
    return false;
}
// This function checks for types change (e.g. int should be able to change to float)
bool ThriftTest::check_types_inheritance() {
    return false;
}
// This function checks for if a field is able to change it's name or not
bool ThriftTest::check_field_names() {
    return false;
}
