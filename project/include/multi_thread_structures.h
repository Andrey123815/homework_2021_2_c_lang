// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_INCLUDE_MULTI_THREAD_STRUCTURES_H_
#define PROJECT_INCLUDE_MULTI_THREAD_STRUCTURES_H_

#define DELETE -1
#define SUCCESS NULL

#include <stdlib.h>

typedef struct Matrix {
    size_t row;
    size_t col;
    double** matr;
} Matrix;

typedef struct {
    const char* path_to_file;
    Matrix* M;
    Matrix* New_M;
    unsigned int start_row;
    unsigned int final_row;
    size_t row_size;
    const int* source_array;
} matrix_data_t;

typedef struct {
    unsigned int need_count_threads;
    unsigned int row_count_to_thread;
    unsigned int rows_count;
} opt_thread_count_t;

typedef struct {
    Matrix* M;
    Matrix* New_M;
    const int *source_array;
    const char* path_file;
    int flag_work_with_file;
} params_t;


#endif  // PROJECT_INCLUDE_MULTI_THREAD_STRUCTURES_H_
