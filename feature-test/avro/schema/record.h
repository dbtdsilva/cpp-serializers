/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef _HOME_MYRDDIN_DOCUMENTS_CPP_SERIALIZERS_FEATURE_TEST_AVRO_SCHEMA_RECORD_H_1251640384__H_
#define _HOME_MYRDDIN_DOCUMENTS_CPP_SERIALIZERS_FEATURE_TEST_AVRO_SCHEMA_RECORD_H_1251640384__H_


#include <sstream>
#include "boost/any.hpp"
#include "avro/Specific.hh"
#include "avro/Encoder.hh"
#include "avro/Decoder.hh"

struct Record {
    std::vector<int64_t > ids;
    std::vector<std::string > strings;
    Record() :
        ids(std::vector<int64_t >()),
        strings(std::vector<std::string >())
        { }
};

struct RecordMissing {
    std::vector<std::string > strings;
    RecordMissing() :
        strings(std::vector<std::string >())
        { }
};

struct RecordNewField {
    std::vector<int64_t > ids;
    std::vector<std::string > strings;
    int64_t id;
    RecordNewField() :
        ids(std::vector<int64_t >()),
        strings(std::vector<std::string >()),
        id(int64_t())
        { }
};

struct RecordRename {
    std::vector<int64_t > ids_rem;
    std::vector<std::string > strings_rem;
    RecordRename() :
        ids_rem(std::vector<int64_t >()),
        strings_rem(std::vector<std::string >())
        { }
};

struct RecordTypeInheritance {
    std::vector<double > ids;
    std::vector<std::string > strings;
    RecordTypeInheritance() :
        ids(std::vector<double >()),
        strings(std::vector<std::string >())
        { }
};

struct _test_json_Union__0__ {
private:
    size_t idx_;
    boost::any value_;
public:
    size_t idx() const { return idx_; }
    Record get_Record() const;
    void set_Record(const Record& v);
    RecordMissing get_RecordMissing() const;
    void set_RecordMissing(const RecordMissing& v);
    RecordNewField get_RecordNewField() const;
    void set_RecordNewField(const RecordNewField& v);
    RecordRename get_RecordRename() const;
    void set_RecordRename(const RecordRename& v);
    RecordTypeInheritance get_RecordTypeInheritance() const;
    void set_RecordTypeInheritance(const RecordTypeInheritance& v);
    _test_json_Union__0__();
};

inline
Record _test_json_Union__0__::get_Record() const {
    if (idx_ != 0) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<Record >(value_);
}

inline
void _test_json_Union__0__::set_Record(const Record& v) {
    idx_ = 0;
    value_ = v;
}

inline
RecordMissing _test_json_Union__0__::get_RecordMissing() const {
    if (idx_ != 1) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<RecordMissing >(value_);
}

inline
void _test_json_Union__0__::set_RecordMissing(const RecordMissing& v) {
    idx_ = 1;
    value_ = v;
}

inline
RecordNewField _test_json_Union__0__::get_RecordNewField() const {
    if (idx_ != 2) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<RecordNewField >(value_);
}

inline
void _test_json_Union__0__::set_RecordNewField(const RecordNewField& v) {
    idx_ = 2;
    value_ = v;
}

inline
RecordRename _test_json_Union__0__::get_RecordRename() const {
    if (idx_ != 3) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<RecordRename >(value_);
}

inline
void _test_json_Union__0__::set_RecordRename(const RecordRename& v) {
    idx_ = 3;
    value_ = v;
}

inline
RecordTypeInheritance _test_json_Union__0__::get_RecordTypeInheritance() const {
    if (idx_ != 4) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<RecordTypeInheritance >(value_);
}

inline
void _test_json_Union__0__::set_RecordTypeInheritance(const RecordTypeInheritance& v) {
    idx_ = 4;
    value_ = v;
}

inline _test_json_Union__0__::_test_json_Union__0__() : idx_(0), value_(Record()) { }
namespace avro {
template<> struct codec_traits<Record> {
    static void encode(Encoder& e, const Record& v) {
        avro::encode(e, v.ids);
        avro::encode(e, v.strings);
    }
    static void decode(Decoder& d, Record& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.ids);
                    break;
                case 1:
                    avro::decode(d, v.strings);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.ids);
            avro::decode(d, v.strings);
        }
    }
};

template<> struct codec_traits<RecordMissing> {
    static void encode(Encoder& e, const RecordMissing& v) {
        avro::encode(e, v.strings);
    }
    static void decode(Decoder& d, RecordMissing& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.strings);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.strings);
        }
    }
};

template<> struct codec_traits<RecordNewField> {
    static void encode(Encoder& e, const RecordNewField& v) {
        avro::encode(e, v.ids);
        avro::encode(e, v.strings);
        avro::encode(e, v.id);
    }
    static void decode(Decoder& d, RecordNewField& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.ids);
                    break;
                case 1:
                    avro::decode(d, v.strings);
                    break;
                case 2:
                    avro::decode(d, v.id);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.ids);
            avro::decode(d, v.strings);
            avro::decode(d, v.id);
        }
    }
};

template<> struct codec_traits<RecordRename> {
    static void encode(Encoder& e, const RecordRename& v) {
        avro::encode(e, v.ids_rem);
        avro::encode(e, v.strings_rem);
    }
    static void decode(Decoder& d, RecordRename& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.ids_rem);
                    break;
                case 1:
                    avro::decode(d, v.strings_rem);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.ids_rem);
            avro::decode(d, v.strings_rem);
        }
    }
};

template<> struct codec_traits<RecordTypeInheritance> {
    static void encode(Encoder& e, const RecordTypeInheritance& v) {
        avro::encode(e, v.ids);
        avro::encode(e, v.strings);
    }
    static void decode(Decoder& d, RecordTypeInheritance& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.ids);
                    break;
                case 1:
                    avro::decode(d, v.strings);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.ids);
            avro::decode(d, v.strings);
        }
    }
};

template<> struct codec_traits<_test_json_Union__0__> {
    static void encode(Encoder& e, _test_json_Union__0__ v) {
        e.encodeUnionIndex(v.idx());
        switch (v.idx()) {
        case 0:
            avro::encode(e, v.get_Record());
            break;
        case 1:
            avro::encode(e, v.get_RecordMissing());
            break;
        case 2:
            avro::encode(e, v.get_RecordNewField());
            break;
        case 3:
            avro::encode(e, v.get_RecordRename());
            break;
        case 4:
            avro::encode(e, v.get_RecordTypeInheritance());
            break;
        }
    }
    static void decode(Decoder& d, _test_json_Union__0__& v) {
        size_t n = d.decodeUnionIndex();
        if (n >= 5) { throw avro::Exception("Union index too big"); }
        switch (n) {
        case 0:
            {
                Record vv;
                avro::decode(d, vv);
                v.set_Record(vv);
            }
            break;
        case 1:
            {
                RecordMissing vv;
                avro::decode(d, vv);
                v.set_RecordMissing(vv);
            }
            break;
        case 2:
            {
                RecordNewField vv;
                avro::decode(d, vv);
                v.set_RecordNewField(vv);
            }
            break;
        case 3:
            {
                RecordRename vv;
                avro::decode(d, vv);
                v.set_RecordRename(vv);
            }
            break;
        case 4:
            {
                RecordTypeInheritance vv;
                avro::decode(d, vv);
                v.set_RecordTypeInheritance(vv);
            }
            break;
        }
    }
};

}
#endif
