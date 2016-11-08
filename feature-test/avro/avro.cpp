#include "avro.h"
#include <string>

using namespace std;

AvroTest::AvroTest() : FeatureTestObject(string("Avro")) {

}

bool AvroTest::check_missing_field() {
    return false;
}

bool AvroTest::check_new_field() {
    return false;
}

bool AvroTest::check_types_inheritance() {
    return false;
}

bool AvroTest::check_field_names() {
    return false;
}