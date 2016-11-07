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
#include <cstdlib>

#include "feature-test-obj.h"
#include "protobuf/protobuf.h"

using namespace std;

int main(int argc, char **argv)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    vector<unique_ptr<FeatureTestObject>> tests_protocols;

    if (argc < 1) {
        std::cout << "usage: " << argv[0] << " [thrift-binary thrift-compact protobuf boost msgpack cereal avro capnproto flatbuffers bson]";
        std::cout << std::endl << std::endl;
        return EXIT_SUCCESS;
    }

    std::set<std::string> names;
    if (argc > 2) {
        for (int i = 2; i < argc; i++) {
            names.insert(argv[i]);
        }
    }

    try {
        if (names.empty() || names.find("thrift-binary") != names.end()) {
        }

        if (names.empty() || names.find("thrift-compact") != names.end()) {

        }

        if (names.empty() || names.find("protobuf") != names.end()) {
            tests_protocols.push_back(make_unique<ProtobufTest>());
        }

        if (names.empty() || names.find("capnproto") != names.end()) {
        }

        if (names.empty() || names.find("boost") != names.end()) {
        }

        if (names.empty() || names.find("msgpack") != names.end()) {
        }

        if (names.empty() || names.find("cereal") != names.end()) {
        }

        if (names.empty() || names.find("avro") != names.end()) {
        }

        if (names.empty() || names.find("flatbuffers") != names.end()) {
        }

        if (names.empty() || names.find("bson") != names.end()) {
        }
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
