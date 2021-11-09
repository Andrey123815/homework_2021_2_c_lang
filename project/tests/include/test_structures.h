// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_TESTS_INCLUDE_TEST_STRUCTURES_H_
#define PROJECT_TESTS_INCLUDE_TEST_STRUCTURES_H_

#include "../../include/structures.h"

typedef struct {
    int flag;
    Matrix* M;
    const char* function_name;
} parameters_t;

typedef enum {
    ONE_THREAD_MODE,
    MULTI_THREAD_MODE
} flag_mode;

typedef struct {
    int data_row_count[2];
    int data_col_count[2];
} data_size_t;


#endif  // PROJECT_TESTS_INCLUDE_TEST_STRUCTURES_H_
