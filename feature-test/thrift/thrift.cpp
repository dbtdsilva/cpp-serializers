#include <string>
#include <set>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <chrono>
#include <sstream>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "gen-cpp/test_types.h"
#include "gen-cpp/test_constants.h"

#include "thrift.h"
#include "../data.hpp"

using namespace std;
using apache::thrift::transport::TMemoryBuffer;
using apache::thrift::protocol::TBinaryProtocol;
using apache::thrift::protocol::TBinaryProtocolT;
using apache::thrift::protocol::TProtocolException;

using namespace thrift_test;

ThriftTest::ThriftTest() : FeatureTestObject(string("Thrift")) {

}

bool ThriftTest::check_missing_field() {
    boost::shared_ptr<TMemoryBuffer> buffer1(new TMemoryBuffer());
    boost::shared_ptr<TMemoryBuffer> buffer2(new TMemoryBuffer());

    TBinaryProtocolT<TMemoryBuffer> binary_protocol1(buffer1);
    TBinaryProtocolT<TMemoryBuffer> binary_protocol2(buffer2);
    Record r1;

    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }

    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::string serialized;
    r1.write(&binary_protocol1);
    serialized = buffer1->getBufferAsString();

    // check if we can deserialize back
    RecordMissing r2;
    buffer2->resetBuffer((uint8_t*)serialized.data(), serialized.length());
    try {
        r2.read(&binary_protocol2);
    } catch(TProtocolException&) {
        return false;
    }

    if (r2.strings.size() != r1.strings.size()) return false;
    for (size_t i = 0; i < r2.strings.size(); i++) {
        if (r2.strings.at(i) != r1.strings.at(i))
            return false;
    }
    return true;
}

bool ThriftTest::check_new_field() {
    boost::shared_ptr<TMemoryBuffer> buffer1(new TMemoryBuffer());
    boost::shared_ptr<TMemoryBuffer> buffer2(new TMemoryBuffer());

    TBinaryProtocolT<TMemoryBuffer> binary_protocol1(buffer1);
    TBinaryProtocolT<TMemoryBuffer> binary_protocol2(buffer2);
    Record r1;

    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }

    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::string serialized;
    r1.write(&binary_protocol1);
    serialized = buffer1->getBufferAsString();

    // check if we can deserialize back
    RecordNewField r2;
    buffer2->resetBuffer((uint8_t*)serialized.data(), serialized.length());
    try {
        r2.read(&binary_protocol2);
    } catch(TProtocolException&) {
        return false;
    }

    if (r2.ids.size() != r1.ids.size() || r1.strings.size() != r2.strings.size()) return false;
    for (size_t i = 0; i < r2.ids.size(); i++) {
        if (r2.ids.at(i) != r1.ids.at(i))
            return false;
    }
    for (size_t i = 0; i < r2.strings.size(); i++) {
        if (r2.strings.at(i) != r1.strings.at(i))
            return false;
    }
    return true;
}

bool ThriftTest::check_types_inheritance() {
    boost::shared_ptr<TMemoryBuffer> buffer1(new TMemoryBuffer());
    boost::shared_ptr<TMemoryBuffer> buffer2(new TMemoryBuffer());

    TBinaryProtocolT<TMemoryBuffer> binary_protocol1(buffer1);
    TBinaryProtocolT<TMemoryBuffer> binary_protocol2(buffer2);
    Record r1;

    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }

    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::string serialized;
    r1.write(&binary_protocol1);
    serialized = buffer1->getBufferAsString();

    // check if we can deserialize back
    RecordTypes r2;
    buffer2->resetBuffer((uint8_t*)serialized.data(), serialized.length());
    try {
        r2.read(&binary_protocol2);
    } catch(TProtocolException&) {
        return false;
    }

    if (r2.ids.size() != r1.ids.size() || r1.strings.size() != r2.strings.size()) return false;
    for (size_t i = 0; i < r2.ids.size(); i++) {
        if (r2.ids.at(i) != r1.ids.at(i))
            return false;
    }
    for (size_t i = 0; i < r2.strings.size(); i++) {
        if (r2.strings.at(i) != r1.strings.at(i))
            return false;
    }
    return true;
}

bool ThriftTest::check_field_names() {
    boost::shared_ptr<TMemoryBuffer> buffer1(new TMemoryBuffer());
    boost::shared_ptr<TMemoryBuffer> buffer2(new TMemoryBuffer());

    TBinaryProtocolT<TMemoryBuffer> binary_protocol1(buffer1);
    TBinaryProtocolT<TMemoryBuffer> binary_protocol2(buffer2);
    Record r1;

    for (size_t i = 0; i < kIntegers.size(); i++) {
        r1.ids.push_back(kIntegers[i]);
    }

    for (size_t i = 0; i < kStringsCount; i++) {
        r1.strings.push_back(kStringValue);
    }

    std::string serialized;
    r1.write(&binary_protocol1);
    serialized = buffer1->getBufferAsString();

    // check if we can deserialize back
    RecordRename r2;
    buffer2->resetBuffer((uint8_t*)serialized.data(), serialized.length());
    try {
        r2.read(&binary_protocol2);
    } catch(TProtocolException&) {
        return false;
    }

    if (r2.ids_rem.size() != r1.ids.size() || r1.strings.size() != r2.strings_rem.size()) return false;
    for (size_t i = 0; i < r2.ids_rem.size(); i++) {
        if (r2.ids_rem.at(i) != r1.ids.at(i))
            return false;
    }
    for (size_t i = 0; i < r2.strings_rem.size(); i++) {
        if (r2.strings_rem.at(i) != r1.strings.at(i))
            return false;
    }
    return true;
}
