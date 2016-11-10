@0xe1e66843d9fb6aa1;

struct Record {
    ids @0 :List(Int64);
    strings @1 :List(Text);
}

struct RecordMissing {
    strings @0 :List(Text);
}

struct RecordNewField {
    ids @0 :List(Int64);
    strings @1 :List(Text);
    id @2 :Int64;
}

struct RecordRename {
    idsrem @0 :List(Int64);
    stringsrem @1 :List(Text);
}

struct RecordTypeInheritance {
    ids @0 :List(Float64);
    strings @1 :List(Text);
}
