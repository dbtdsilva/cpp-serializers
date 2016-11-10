#ifndef CPP_SERIALIZERS_TEST_H_H
#define CPP_SERIALIZERS_TEST_H_H

#include <vector>
#include <string>
#include <sstream>

#include <stdint.h>

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

typedef std::vector<int64_t>     Integers;
typedef std::vector<std::string> Strings;

class Record {
public:
    Integers ids;
    Strings  strings;
private:
    friend class cereal::access;
    template<typename Archive>
    void serialize(Archive &ar) {
        ar & ids;
        ar & strings;
    }
};

class RecordMissing {
public:
    Strings strings;
private:
    friend class cereal::access;
    template<typename Archive>
    void serialize(Archive &ar) {
        ar & strings;
    }
};

class RecordNewField {
public:
    Integers ids;
    Strings  strings;
    int64_t  id;
private:
    friend class cereal::access;
    template<typename Archive>
    void serialize(Archive &ar) {
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
    friend class cereal::access;
    template<typename Archive>
    void serialize(Archive &ar) {
        ar & ids_rem;
        ar & strings_rem;
    }
};

class RecordTypeInheritance {
public:
    std::vector<int32_t> ids;
    Strings  strings;
private:
    friend class cereal::access;
    template<typename Archive>
    void serialize(Archive &ar) {
        ar & ids;
        ar & strings;
    }
};

#endif //CPP_SERIALIZERS_TEST_H_H
