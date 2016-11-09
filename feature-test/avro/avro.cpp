#include "avro.h"
#include <iostream>
#include <avro/Exception.hh>
#include "schema/record.h"
#include "../data.hpp"

using namespace std;
using namespace avro;

AvroTest::AvroTest() : FeatureTestObject(string("Avro")) {

}

bool AvroTest::check_missing_field() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }
    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::unique_ptr<OutputStream> out = memoryOutputStream();
    EncoderPtr encoder = binaryEncoder();

    encoder->init(*out);
    encode(*encoder, r1);

    std::unique_ptr<InputStream> in = memoryInputStream(*out);
    DecoderPtr decoder = binaryDecoder();

    decoder->init(*in);
    RecordMissing r2;
    decode(*decoder, r2);

    return !(r1.ids != r2.ids || r2.ids.size() != kIntegers.size());
}

bool AvroTest::check_new_field() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }
    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::unique_ptr<OutputStream> out = memoryOutputStream();
    EncoderPtr encoder = binaryEncoder();

    encoder->init(*out);
    encode(*encoder, r1);

    std::unique_ptr<InputStream> in = memoryInputStream(*out);
    DecoderPtr decoder = binaryDecoder();

    decoder->init(*in);
    RecordNewField r2;
    decode(*decoder, r2);

    return !(r1.ids != r2.ids || r2.ids.size() != kIntegers.size() || r1.strings != r2.strings ||
            r2.strings.size() != kStringsCount);
}

bool AvroTest::check_types_inheritance() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }
    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::unique_ptr<OutputStream> out = memoryOutputStream();
    EncoderPtr encoder = binaryEncoder();

    encoder->init(*out);
    encode(*encoder, r1);

    std::unique_ptr<InputStream> in = memoryInputStream(*out);
    DecoderPtr decoder = binaryDecoder();

    decoder->init(*in);
    RecordTypeInheritance r2;
    try {
        decode(*decoder, r2);
    } catch (avro::Exception&) {
        return false;
    }

    return !(r2.ids.size() != kIntegers.size() || r1.strings != r2.strings ||
             r2.strings.size() != kStringsCount);
}

bool AvroTest::check_field_names() {
    Record r1;
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }
    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::unique_ptr<OutputStream> out = memoryOutputStream();
    EncoderPtr encoder = binaryEncoder();

    encoder->init(*out);
    encode(*encoder, r1);

    std::unique_ptr<InputStream> in = memoryInputStream(*out);
    DecoderPtr decoder = binaryDecoder();

    decoder->init(*in);
    RecordRename r2;
    decode(*decoder, r2);

    return !(r1.ids != r2.ids_rem || r2.ids_rem.size() != kIntegers.size() || r1.strings != r2.strings_rem ||
             r2.strings_rem.size() != kStringsCount);
}