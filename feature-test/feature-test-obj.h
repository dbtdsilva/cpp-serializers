#ifndef FEATURE_TEST_OBJ_H
#define FEATURE_TEST_OBJ_H

#include <string>

class FeatureTestObject {
public:
    FeatureTestObject(std::string name) : name_(name) {};
    
    // This function checks if a protocol is still able to handle missing fields
    virtual bool check_missing_field() = 0;
    // This function checks if a protocol is able to ignore a new field in the schema
    virtual bool check_new_field() = 0;
    // This function checks for types change (e.g. int should be able to change to float)
    virtual bool check_types_inheritance() = 0;
    // This function checks for if a field is able to change it's name or not
    virtual bool check_field_names() = 0;

    std::string& get_name() { return name_; };
private:
    std::string name_;
};

#endif