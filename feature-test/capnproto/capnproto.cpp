#include "capnproto.h"

#include <capnp/message.h>
#include <capnp/serialize.h>

#include "schema/test.capnp.h"
#include "../data.hpp"

#include <iostream>
using namespace std;
using namespace capnp;

CapNProtoTest::CapNProtoTest() : FeatureTestObject(string("CapNProto")) {

}

bool CapNProtoTest::check_missing_field() {
    MallocMessageBuilder message;
    Record::Builder r1 = message.getRoot<Record>();

    auto ids = r1.initIds(kIntegers.size());
    for (size_t i = 0; i < kIntegers.size(); i++) {
        ids.set(i, kIntegers[i]);
    }

    auto strings = r1.initStrings(kStringsCount);
    for (size_t i = 0; i < kStringsCount; i++) {
        strings.set(i, kStringValue);
    }

    kj::ArrayPtr<const kj::ArrayPtr<const capnp::word>> serialized =
            message.getSegmentsForOutput();

    SegmentArrayMessageReader reader(serialized);
    RecordMissing::Reader r2;
    try {
        r2 = reader.getRoot<RecordMissing>();
        if (r2.getStrings().size() != kStringsCount) {
            return false;
        }
        for (unsigned int i = 0; i < r1.getStrings().size(); i++) {
            if (string(r1.getStrings()[i].cStr()) != string(r2.getStrings()[i].cStr()))
                return false;
        }
    } catch (...) {
        return false;
    }
    return true;
}

bool CapNProtoTest::check_new_field() {
    MallocMessageBuilder message;
    Record::Builder r1 = message.getRoot<Record>();

    auto ids = r1.initIds(kIntegers.size());
    for (size_t i = 0; i < kIntegers.size(); i++) {
        ids.set(i, kIntegers[i]);
    }

    auto strings = r1.initStrings(kStringsCount);
    for (size_t i = 0; i < kStringsCount; i++) {
        strings.set(i, kStringValue);
    }

    kj::ArrayPtr<const kj::ArrayPtr<const capnp::word>> serialized =
            message.getSegmentsForOutput();

    SegmentArrayMessageReader reader(serialized);
    RecordNewField::Reader r2;
    try {
        r2 = reader.getRoot<RecordNewField>();
        if (r2.getIds().size() != kIntegers.size() || r2.getStrings().size() != kStringsCount) {
            return false;
        }
        for (unsigned int i = 0; i < r1.getIds().size(); i++) {
            if (r1.getIds()[i] != r2.getIds()[i])
                return false;
        }
        for (unsigned int i = 0; i < r1.getStrings().size(); i++) {
            if (string(r1.getStrings()[i].cStr()) != string(r2.getStrings()[i].cStr()))
                return false;
        }
    } catch (...) {
        return false;
    }
    return true;
}

bool CapNProtoTest::check_types_inheritance() {
    MallocMessageBuilder message;
    Record::Builder r1 = message.getRoot<Record>();

    auto ids = r1.initIds(kIntegers.size());
    for (size_t i = 0; i < kIntegers.size(); i++) {
        ids.set(i, kIntegers[i]);
    }

    auto strings = r1.initStrings(kStringsCount);
    for (size_t i = 0; i < kStringsCount; i++) {
        strings.set(i, kStringValue);
    }
    kj::ArrayPtr<const kj::ArrayPtr<const capnp::word>> serialized =
            message.getSegmentsForOutput();

    SegmentArrayMessageReader reader(serialized);
    RecordTypeInheritance::Reader r2;
    try {
        r2 = reader.getRoot<RecordTypeInheritance>();
        if (r2.getIds().size() != kIntegers.size() || r2.getStrings().size() != kStringsCount) {
            return false;
        }
        for (unsigned int i = 0; i < r1.getIds().size(); i++) {
            if (r1.getIds()[i] != r2.getIds()[i])
                return false;
        }
        for (unsigned int i = 0; i < r1.getStrings().size(); i++) {
            if (string(r1.getStrings()[i].cStr()) != string(r2.getStrings()[i].cStr()))
                return false;
        }
    } catch (...) {
        return false;
    }
    return true;
}

bool CapNProtoTest::check_field_names() {
    MallocMessageBuilder message;
    Record::Builder r1 = message.getRoot<Record>();

    auto ids = r1.initIds(kIntegers.size());
    for (size_t i = 0; i < kIntegers.size(); i++) {
        ids.set(i, kIntegers[i]);
    }

    auto strings = r1.initStrings(kStringsCount);
    for (size_t i = 0; i < kStringsCount; i++) {
        strings.set(i, kStringValue);
    }
    kj::ArrayPtr<const kj::ArrayPtr<const capnp::word>> serialized =
            message.getSegmentsForOutput();

    SegmentArrayMessageReader reader(serialized);
    RecordRename::Reader r2;
    try {
        r2 = reader.getRoot<RecordRename>();
        if (r2.getIdsrem().size() != kIntegers.size() || r2.getStringsrem().size() != kStringsCount) {
            return false;
        }
        for (unsigned int i = 0; i < r1.getIds().size(); i++) {
            if (r1.getIds()[i] != r2.getIdsrem()[i])
                return false;
        }
        for (unsigned int i = 0; i < r1.getStrings().size(); i++) {
            if (string(r1.getStrings()[i].cStr()) != string(r2.getStringsrem()[i].cStr()))
                return false;
        }
    } catch (...) {
        return false;
    }
    return true;
}