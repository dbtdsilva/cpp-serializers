namespace cpp thrift_test

struct Record {
    1: required list<i64>       ids,
    2: required list<string>    strings
}

struct RecordMissing {
    1: required list<i64>       ids
}

struct RecordNewField {
    1: required list<i64>       ids,
    2: required list<string>    strings,
    3: required i64             id
}

struct RecordRename {
    1: required list<i64>       ids_rem,
    2: required list<string>    strings_rem
}

struct RecordTypes {
    1: required list<double>    ids,
    2: required list<string>    strings
}