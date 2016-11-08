#include <string>
#include <set>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <chrono>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <google/protobuf/stubs/common.h>

#include "feature-test/feature-test-obj.h"
#include "feature-test/avro/avro.h"
#include "feature-test/boost/boost.h"
#include "feature-test/bson/bson.h"
#include "feature-test/capnproto/capnproto.h"
#include "feature-test/cereal/cereal.h"
#include "feature-test/flatbuffers/flatbuffers.h"
#include "feature-test/msgpack/msgpack.h"
#include "feature-test/protobuf/protobuf.h"
#include "feature-test/thrift/thrift.h"

using namespace std;

int main(int argc, char **argv)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    vector<unique_ptr<FeatureTestObject>> tests_protocols;

    if (argc < 1) {
        std::cout << "usage: " << argv[0] << " [thrift protobuf boost msgpack cereal avro capnproto flatbuffers bson]";
        std::cout << std::endl << std::endl;
        return EXIT_SUCCESS;
    }

    std::set<std::string> names;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            names.insert(argv[i]);
        }
    }

    try {
        if (names.empty() || names.find("thrift") != names.end())
            tests_protocols.push_back(make_unique<ThriftTest>());
        if (names.empty() || names.find("protobuf") != names.end())
            tests_protocols.push_back(make_unique<ProtobufTest>());
        if (names.empty() || names.find("capnproto") != names.end())
            tests_protocols.push_back(make_unique<CapNProtoTest>());
        if (names.empty() || names.find("boost") != names.end())
            tests_protocols.push_back(make_unique<BoostTest>());
        if (names.empty() || names.find("msgpack") != names.end())
            tests_protocols.push_back(make_unique<MsgPackTest>());
        if (names.empty() || names.find("cereal") != names.end())
            tests_protocols.push_back(make_unique<CerealTest>());
        if (names.empty() || names.find("avro") != names.end())
            tests_protocols.push_back(make_unique<AvroTest>());
        if (names.empty() || names.find("flatbuffers") != names.end()) 
            tests_protocols.push_back(make_unique<FlatBuffersTest>());
        if (names.empty() || names.find("bson") != names.end()) 
            tests_protocols.push_back(make_unique<BsonTest>());
    } catch (std::exception &exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    for(auto const& protocol: tests_protocols) {
        cout << "Testing " << protocol->get_name() << endl;
        cout << "\tMissing field: " << (protocol->check_missing_field() ? "PASS" : "FAILED") << endl;
        cout << "\tAdded new field: " << (protocol->check_new_field() ? "PASS" : "FAILED") << endl;
        cout << "\tRenaming fields: " << (protocol->check_field_names() ? "PASS" : "FAILED") << endl;
        cout << "\tType inheritance: " << (protocol->check_types_inheritance() ? "PASS" : "FAILED") << endl;
        cout << endl;
    }

    google::protobuf::ShutdownProtobufLibrary();

    return EXIT_SUCCESS;
}
