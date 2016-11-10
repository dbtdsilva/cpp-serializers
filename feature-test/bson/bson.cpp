#include "bson.h"
#include <bson.h>
#include <iostream>

#include "../data.hpp"

using namespace std;

BsonTest::BsonTest() : FeatureTestObject(string("Bson")) {

}

bool BsonTest::check_missing_field() {
    bson_t bson, ints, strings;
    bson_init(&bson);
    bson_iter_t iter;
    bson_iter_t sub_iter;

    bson_append_array_begin(&bson, "ints", -1, &ints);
    for (size_t i = 0; i < kIntegers.size(); i++)
        bson_append_int32(&ints, "0", -1, kIntegers[i]);
    bson_append_array_end(&bson, &ints);

    bson_append_array_begin(&bson, "strings", -1, &strings);
    for (size_t i = 0; i < kStringsCount; i++)
        bson_append_utf8(&strings, "0", -1, kStringValue.c_str(), kStringValue.size());
    bson_append_array_end(&bson, &strings);

    unsigned int counter = 0;
    const char * recvString;
    if (bson_iter_init_find (&iter, &bson, "strings") &&
        (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
        bson_iter_recurse (&iter, &sub_iter)) {
        while (bson_iter_next (&sub_iter)) {
            recvString = bson_iter_utf8(&sub_iter, NULL);
            if (string(recvString) != kStringValue)
                return false;
            counter++;
        }
    }
    if (counter != kStringsCount)
        return false;

    bson_destroy(&bson);
    return true;
}

bool BsonTest::check_new_field() {
    bson_t bson, ints, strings;
    bson_init(&bson);
    bson_iter_t iter;
    bson_iter_t sub_iter;

    bson_append_int64(&bson, "int", -1, 10);
    bson_append_array_begin(&bson, "ints", -1, &ints);
    for (size_t i = 0; i < kIntegers.size(); i++)
        bson_append_int32(&ints, "0", -1, kIntegers[i]);
    bson_append_array_end(&bson, &ints);

    bson_append_array_begin(&bson, "strings", -1, &strings);
    for (size_t i = 0; i < kStringsCount; i++)
        bson_append_utf8(&strings, "0", -1, kStringValue.c_str(), kStringValue.size());
    bson_append_array_end(&bson, &strings);

    unsigned int counter = 0;
    int recvInt;
    if (bson_iter_init_find(&iter, &bson, "ints") &&
        (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
        bson_iter_recurse (&iter, &sub_iter)) {
        while (bson_iter_next (&sub_iter)) {
            recvInt = bson_iter_int32(&sub_iter);
            if (kIntegers.at(counter) != recvInt)
                return false;
            counter++;
        }
    }
    if (counter != kIntegers.size())
        return false;

    counter = 0;
    const char * recvString;
    if (bson_iter_init_find (&iter, &bson, "strings") &&
        (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
        bson_iter_recurse (&iter, &sub_iter)) {
        while (bson_iter_next (&sub_iter)) {
            recvString = bson_iter_utf8(&sub_iter, NULL);
            if (string(recvString) != kStringValue)
                return false;
            counter++;
        }
    }

    if (counter != kStringsCount)
        return false;

    bson_destroy(&bson);
    return true;
}

bool BsonTest::check_types_inheritance() {
    bson_t bson, ints, strings;
    bson_init(&bson);
    bson_iter_t iter;
    bson_iter_t sub_iter;

    bson_append_array_begin(&bson, "ints", -1, &ints);
    for (size_t i = 0; i < kIntegers.size(); i++)
        bson_append_double(&ints, "0", -1, kIntegers[i]);
    bson_append_array_end(&bson, &ints);

    bson_append_array_begin(&bson, "strings", -1, &strings);
    for (size_t i = 0; i < kStringsCount; i++)
        bson_append_utf8(&strings, "0", -1, kStringValue.c_str(), kStringValue.size());
    bson_append_array_end(&bson, &strings);

    unsigned int counter = 0;
    int recvInt;
    if (bson_iter_init_find (&iter, &bson, "ints") &&
        (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
        bson_iter_recurse (&iter, &sub_iter)) {
        while (bson_iter_next (&sub_iter)) {
            recvInt = bson_iter_int32(&sub_iter);
            if (kIntegers.at(counter) != recvInt)
                return false;
            counter++;
        }
    }
    if (counter != kIntegers.size())
        return false;

    counter = 0;
    const char * recvString;
    if (bson_iter_init_find (&iter, &bson, "strings") &&
        (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
        bson_iter_recurse (&iter, &sub_iter)) {
        while (bson_iter_next (&sub_iter)) {
            recvString = bson_iter_utf8(&sub_iter, NULL);
            if (string(recvString) != kStringValue)
                return false;
            counter++;
        }
    }
    if (counter != kStringsCount)
        return false;

    bson_destroy(&bson);
    return true;
}

bool BsonTest::check_field_names() {
    bson_t bson, ints, strings;
    bson_init(&bson);
    bson_iter_t iter;
    bson_iter_t sub_iter;

    bson_append_array_begin(&bson, "ints_rem", -1, &ints);
    for (size_t i = 0; i < kIntegers.size(); i++)
        bson_append_int32(&ints, "0", -1, kIntegers[i]);
    bson_append_array_end(&bson, &ints);

    bson_append_array_begin(&bson, "strings_rem", -1, &strings);
    for (size_t i = 0; i < kStringsCount; i++)
        bson_append_utf8(&strings, "0", -1, kStringValue.c_str(), kStringValue.size());
    bson_append_array_end(&bson, &strings);

    unsigned int counter = 0;
    int recvInt;
    if (bson_iter_init_find (&iter, &bson, "ints") &&
        (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
        bson_iter_recurse (&iter, &sub_iter)) {
        while (bson_iter_next (&sub_iter)) {
            recvInt = bson_iter_int32(&sub_iter);
            if (kIntegers.at(counter) != recvInt)
                return false;
            counter++;
        }
    }
    if (counter != kIntegers.size())
        return false;

    counter = 0;
    const char * recvString;
    if (bson_iter_init_find (&iter, &bson, "strings") &&
        (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
        bson_iter_recurse (&iter, &sub_iter)) {
        while (bson_iter_next (&sub_iter)) {
            recvString = bson_iter_utf8(&sub_iter, NULL);
            if (string(recvString) != kStringValue)
                return false;
            counter++;
        }
    }
    if (counter != kStringsCount)
        return false;

    bson_destroy(&bson);
    return true;
}