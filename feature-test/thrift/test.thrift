namespace cpp thrift_test

struct Record {
    1: required list<i32>       ids,
    2: required list<string>    strings
}

struct RecordMissing {
    2: required list<string>    strings
}

struct RecordNewField {
    1: required list<i32>       ids,
    2: required list<string>    strings,
    3: optional i32             id
}

struct RecordRename {
    1: required list<i32>       ids_rem,
    2: required list<string>    strings_rem
}

struct RecordTypes {
    1: required list<i64>       ids,
    2: required list<string>    strings
}