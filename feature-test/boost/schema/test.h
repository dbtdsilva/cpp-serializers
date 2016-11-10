#ifndef CPP_SERIALIZERS_TEST_H_H
#define CPP_SERIALIZERS_TEST_H_H

#include <vector>
#include <string>
#include <sstream>

#include <stdint.h>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <boost/serialization/version.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/tracking.hpp>

#include <boost/version.hpp>

typedef std::vector<int64_t>     Integers;
typedef std::vector<std::string> Strings;

class Record {
public:
    Integers ids;
    Strings  strings;
private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & ids;
        ar & strings;
    }
};

class RecordMissing {
public:
    Strings strings;
private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & strings;
    }
};

class RecordNewField {
public:
    Integers ids;
    Strings  strings;
    int64_t  id;
private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & ids;
        ar & strings;
        ar & id;
    }
};

class RecordRename {
public:
    Integers ids_rem;
    Strings  strings_rem;
private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & ids_rem;
        ar & strings_rem;
    }
};

class RecordTypeInheritance {
public:
    std::vector<int32_t> ids;
    Strings  strings;
private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & ids;
        ar & strings;
    }
};

#endif //CPP_SERIALIZERS_TEST_H_H
