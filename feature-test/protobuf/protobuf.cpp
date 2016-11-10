#include <string>
#include <set>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <chrono>
#include <sstream>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include "protobuf.h"
#include "schema/test.pb.h"
#include "../data.hpp"

using namespace std;
using namespace protobuf_test;

ProtobufTest::ProtobufTest() : FeatureTestObject(string("Protobuf")) {

}

bool ProtobufTest::check_missing_field() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.add_ids(kIntegers[i]);
    }
    for (size_t i = 0; i < kStringsCount; i++) {
        r1.add_strings(kStringValue);
    }
    std::string serialized;
    r1.SerializeToString(&serialized);

    // check if we can deserialize back
    RecordMissing r2;
    bool ok = r2.ParseFromString(serialized);
    if (!ok || r1.strings_size() != r2.strings_size()) return false;
    for (int i = 0; i < r1.strings_size(); i++) {
        if (r2.strings(i) != r1.strings(i))
            return false;
    }
    return true;
}

bool ProtobufTest::check_new_field() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.add_ids(kIntegers[i]);
    }
    for (size_t i = 0; i < kStringsCount; i++) {
        r1.add_strings(kStringValue);
    }
    std::string serialized;
    r1.SerializeToString(&serialized);

    // check if we can deserialize back
    RecordNewField r2;
    bool ok = r2.ParseFromString(serialized);
    if (!ok || r1.ids_size() != r2.ids_size() || r1.strings_size() != r2.strings_size()) return false;
    for (int i = 0; i < r1.strings_size(); i++) {
        if (r2.strings(i) != r1.strings(i))
            return false;
    }
    for (int i = 0; i < r1.ids_size(); i++) {
        if (r2.ids(i) != r1.ids(i))
            return false;
    }
    return true;
}

bool ProtobufTest::check_types_inheritance() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.add_ids(kIntegers[i]);
    }
    for (size_t i = 0; i < kStringsCount; i++) {
        r1.add_strings(kStringValue);
    }
    std::string serialized;
    r1.SerializeToString(&serialized);

    // check if we can deserialize back
    RecordTypes r2;
    bool ok = r2.ParseFromString(serialized);
    if (!ok || r1.ids_size() != r2.ids_size() || r1.strings_size() != r2.strings_size()) return false;
    for (int i = 0; i < r1.strings_size(); i++) {
        if (r2.strings(i) != r1.strings(i))
            return false;
    }
    for (int i = 0; i < r1.ids_size(); i++) {
        if (r2.ids(i) != r1.ids(i))
            return false;
    }
    return true;
}

bool ProtobufTest::check_field_names() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.add_ids(kIntegers[i]);
    }
    for (size_t i = 0; i < kStringsCount; i++) {
        r1.add_strings(kStringValue);
    }
    std::string serialized;
    r1.SerializeToString(&serialized);

    // check if we can deserialize back
    RecordRename r2;
    bool ok = r2.ParseFromString(serialized);
    if (!ok || r1.ids_size() != r2.ids_rem_size() || r1.strings_size() != r2.strings_rem_size()) return false;
    for (int i = 0; i < r1.strings_size(); i++) {
        if (r2.strings_rem(i) != r1.strings(i))
            return false;
    }
    for (int i = 0; i < r1.ids_size(); i++) {
        if (r2.ids_rem(i) != r1.ids(i))
            return false;
    }
    return true;
}
