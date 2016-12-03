#ifndef __DATA_GENERATOR_H_INCLUDED__
#define __DATA_GENERATOR_H_INCLUDED__

#include <string>
#include <vector>
#include <stdint.h>

class DataGenerator {
public:
    DataGenerator(unsigned int total_values);

    const unsigned int total_values_;

    const std::vector<std::string> string_list_;
    const std::vector<int64_t> integer_list;
    const std::vector<double> double_list;

    static std::string generate_random_string(unsigned int size);
private:
    static const std::string alphanum;
};

#endif