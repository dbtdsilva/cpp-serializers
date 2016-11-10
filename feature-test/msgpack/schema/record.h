#ifndef MSGPACK_RECORD_H
#define MSGPACK_RECORD_H

#include <vector>
#include <string>

#include <stdint.h>
#include <msgpack.hpp>

class Record {
public:
    std::vector<int32_t> ids;
    std::vector<std::string> strings;

    MSGPACK_DEFINE(ids, strings);
};

class RecordMissing {
public:
    std::vector<std::string> strings;

    MSGPACK_DEFINE(strings);
};

class RecordNewField {
public:
    std::vector<int32_t> ids;
    std::vector<std::string> strings;
    int32_t id;

    MSGPACK_DEFINE(ids, strings, id);
};

class RecordRename {
public:
    std::vector<int32_t> ids_rem;
    std::vector<std::string> strings_rem;

    MSGPACK_DEFINE(ids_rem, strings_rem);
};

class RecordTypeInheritance {
public:
    std::vector<double> ids;
    std::vector<std::string> strings;

    MSGPACK_DEFINE(ids, strings);
};

#endif
