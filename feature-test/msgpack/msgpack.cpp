#include "msgpack.h"

#include <iostream>
#include <msgpack.hpp>
#include "../data.hpp"
#include "schema/record.h"

using namespace std;
using namespace msgpack;

MsgPackTest::MsgPackTest() : FeatureTestObject(string("MsgPack")) {

}

bool MsgPackTest::check_missing_field() {
    Record r1;
    RecordMissing r2;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }
    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }
    sbuffer sbuf;
    pack(sbuf, r1);
    string serialized(sbuf.data(), sbuf.size());
    object_handle msg = unpack(serialized.data(), serialized.size());
    object obj = msg.get();
    try {
        obj.convert(r2);
    } catch(...) {
        return false;
    }
    if (r1.strings.size() != r2.strings.size())
        return false;

    for (unsigned int i = 0; i < r1.strings.size(); i++) {
        if (r1.strings.at(i) != r2.strings.at(i))
            return false;
    }
    return true;
}

bool MsgPackTest::check_new_field() {
    Record r1;
    RecordNewField r2;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }
    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }
    sbuffer sbuf;
    pack(sbuf, r1);
    string serialized(sbuf.data(), sbuf.size());
    object_handle msg = unpack(serialized.data(), serialized.size());
    object obj = msg.get();
    obj.convert(r2);

    if (r1.ids.size() != r2.ids.size() || r1.strings.size() != r2.strings.size())
        return false;

    for (unsigned int i = 0; i < r1.ids.size(); i++) {
        if (r1.ids.at(i) != r2.ids.at(i))
            return false;
    }
    for (unsigned int i = 0; i < r1.strings.size(); i++) {
        if (r1.strings.at(i) != r2.strings.at(i))
            return false;
    }
    return true;
}

bool MsgPackTest::check_types_inheritance() {
    Record r1;
    RecordTypeInheritance r2;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }
    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }
    sbuffer sbuf;
    pack(sbuf, r1);
    string serialized(sbuf.data(), sbuf.size());
    object_handle msg = unpack(serialized.data(), serialized.size());
    object obj = msg.get();
    obj.convert(r2);

    if (r1.ids.size() != r2.ids.size() || r1.strings.size() != r2.strings.size())
        return false;

    for (unsigned int i = 0; i < r1.ids.size(); i++) {
        if (r1.ids.at(i) != r2.ids.at(i))
            return false;
    }
    for (unsigned int i = 0; i < r1.strings.size(); i++) {
        if (r1.strings.at(i) != r2.strings.at(i))
            return false;
    }
    return true;
}

bool MsgPackTest::check_field_names() {
    Record r1;
    RecordRename r2;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }
    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }
    sbuffer sbuf;
    pack(sbuf, r1);
    string serialized(sbuf.data(), sbuf.size());
    object_handle msg = unpack(serialized.data(), serialized.size());
    object obj = msg.get();
    obj.convert(r2);

    if (r1.ids.size() != r2.ids_rem.size() || r1.strings.size() != r2.strings_rem.size())
        return false;

    for (unsigned int i = 0; i < r1.ids.size(); i++) {
        if (r1.ids.at(i) != r2.ids_rem.at(i))
            return false;
    }
    for (unsigned int i = 0; i < r1.strings.size(); i++) {
        if (r1.strings.at(i) != r2.strings_rem.at(i))
            return false;
    }
    return true;
}