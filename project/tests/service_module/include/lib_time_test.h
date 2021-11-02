// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_TESTS_SERVICE_MODULE_INCLUDE_LIB_TIME_TEST_H_
#define PROJECT_TESTS_SERVICE_MODULE_INCLUDE_LIB_TIME_TEST_H_

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "matrix_one_thread.h"
#include "matrix_multi_thread.h"
#include "test_structures.h"
#include "lib_generator.h"

#define CREATE_FROM_FILE 1
#define CREATE 2
#define TRANSP 3


Matrix* get_handler(int flag, data_size_t* data_size, int number_iteration);

int time_test(parameters_t* params, flag_mode mode);


#endif  // PROJECT_TESTS_SERVICE_MODULE_INCLUDE_LIB_TIME_TEST_H_
