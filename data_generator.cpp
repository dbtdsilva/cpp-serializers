#include "data_generator.h"
#include <random>
#include <ctime>
#include <iostream>

const std::string DataGenerator::ALPHANUM("0123456789!@#$%^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
const int DataGenerator::RANGE(50000);

DataGenerator::DataGenerator(unsigned int total_values) : total_values_(total_values),
                                                          string_list_(generate_vector_string(total_values)),
                                                          integer_list_(generate_vector_int64(total_values)),
                                                          double_list_(generate_vector_double(total_values))
{
    srand(time(0));
}

std::string DataGenerator::generate_random_string(unsigned int size) {
    std::string value;
    for (unsigned int i = 0; i < size; i++) {
        value += ALPHANUM[rand() % ALPHANUM.size()];
    }
    return value;
}

std::vector<int64_t> DataGenerator::generate_vector_int64(unsigned int size) {
    std::vector<int64_t> list;
    std::uniform_int_distribution<int64_t> unif_int(-RANGE, RANGE);
    std::default_random_engine re_int64;
    for (unsigned int i = 0; i < size; i++) {
        list.push_back(unif_int(re_int64));
    }
    return list;
}

std::vector<double> DataGenerator::generate_vector_double(unsigned int size) {
    std::vector<double> list;
    std::uniform_real_distribution<double> unif_double(-RANGE, RANGE);
    std::default_random_engine re_double;
    for (unsigned int i = 0; i < size; i++) {
        list.push_back(unif_double(re_double));
    }
    return list;
}

std::vector<std::string> DataGenerator::generate_vector_string(unsigned int size) {
    std::vector<std::string> list;
    for (unsigned int i = 0; i < size; i++) {
        list.push_back(DataGenerator::generate_random_string(sizeof(int64_t)));
    }
    return list;
}