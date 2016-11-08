#include "boost.h"
#include <string>

using namespace std;

BoostTest::BoostTest() : FeatureTestObject(string("Boost")) {

}

bool BoostTest::check_missing_field() {
    return false;
}

bool BoostTest::check_new_field() {
    return false;
}

bool BoostTest::check_types_inheritance() {
    return false;
}

bool BoostTest::check_field_names() {
    return false;
}