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
#include <thrift/protocol/TCompactProtocol.h>
#include "thrift/gen-cpp/test_types.h"
#include "thrift/gen-cpp/test_constants.h"
#include <capnp/message.h>
#include <capnp/serialize.h>
#include <bson.h>

#include "protobuf/test.pb.h"
#include "capnproto/test.capnp.h"
#include "boost/record.hpp"
#include "msgpack/record.hpp"
#include "cereal/record.hpp"
#include "avro/record.hpp"
#include "flatbuffers/test_generated.h"

#include "data_generator.h"

enum class ThriftSerializationProto {
    Binary,
    Compact
};

void thrift_serialization_test(size_t iterations, DataGenerator& data_ref,
                               ThriftSerializationProto proto = ThriftSerializationProto::Binary)
{
    using apache::thrift::transport::TMemoryBuffer;
    using apache::thrift::protocol::TBinaryProtocol;
    using apache::thrift::protocol::TCompactProtocol;
    using apache::thrift::protocol::TBinaryProtocolT;
    using apache::thrift::protocol::TCompactProtocolT;

    using namespace thrift_test;
    boost::shared_ptr<TMemoryBuffer> buffer1(new TMemoryBuffer());
    boost::shared_ptr<TMemoryBuffer> buffer2(new TMemoryBuffer());

    TBinaryProtocolT<TMemoryBuffer> binary_protocol1(buffer1);
    TBinaryProtocolT<TMemoryBuffer> binary_protocol2(buffer2);

    TCompactProtocolT<TMemoryBuffer> compact_protocol1(buffer1);
    TCompactProtocolT<TMemoryBuffer> compact_protocol2(buffer2);

    Record r1;
    for (size_t i = 0; i < data_ref.integer_list_.size(); i++) {
        r1.ids.push_back(data_ref.integer_list_[i]);
    }
    for (size_t i = 0; i < data_ref.string_list_.size(); i++) {
        r1.strings.push_back(data_ref.string_list_[i]);
    }

    std::string serialized;
    if (proto == ThriftSerializationProto::Binary) {
        r1.write(&binary_protocol1);
    } else if (proto == ThriftSerializationProto::Compact) {
        r1.write(&compact_protocol1);
    }

    serialized = buffer1->getBufferAsString();
    // check if we can deserialize back
    Record r2;
    buffer2->resetBuffer((uint8_t*)serialized.data(), serialized.length());
    if (proto == ThriftSerializationProto::Binary) {
        r2.read(&binary_protocol2);
    } else if (proto == ThriftSerializationProto::Compact) {
        r2.read(&compact_protocol2);
    }

    if (r1 != r2) {
        throw std::logic_error("thrift's case: deserialization failed");
    }

    std::string tag;
    if (proto == ThriftSerializationProto::Binary) {
        tag = "thrift-binary:";
    } else if (proto == ThriftSerializationProto::Compact) {
        tag = "thrift-compact:";
    }

    std::cout << tag << " size = " << serialized.size() << " bytes" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    if (proto == ThriftSerializationProto::Binary) {
        for (size_t i = 0; i < iterations; i++) {
            buffer1->resetBuffer();
            r1.write(&binary_protocol1);
            serialized = buffer1->getBufferAsString();
            buffer2->resetBuffer((uint8_t*)serialized.data(), serialized.length());
            r2.read(&binary_protocol2);
        }
    } else if (proto == ThriftSerializationProto::Compact) {
        for (size_t i = 0; i < iterations; i++) {
            buffer1->resetBuffer();
            r1.write(&compact_protocol1);
            serialized = buffer1->getBufferAsString();
            buffer2->resetBuffer((uint8_t*)serialized.data(), serialized.length());
            r2.read(&compact_protocol2);
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << tag << "total time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    if (proto == ThriftSerializationProto::Binary) {
        for (size_t i = 0; i < iterations; i++) {
            buffer1->resetBuffer();
            r1.write(&binary_protocol1);
            serialized = buffer1->getBufferAsString();
        }
    } else if (proto == ThriftSerializationProto::Compact) {
        for (size_t i = 0; i < iterations; i++) {
            buffer1->resetBuffer();
            r1.write(&compact_protocol1);
            serialized = buffer1->getBufferAsString();
        }
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << tag << "serialize time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    if (proto == ThriftSerializationProto::Binary) {
        for (size_t i = 0; i < iterations; i++) {
            buffer2->resetBuffer((uint8_t*)serialized.data(), serialized.length());
            r2.read(&binary_protocol2);
        }
    } else if (proto == ThriftSerializationProto::Compact) {
        for (size_t i = 0; i < iterations; i++) {
            buffer2->resetBuffer((uint8_t*)serialized.data(), serialized.length());
            r2.read(&compact_protocol2);
        }
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << tag << "unserialize time = " << duration << " milliseconds" << std::endl << std::endl;
}

void protobuf_serialization_test(size_t iterations, DataGenerator& data_ref)
{
    using namespace protobuf_test;

    Record r1;
    for (size_t i = 0; i < data_ref.integer_list_.size(); i++) {
        r1.add_ids(data_ref.integer_list_[i]);
    }
    for (size_t i = 0; i < data_ref.string_list_.size(); i++) {
        r1.add_strings(data_ref.string_list_[i]);
    }

    std::string serialized;

    r1.SerializeToString(&serialized);

    // check if we can deserialize back
    Record r2;
    bool ok = r2.ParseFromString(serialized);
    if (!ok /*|| r2 != r1*/) {
        throw std::logic_error("protobuf's case: deserialization failed");
    }

    std::cout << "protobuf: size = " << serialized.size() << " bytes" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        serialized.clear();
        r1.SerializeToString(&serialized);
        r2.ParseFromString(serialized);

        (void)r2.ids().size();
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "protobuf: total time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        serialized.clear();
        r1.SerializeToString(&serialized);
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "protobuf: serialize time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        r2.ParseFromString(serialized);
        (void)r2.ids().size();
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "protobuf: unserialize time = " << duration << " milliseconds" << std::endl << std::endl;
}

void capnproto_serialization_test(size_t iterations, DataGenerator& data_ref)
{
    using namespace capnp_test;

    capnp::MallocMessageBuilder message;
    Record::Builder r1 = message.getRoot<Record>();

    auto ids = r1.initIds(data_ref.integer_list_.size());
    for (size_t i = 0; i < data_ref.integer_list_.size(); i++) {
        ids.set(i, data_ref.integer_list_[i]);
    }

    auto strings = r1.initStrings(data_ref.string_list_.size());
    for (size_t i = 0; i < data_ref.string_list_.size(); i++) {
        strings.set(i, data_ref.string_list_[i]);
    }

    kj::ArrayPtr<const kj::ArrayPtr<const capnp::word>> serialized = message.getSegmentsForOutput();

    // check if we can deserialize back
    capnp::SegmentArrayMessageReader reader(serialized);
    Record::Reader r2 = reader.getRoot<Record>();
    if (r2.getIds().size() != data_ref.integer_list_.size() ||
            r2.getStrings().size() != data_ref.string_list_.size()) {
        throw std::logic_error("capnproto's case: deserialization failed");
    }

    size_t size = 0;
    for (auto segment: serialized) {
        size += segment.asBytes().size();
    }

    std::cout << "capnproto: size = " << size << " bytes" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        capnp::MallocMessageBuilder message;
        Record::Builder r1 = message.getRoot<Record>();
        auto ids = r1.initIds(data_ref.integer_list_.size());
        for (size_t j = 0; j < data_ref.integer_list_.size(); j++) {
            ids.set(j, data_ref.integer_list_[j]);
        }
        auto strings = r1.initStrings(data_ref.string_list_.size());
        for (size_t j = 0; j < data_ref.string_list_.size(); j++) {
            strings.set(j, data_ref.string_list_[j]);
        }
        serialized = message.getSegmentsForOutput();
        capnp::SegmentArrayMessageReader reader(serialized);
        auto r2 = reader.getRoot<Record>();
        (void)r2.getIds().size();
        (void)r2.getStrings().size();
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "capnproto: total time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        capnp::MallocMessageBuilder message;
        Record::Builder r1 = message.getRoot<Record>();
        auto ids = r1.initIds(data_ref.integer_list_.size());
        for (size_t j = 0; j < data_ref.integer_list_.size(); j++) {
            ids.set(j, data_ref.integer_list_[j]);
        }
        auto strings = r1.initStrings(data_ref.string_list_.size());
        for (size_t j = 0; j < data_ref.string_list_.size(); j++) {
            strings.set(j, data_ref.string_list_[j]);
        }
        serialized = message.getSegmentsForOutput();
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "capnproto: serialize serialize time = " << duration << " milliseconds" << std::endl;


    r1 = message.getRoot<Record>();
    ids = r1.initIds(data_ref.integer_list_.size());
    for (size_t j = 0; j < data_ref.integer_list_.size(); j++) {
        ids.set(j, data_ref.integer_list_[j]);
    }
    strings = r1.initStrings(data_ref.string_list_.size());
    for (size_t j = 0; j < data_ref.string_list_.size(); j++) {
        strings.set(j, data_ref.string_list_[j]);
    }
    serialized = message.getSegmentsForOutput();

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        capnp::SegmentArrayMessageReader reader(serialized);
        auto r2 = reader.getRoot<Record>();
        (void)r2.getIds().size();
        (void)r2.getStrings().size();
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "capnproto: unserialize time = " << duration << " milliseconds" << std::endl << std::endl;
}

void boost_serialization_test(size_t iterations, DataGenerator& data_ref)
{
    using namespace boost_test;

    Record r1, r2;

    for (size_t i = 0; i < data_ref.integer_list_.size(); i++) {
        r1.ids.push_back(data_ref.integer_list_[i]);
    }

    for (size_t i = 0; i < data_ref.string_list_.size(); i++) {
        r1.strings.push_back(data_ref.string_list_[i]);
    }

    std::string serialized;

    to_string(r1, serialized);
    from_string(r2, serialized);

    if (r1 != r2) {
        throw std::logic_error("boost's case: deserialization failed");
    }

    std::cout << "boost: size = " << serialized.size() << " bytes" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        serialized.clear();
        to_string(r1, serialized);
        from_string(r2, serialized);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "boost: total time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        serialized.clear();
        to_string(r1, serialized);
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "boost: serialize time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        from_string(r2, serialized);
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "boost: unserialize time = " << duration << " milliseconds" << std::endl << std::endl;
}

void msgpack_serialization_test(size_t iterations, DataGenerator& data_ref)
{
    using namespace msgpack_test;

    Record r1, r2;

    for (size_t i = 0; i < data_ref.integer_list_.size(); i++) {
        r1.ids.push_back(data_ref.integer_list_[i]);
    }

    for (size_t i = 0; i < data_ref.string_list_.size(); i++) {
        r1.strings.push_back(data_ref.string_list_[i]);
    }

    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, r1);
    std::string serialized(sbuf.data(), sbuf.size());
    msgpack::object_handle msg = msgpack::unpack(serialized.data(), serialized.size());
    msgpack::object obj = msg.get();

    obj.convert(r2);

    if (r1 != r2) {
        throw std::logic_error("msgpack's case: deserialization failed");
    }

    std::cout << "msgpack: size = " << serialized.size() << " bytes" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        sbuf.clear();
        msgpack::pack(sbuf, r1);
        msgpack::object_handle msg = msgpack::unpack(sbuf.data(), sbuf.size());
        msgpack::object obj = msg.get();
        obj.convert(r2);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "msgpack: total time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        sbuf.clear();
        msgpack::pack(sbuf, r1);
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "msgpack: serialize time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        msgpack::object_handle msg = msgpack::unpack(sbuf.data(), sbuf.size());
        msgpack::object obj = msg.get();
        obj.convert(r2);
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "msgpack: unserialize time = " << duration << " milliseconds" << std::endl << std::endl;
}

void cereal_serialization_test(size_t iterations, DataGenerator& data_ref)
{
    using namespace cereal_test;

    Record r1, r2;

    for (size_t i = 0; i < data_ref.integer_list_.size(); i++) {
        r1.ids.push_back(data_ref.integer_list_[i]);
    }
    for (size_t i = 0; i < data_ref.string_list_.size(); i++) {
        r1.strings.push_back(data_ref.string_list_[i]);
    }

    std::string serialized;

    to_string(r1, serialized);
    from_string(r2, serialized);

    if (r1 != r2) {
        throw std::logic_error("cereal's case: deserialization failed");
    }
    std::cout << "cereal: size = " << serialized.size() << " bytes" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        serialized.clear();
        to_string(r1, serialized);
        from_string(r2, serialized);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "cereal: total time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        serialized.clear();
        to_string(r1, serialized);
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "cereal: serialize time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        from_string(r2, serialized);
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "cereal: unserialize time = " << duration << " milliseconds" << std::endl << std::endl;
}

void avro_serialization_test(size_t iterations, DataGenerator& data_ref)
{
    using namespace avro_test;

    Record r1, r2;

    for (size_t i = 0; i < data_ref.integer_list_.size(); i++) {
        r1.ids.push_back(data_ref.integer_list_[i]);
    }
    for (size_t i = 0; i < data_ref.string_list_.size(); i++) {
        r1.strings.push_back(data_ref.string_list_[i]);
    }
    std::unique_ptr<avro::OutputStream> out = avro::memoryOutputStream();
    avro::EncoderPtr encoder = avro::binaryEncoder();

    encoder->init(*out);
    avro::encode(*encoder, r1);

    auto serialized_size = out->byteCount();

    std::unique_ptr<avro::InputStream> in = avro::memoryInputStream(*out);
    avro::DecoderPtr decoder = avro::binaryDecoder();

    decoder->init(*in);
    avro::decode(*decoder, r2);

    if (r1.ids != r2.ids || r1.strings != r2.strings ||
        r2.ids.size() != data_ref.integer_list_.size() || r2.strings.size() != data_ref.string_list_.size()) {
        throw std::logic_error("avro's case: deserialization failed");
    }

    std::cout << "avro: size = " << serialized_size << " bytes" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        auto out = avro::memoryOutputStream();
        auto encoder = avro::binaryEncoder();
        encoder->init(*out);
        avro::encode(*encoder, r1);

        auto in = avro::memoryInputStream(*out);
        auto decoder = avro::binaryDecoder();
        decoder->init(*in);
        avro::decode(*decoder, r2);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "avro: total time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        auto out = avro::memoryOutputStream();
        auto encoder = avro::binaryEncoder();
        encoder->init(*out);
        avro::encode(*encoder, r1);
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "avro: serialize time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        auto in = avro::memoryInputStream(*out);
        auto decoder = avro::binaryDecoder();
        decoder->init(*in);
        avro::decode(*decoder, r2);
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "avro: unserialize time = " << duration << " milliseconds" << std::endl << std::endl;
}

void flatbuffers_serialization_test(size_t iterations, DataGenerator& data_ref)
{
    using namespace flatbuffers_test;

    std::vector<flatbuffers::Offset<flatbuffers::String>> strings;
    strings.reserve(data_ref.string_list_.size());

    flatbuffers::FlatBufferBuilder builder;
    for (size_t i = 0; i < data_ref.string_list_.size(); i++) {
        strings.push_back(builder.CreateString(data_ref.string_list_[i]));
    }

    auto ids_vec = builder.CreateVector(data_ref.integer_list_);
    auto strings_vec = builder.CreateVector(strings);
    auto r1 = CreateRecord(builder, ids_vec, strings_vec);

    builder.Finish(r1);

    auto p = reinterpret_cast<char*>(builder.GetBufferPointer());
    auto sz = builder.GetSize();
    std::vector<char> buf(p, p + sz);

    auto r2 = GetRecord(buf.data());
    if (r2->strings()->size() != data_ref.string_list_.size() || r2->ids()->size() != data_ref.integer_list_.size()) {
        throw std::logic_error("flatbuffer's case: deserialization failed");
    }

    std::cout << "flatbuffers: size = " << builder.GetSize() << " bytes" << std::endl;
    builder.ReleaseBufferPointer();

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        builder.Clear();
        strings.clear();
        for (size_t i = 0; i < data_ref.string_list_.size(); i++) {
            strings.push_back(builder.CreateString(data_ref.string_list_[i]));
        }
        auto ids_vec = builder.CreateVector(data_ref.integer_list_);
        auto strings_vec = builder.CreateVector(strings);
        auto r1 = CreateRecord(builder, ids_vec, strings_vec);
        builder.Finish(r1);

        auto p = reinterpret_cast<char*>(builder.GetBufferPointer());
        auto sz = builder.GetSize();
        std::vector<char> buf(p, p + sz);
        auto r2 = GetRecord(buf.data());
        (void)r2->ids()[0];

        builder.ReleaseBufferPointer();
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "flatbuffers: total time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        builder.Clear();
        strings.clear();
        for (size_t i = 0; i < data_ref.string_list_.size(); i++) {
            strings.push_back(builder.CreateString(data_ref.string_list_[i]));
        }
        auto ids_vec = builder.CreateVector(data_ref.integer_list_);
        auto strings_vec = builder.CreateVector(strings);
        auto r1 = CreateRecord(builder, ids_vec, strings_vec);
        builder.Finish(r1);

        builder.ReleaseBufferPointer();
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "flatbuffers: serialize time = " << duration << " milliseconds" << std::endl;

    builder.Clear();
    strings.clear();
    for (size_t i = 0; i < data_ref.string_list_.size(); i++) {
        strings.push_back(builder.CreateString(data_ref.string_list_[i]));
    }

    ids_vec = builder.CreateVector(data_ref.integer_list_);
    strings_vec = builder.CreateVector(strings);
    r1 = CreateRecord(builder, ids_vec, strings_vec);
    builder.Finish(r1);
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        auto p = reinterpret_cast<char*>(builder.GetBufferPointer());
        auto sz = builder.GetSize();
        std::vector<char> buf(p, p + sz);
        auto r2 = GetRecord(buf.data());
        (void)r2->ids()[0];
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "flatbuffers: unserialize time = " << duration << " milliseconds" << std::endl << std::endl;
}

void bson_serialization_test(size_t iterations, DataGenerator& data_ref)
{
    bson_t ints, strings;
    bson_t* bson;
    uint8_t *buf = NULL;
    size_t buflen = 0;

    bson_writer_t* writer = bson_writer_new(&buf, &buflen, 0, bson_realloc_ctx, NULL);
    bson_writer_begin (writer, &bson);
    bson_append_array_begin(bson, "ints", -1, &ints);
    for (size_t i = 0; i < data_ref.integer_list_.size(); i++) {
        bson_append_int32(&ints, "0", -1, data_ref.integer_list_[i]);
    }
    bson_append_array_end(bson, &ints);

    bson_append_array_begin(bson, "strings", -1, &strings);
    for (size_t i = 0; i < data_ref.string_list_.size(); i++) {
        bson_append_utf8(&strings, "0", -1, data_ref.string_list_[i].c_str(), data_ref.string_list_[i].size());
    }
    bson_append_array_end(bson, &strings);
    bson_writer_end (writer);

    bson_iter_t iter;
    bson_iter_t sub_iter;

    unsigned int count_strings = 0, count_ints = 0;
    bson_reader_t* reader = bson_reader_new_from_data(buf, buflen);
    bool eof;
    const bson_t* bson_read;
    bson_read = bson_reader_read (reader, &eof);
    if (bson_iter_init_find (&iter, bson_read, "ints") &&
            (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
            bson_iter_recurse (&iter, &sub_iter)) {
        while (bson_iter_next (&sub_iter)) {
            //printf("Found key \"%d\" in sub document.\n", bson_iter_int32(&sub_iter));
            count_ints++;
        }
    }
    if (bson_iter_init_find (&iter, bson_read, "strings") &&
            (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
            bson_iter_recurse (&iter, &sub_iter)) {
        while (bson_iter_next (&sub_iter)) {
            //printf("Found key \"%s\" in sub document.\n", bson_iter_utf8(&sub_iter, NULL));
            count_strings++;
        }
    }
    if (count_strings != data_ref.string_list_.size() || count_ints != data_ref.integer_list_.size()) {
        throw std::logic_error("bson's case: deserialization failed");
    }
    std::cout << "bson: size = " << bson_read->len << " bytes" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        uint8_t *buf_iter = NULL;
        size_t buflen_iter = 0;
        bson_t* bson_iter;
        bson_t ints_iter, strings_iter;

        bson_writer_t* writer_iter = bson_writer_new(&buf_iter, &buflen_iter, 0, bson_realloc_ctx, NULL);
        bson_writer_begin (writer_iter, &bson_iter);

        bson_append_array_begin(bson_iter, "ints", -1, &ints_iter);
        for (size_t i = 0; i < data_ref.integer_list_.size(); i++)
            bson_append_int32(&ints_iter, "0", -1, data_ref.integer_list_[i]);
        bson_append_array_end(bson_iter, &ints_iter);
        bson_append_array_begin(bson_iter, "strings", -1, &strings_iter);
        for (size_t i = 0; i < data_ref.string_list_.size(); i++)
            bson_append_utf8(&strings_iter, "0", -1, data_ref.string_list_[i].c_str(), data_ref.string_list_[i].size());
        bson_append_array_end(bson_iter, &strings_iter);
        bson_writer_end(writer_iter);

        bson_reader_t* reader_iter = bson_reader_new_from_data(buf_iter, buflen_iter);
        const bson_t* bson_read_iter;
        bson_read_iter = bson_reader_read (reader_iter, &eof);
        if (bson_iter_init_find (&iter, bson_read_iter, "ints") &&
            (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
            bson_iter_recurse (&iter, &sub_iter)) {
            bson_iter_next (&sub_iter);
            bson_iter_int32(&sub_iter);
        }
        if (bson_iter_init_find (&iter, bson_read_iter, "strings") &&
            (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
            bson_iter_recurse (&iter, &sub_iter)) {
            bson_iter_next (&sub_iter);
            bson_iter_utf8(&sub_iter, NULL);
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "bson: total time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        uint8_t *buf_iter = NULL;
        size_t buflen_iter = 0;
        bson_t* bson_iter;
        bson_t ints_iter, strings_iter;

        bson_writer_t* writer_iter = bson_writer_new(&buf_iter, &buflen_iter, 0, bson_realloc_ctx, NULL);
        bson_writer_begin (writer_iter, &bson_iter);

        bson_append_array_begin(bson_iter, "ints", -1, &ints_iter);
        for (size_t i = 0; i < data_ref.integer_list_.size(); i++)
            bson_append_int32(&ints_iter, "0", -1, data_ref.integer_list_[i]);
        bson_append_array_end(bson_iter, &ints_iter);
        bson_append_array_begin(bson_iter, "strings", -1, &strings_iter);
        for (size_t i = 0; i < data_ref.string_list_.size(); i++)
            bson_append_utf8(&strings_iter, "0", -1, data_ref.string_list_[i].c_str(), data_ref.string_list_[i].size());
        bson_append_array_end(bson_iter, &strings_iter);
        bson_writer_end(writer_iter);
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "bson: serialize time = " << duration << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        bson_reader_t* reader_iter = bson_reader_new_from_data(buf, buflen);
        const bson_t* bson_read_iter;
        bson_read_iter = bson_reader_read (reader_iter, &eof);
        if (bson_iter_init_find (&iter, bson_read_iter, "ints") &&
            (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
            bson_iter_recurse (&iter, &sub_iter)) {
            bson_iter_next (&sub_iter);
            bson_iter_int32(&sub_iter);
        }
        if (bson_iter_init_find (&iter, bson_read_iter, "strings") &&
            (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
            bson_iter_recurse (&iter, &sub_iter)) {
            bson_iter_next (&sub_iter);
            bson_iter_utf8(&sub_iter, NULL);
        }
    }
    finish = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "bson: unserialize time = " << duration << " milliseconds" << std::endl;
}

int main(int argc, char **argv)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    if (argc < 3) {
        std::cout << "usage: " << argv[0] << " N DATA_SIZE [thrift-binary thrift-compact protobuf boost msgpack "
                "cereal avro capnproto flatbuffers bson]";
        std::cout << std::endl << std::endl;
        std::cout << "arguments: " << std::endl;
        std::cout << " N  -- number of iterations on the same size" << std::endl;
        std::cout << " DATA_SIZE -- Number of elements in each data type" << std::endl << std::endl;
        return EXIT_SUCCESS;
    }

    size_t iterations;
    unsigned int data_size;
    try {
        iterations = boost::lexical_cast<size_t>(argv[1]);
        data_size = boost::lexical_cast<unsigned int>(argv[2]);
    } catch (std::exception &exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        std::cerr << "First and second positional argument must be an integer." << std::endl;
        return EXIT_FAILURE;
    }

    std::set<std::string> names;
    if (argc > 3) {
        for (int i = 3; i < argc; i++) {
            names.insert(argv[i]);
        }
    }

    DataGenerator data(data_size);
    std::cout << "unserialized data has " << (sizeof(data.integer_list_[0]) * data.integer_list_.size() +
            data.string_list_[0].size() * data.string_list_.size()) << " bytes" << std::endl;
    std::cout << "performing " << iterations << " iterations" << std::endl << std::endl;

    try {
        if (names.empty() || names.find("thrift-binary") != names.end()) {
            thrift_serialization_test(iterations, data, ThriftSerializationProto::Binary);
        }

        if (names.empty() || names.find("thrift-compact") != names.end()) {
            thrift_serialization_test(iterations, data, ThriftSerializationProto::Compact);
        }

        if (names.empty() || names.find("protobuf") != names.end()) {
            protobuf_serialization_test(iterations, data);
        }

        if (names.empty() || names.find("capnproto") != names.end()) {
            capnproto_serialization_test(iterations, data);
        }

        if (names.empty() || names.find("boost") != names.end()) {
            boost_serialization_test(iterations, data);
        }

        if (names.empty() || names.find("msgpack") != names.end()) {
            msgpack_serialization_test(iterations, data);
        }

        if (names.empty() || names.find("cereal") != names.end()) {
            cereal_serialization_test(iterations, data);
        }

        if (names.empty() || names.find("avro") != names.end()) {
            avro_serialization_test(iterations, data);
        }

        if (names.empty() || names.find("flatbuffers") != names.end()) {
            flatbuffers_serialization_test(iterations, data);
        }

        if (names.empty() || names.find("bson") != names.end()) {
            bson_serialization_test(iterations, data);
        }
    } catch (std::exception &exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    google::protobuf::ShutdownProtobufLibrary();

    return EXIT_SUCCESS;
}
