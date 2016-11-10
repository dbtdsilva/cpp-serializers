#include "flatbuffers.h"
#include "schema/test_generated.h"
#include "../data.hpp"
#include <iostream>

using namespace std;
using namespace flatbuffers;

FlatBuffersTest::FlatBuffersTest() : FeatureTestObject(string("FlatBuffers")) {

}

bool FlatBuffersTest::check_missing_field() {
    vector<Offset<String>> strings;
    strings.reserve(kStringsCount);

    FlatBufferBuilder builder;
    for (size_t i = 0; i < kStringsCount; i++) {
        strings.push_back(builder.CreateString(kStringValue));
    }

    auto ids_vec = builder.CreateVector(kIntegers);
    auto strings_vec = builder.CreateVector(strings);
    auto r1 = CreateRecord(builder, ids_vec, strings_vec);
    builder.Finish(r1);

    auto p = reinterpret_cast<char*>(builder.GetBufferPointer());
    auto sz = builder.GetSize();
    std::vector<char> buf(p, p + sz);

    const RecordMissing* r2 = GetRoot<RecordMissing>(buf.data());
    if (r2->strings()->size() != kIntegers.size()) {
        return false;
    }
    for (unsigned int i = 0; i < kStringsCount; i++) {
        if (string(r2->strings()->Get(i)->c_str()) != kStringValue)
            return false;
    }

    builder.ReleaseBufferPointer();
    return true;
}

bool FlatBuffersTest::check_new_field() {
    vector<Offset<String>> strings;
    strings.reserve(kStringsCount);

    FlatBufferBuilder builder;
    for (size_t i = 0; i < kStringsCount; i++) {
        strings.push_back(builder.CreateString(kStringValue));
    }

    auto ids_vec = builder.CreateVector(kIntegers);
    auto strings_vec = builder.CreateVector(strings);
    auto r1 = CreateRecord(builder, ids_vec, strings_vec);
    builder.Finish(r1);

    auto p = reinterpret_cast<char*>(builder.GetBufferPointer());
    auto sz = builder.GetSize();
    std::vector<char> buf(p, p + sz);

    const RecordNewField* r2 = GetRoot<RecordNewField>(buf.data());
    if (r2->strings()->size() != kStringsCount || r2->ids()->size() != kIntegers.size()) {
        return false;
    }
    for (unsigned int i = 0; i < kIntegers.size(); i++) {
        if (r2->ids()->Get(i) != kIntegers.at(i))
            return false;
    }
    for (unsigned int i = 0; i < kStringsCount; i++) {
        if (string(r2->strings()->Get(i)->c_str()) != kStringValue)
            return false;
    }

    builder.ReleaseBufferPointer();
    return true;
}

bool FlatBuffersTest::check_types_inheritance() {
    vector<Offset<String>> strings;
    strings.reserve(kStringsCount);

    FlatBufferBuilder builder;
    for (size_t i = 0; i < kStringsCount; i++) {
        strings.push_back(builder.CreateString(kStringValue));
    }

    auto ids_vec = builder.CreateVector(kIntegers);
    auto strings_vec = builder.CreateVector(strings);
    auto r1 = CreateRecord(builder, ids_vec, strings_vec);
    builder.Finish(r1);

    auto p = reinterpret_cast<char*>(builder.GetBufferPointer());
    auto sz = builder.GetSize();
    std::vector<char> buf(p, p + sz);

    const RecordTypeInheritance* r2 = GetRoot<RecordTypeInheritance>(buf.data());
    if (r2->strings()->size() != kStringsCount || r2->ids()->size() != kIntegers.size()) {
        return false;
    }
    for (unsigned int i = 0; i < kIntegers.size(); i++) {
        if (r2->ids()->Get(i) != kIntegers.at(i)) {
            return false;
        }
    }
    for (unsigned int i = 0; i < kStringsCount; i++) {
        if (string(r2->strings()->Get(i)->c_str()) != kStringValue)
            return false;
    }

    builder.ReleaseBufferPointer();
    return true;
}

bool FlatBuffersTest::check_field_names() {
    vector<Offset<String>> strings;
    strings.reserve(kStringsCount);

    FlatBufferBuilder builder;
    for (size_t i = 0; i < kStringsCount; i++) {
        strings.push_back(builder.CreateString(kStringValue));
    }

    auto ids_vec = builder.CreateVector(kIntegers);
    auto strings_vec = builder.CreateVector(strings);
    auto r1 = CreateRecord(builder, ids_vec, strings_vec);
    builder.Finish(r1);

    auto p = reinterpret_cast<char*>(builder.GetBufferPointer());
    auto sz = builder.GetSize();
    std::vector<char> buf(p, p + sz);

    const RecordRename* r2 = GetRoot<RecordRename>(buf.data());
    if (r2->strings_rem()->size() != kStringsCount || r2->ids_rem()->size() != kIntegers.size()) {
        return false;
    }
    for (unsigned int i = 0; i < kIntegers.size(); i++) {
        if (r2->ids_rem()->Get(i) != kIntegers.at(i))
            return false;
    }
    for (unsigned int i = 0; i < kStringsCount; i++) {
        if (string(r2->strings_rem()->Get(i)->c_str()) != kStringValue)
            return false;
    }

    builder.ReleaseBufferPointer();
    return true;
}