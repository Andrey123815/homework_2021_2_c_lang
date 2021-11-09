// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_TESTS_SERVICE_MODULE_INCLUDE_LIB_STRESS_TEST_H_
#define PROJECT_TESTS_SERVICE_MODULE_INCLUDE_LIB_STRESS_TEST_H_

#include <string.h>
#include <stdio.h>

#include "../../../include/matrix_processing.h"
#include "test_structures.h"


int write_results_to_file(const char* path, const Matrix* M);

int read_and_compare();


#endif  // PROJECT_TESTS_SERVICE_MODULE_INCLUDE_LIB_STRESS_TEST_H_
