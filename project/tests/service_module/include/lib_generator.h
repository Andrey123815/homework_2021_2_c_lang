// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_TESTS_SERVICE_MODULE_INCLUDE_LIB_GENERATOR_H_
#define PROJECT_TESTS_SERVICE_MODULE_INCLUDE_LIB_GENERATOR_H_

#include <stdio.h>
#include "test_structures.h"


void generate_file(const char* path_file, data_size_t* data_size, int number_iteration);

int* generate_source_array(int rows, int cols);


#endif  // PROJECT_TESTS_SERVICE_MODULE_INCLUDE_LIB_GENERATOR_H_
