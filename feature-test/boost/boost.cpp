#include "boost.h"
#include "schema/test.h"
#include "../data.hpp"

using namespace std;
using namespace boost;

BoostTest::BoostTest() : FeatureTestObject(string("Boost")) {

}

bool BoostTest::check_missing_field() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }

    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::ostringstream stream_in;
    boost::archive::binary_oarchive archiver_in(stream_in);
    archiver_in << r1;
    string data = stream_in.str();

    RecordMissing r2;
    std::stringstream stream_out(data);
    boost::archive::binary_iarchive archiver_out(stream_out);
    try {
        archiver_out >> r2;
    } catch (...) {
        return false;
    }

    return !(r2.strings != r1.strings || r2.strings.size() != kStringsCount);
}

bool BoostTest::check_new_field() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }

    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::ostringstream stream_in;
    boost::archive::binary_oarchive archiver_in(stream_in);
    archiver_in << r1;
    string data = stream_in.str();

    RecordNewField r2;
    std::stringstream stream_out(data);
    boost::archive::binary_iarchive archiver_out(stream_out);
    try {
        archiver_out >> r2;
    } catch (...) {
        return false;
    }

    return !(r2.ids != r1.ids || r2.ids.size() != kIntegers.size() ||
            r2.strings != r1.strings || r2.strings.size() != kStringsCount);
}

bool BoostTest::check_types_inheritance() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }

    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::ostringstream stream_in;
    boost::archive::binary_oarchive archiver_in(stream_in);
    archiver_in << r1;
    string data = stream_in.str();

    RecordTypeInheritance r2;
    std::stringstream stream_out(data);
    boost::archive::binary_iarchive archiver_out(stream_out);
    try {
        archiver_out >> r2;
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

bool BoostTest::check_field_names() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }

    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::ostringstream stream_in;
    boost::archive::binary_oarchive archiver_in(stream_in);
    archiver_in << r1;
    string data = stream_in.str();

    RecordRename r2;
    std::stringstream stream_out(data);
    boost::archive::binary_iarchive archiver_out(stream_out);
    try {
        archiver_out >> r2;
    } catch (...) {
        return false;
    }

    return !(r2.ids_rem != r1.ids || r2.ids_rem.size() != kIntegers.size() ||
             r2.strings_rem != r1.strings || r2.strings_rem.size() != kStringsCount);
}