#include "cereal.h"
#include <string>

using namespace std;

CerealTest::CerealTest() : FeatureTestObject(string("Cereal")) {

}

bool CerealTest::check_missing_field() {
    return false;
}

bool CerealTest::check_new_field() {
    return false;
}

bool CerealTest::check_types_inheritance() {
    return false;
}

bool CerealTest::check_field_names() {
    return false;
}