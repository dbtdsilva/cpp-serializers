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

    if (argc < 2) {
        std::cout << "usage: " << argv[0] << " N [thrift-binary thrift-compact protobuf boost msgpack cereal avro capnproto flatbuffers bson]";
        std::cout << std::endl << std::endl;
        std::cout << "arguments: " << std::endl;
        std::cout << " N  -- number of iterations" << std::endl << std::endl;
        return EXIT_SUCCESS;
    }

    size_t iterations;

    try {
        iterations = boost::lexical_cast<size_t>(argv[1]);
    } catch (std::exception &exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        std::cerr << "First positional argument must be an integer." << std::endl;
        return EXIT_FAILURE;
    }

    std::set<std::string> names;

    if (argc > 2) {
        for (int i = 2; i < argc; i++) {
            names.insert(argv[i]);
        }
    }

    std::cout << "performing " << iterations << " iterations" << std::endl << std::endl;

    /*std::cout << "total size: " << sizeof(kIntegerValue) * kIntegersCount + kStringValue.size() * kStringsCount << std::endl;*/

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

    }

    google::protobuf::ShutdownProtobufLibrary();

    return EXIT_SUCCESS;
}
