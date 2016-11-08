#include "bson.h"
#include <string>

using namespace std;

BsonTest::BsonTest() : FeatureTestObject(string("Bson")) {

}

bool BsonTest::check_missing_field() {
    return false;
}

bool BsonTest::check_new_field() {
    return false;
}

bool BsonTest::check_types_inheritance() {
    return false;
}

bool BsonTest::check_field_names() {
    return false;
}