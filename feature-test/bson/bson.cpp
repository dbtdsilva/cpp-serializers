#include "bson.h"
#include <string>
#include <bson.h>

#include "../data.hpp"

using namespace std;

BsonTest::BsonTest() : FeatureTestObject(string("Bson")) {

}

bool BsonTest::check_missing_field() {
    bson_t bson, ints, strings;
    bson_init(&bson);

    bson_append_array_begin(&bson, "ints", -1, &ints);
    for (size_t i = 0; i < kIntegers.size(); i++)
        bson_append_int32(&ints, "0", -1, kIntegers[i]);
    bson_append_array_end(&bson, &ints);

    bson_append_array_begin(&bson, "strings", -1, &strings);
    for (size_t i = 0; i < kStringsCount; i++)
        bson_append_utf8(&strings, "0", -1, kStringValue.c_str(), kStringValue.size());
    bson_append_array_end(&bson, &strings);

    if (bson_iter_init_find (&iter, &bson, "ints") &&
        (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
        bson_iter_recurse (&iter, &sub_iter)) {
        bson_iter_next (&sub_iter);
        bson_iter_int32(&sub_iter);
    }
    if (bson_iter_init_find (&iter, &bson, "strings") &&
        (BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
        bson_iter_recurse (&iter, &sub_iter)) {
        bson_iter_next (&sub_iter);
        bson_iter_utf8(&sub_iter, NULL);
    }
    bson_destroy(&bson);
}

bool BsonTest::check_new_field() {
    return false;
}

bool BsonTest::check_types_inheritance() {
    return false;
}

bool BsonTest::check_field_names() {
    return false;
}