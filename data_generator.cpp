#include "data_generator.h"
#include <random>
#include <ctime>
#include <limits>
#include <stdexcept>

const std::string DataGenerator::alphanum("0123456789!@#$%^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

std::vector<int64_t> generate_vector_int64(unsigned int size);
std::vector<double> generate_vector_double(unsigned int size);
std::vector<std::string> generate_vector_string(unsigned int size);

DataGenerator::DataGenerator(unsigned int total_values) : total_values_(total_values),
                                                          string_list_(generate_vector_string(total_values)),
                                                          integer_list(generate_vector_int64(total_values)),
                                                          double_list(generate_vector_double(total_values))
{
}



std::string DataGenerator::generate_random_string(unsigned int size) {
    std::string value;
    for (unsigned int i = 0; i < size; i++) {
        value += alphanum[rand() % alphanum.size()];
    }
    return value;
}

std::vector<int64_t> generate_vector_int64(unsigned int size) {
    std::vector<int64_t> list;
    std::uniform_int_distribution<int64_t> unif_int(std::numeric_limits<int64_t>::min(),
                                                     std::numeric_limits<int64_t>::max());
    std::default_random_engine re_int64;
    for (unsigned int i = 0; i < size; i++) {
        list.push_back(unif_int(re_int64));
    }
    return list;
}

std::vector<double> generate_vector_double(unsigned int size) {
    std::vector<double> list;
    std::uniform_real_distribution<double> unif_double(std::numeric_limits<double>::min(),
                                                    std::numeric_limits<double>::max());
    std::default_random_engine re_double;
    for (unsigned int i = 0; i < size; i++) {
        list.push_back(unif_double(re_double));
    }
    return list;
}

std::vector<std::string> generate_vector_string(unsigned int size) {
    srand(time(0));
    std::vector<std::string> list;
    for (unsigned int i = 0; i < size; i++) {
        list.push_back(DataGenerator::generate_random_string(sizeof(int64_t)));
    }
    return list;
}