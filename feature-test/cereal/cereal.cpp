#include "cereal.h"
#include <string>

#include "schema/test.h"
#include "../data.hpp"
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

using namespace std;

CerealTest::CerealTest() : FeatureTestObject(string("Cereal")) {

}

bool CerealTest::check_missing_field() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }

    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::ostringstream stream_in;
    cereal::BinaryOutputArchive archiver_out(stream_in);
    archiver_out(r1);
    string data = stream_in.str();

    RecordMissing r2;
    std::stringstream stream_out(data);
    cereal::BinaryInputArchive archiver_in(stream_out);
    try {
        archiver_in(r2);
    } catch (...) {
        return false;
    }

    return !(r2.strings != r1.strings || r2.strings.size() != kStringsCount);
}

bool CerealTest::check_new_field() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }

    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::ostringstream stream_in;
    cereal::BinaryOutputArchive archiver_out(stream_in);
    archiver_out(r1);
    string data = stream_in.str();

    RecordNewField r2;
    std::stringstream stream_out(data);
    cereal::BinaryInputArchive archiver_in(stream_out);
    try {
        archiver_in(r2);
    } catch (...) {
        return false;
    }

    return !(r2.ids != r1.ids || r2.ids.size() != kIntegers.size() ||
             r2.strings != r1.strings || r2.strings.size() != kStringsCount);
}

bool CerealTest::check_types_inheritance() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }

    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::ostringstream stream_in;
    cereal::BinaryOutputArchive archiver_out(stream_in);
    archiver_out(r1);
    string data = stream_in.str();

    RecordTypeInheritance r2;
    std::stringstream stream_out(data);
    cereal::BinaryInputArchive archiver_in(stream_out);
    try {
        archiver_in(r2);
    } catch (...) {
        return false;
    }

    if (r2.strings != r1.strings || r2.strings.size() != kStringsCount ||
        r1.ids.size() != r2.ids.size() || r2.ids.size() != kIntegers.size())
        return false;
    for (unsigned int i = 0; i < r2.ids.size(); i++) {
        if (r2.ids.at(i) != r1.ids.at(i))
            return false;
    }
    return true;
}

bool CerealTest::check_field_names() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }

    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::ostringstream stream_in;
    cereal::BinaryOutputArchive archiver_out(stream_in);
    archiver_out(r1);
    string data = stream_in.str();

    RecordRename r2;
    std::stringstream stream_out(data);
    cereal::BinaryInputArchive archiver_in(stream_out);
    try {
        archiver_in(r2);
    } catch (...) {
        return false;
    }

    return !(r2.ids_rem != r1.ids || r2.ids_rem.size() != kIntegers.size() ||
             r2.strings_rem != r1.strings || r2.strings_rem.size() != kStringsCount);
}