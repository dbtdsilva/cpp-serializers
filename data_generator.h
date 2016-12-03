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
    const std::vector<int64_t> integer_list_;
    const std::vector<double> double_list_;

    static std::string generate_random_string(unsigned int size);
private:
    static const std::string ALPHANUM;
    static const int RANGE;

    std::vector<int64_t> generate_vector_int64(unsigned int size);
    std::vector<double> generate_vector_double(unsigned int size);
    std::vector<std::string> generate_vector_string(unsigned int size);
};

#endif