// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_INCLUDE_MATRIX_SERVICE_THREAD_H_
#define PROJECT_INCLUDE_MATRIX_SERVICE_THREAD_H_

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "../include/structures.h"

// Service operations
Matrix* multi_thread_data_processing(void* func, params_t* params);

void* multi_read_from_file(void* data);
void* multi_calloc_and_check(void* data);
void* multi_fill_matrix(void* data);
void* multi_free_matrix(void* data);
void* multi_transp_matrix(void* data);

void get_optimal_thread_count(opt_thread_count_t *thread);


//  Init/release operations
Matrix* create_matrix_from_file(const char* path_file);
Matrix* create_matrix(size_t rows, size_t cols);
Matrix* fill_matrix(Matrix* matrix, const int source_array[]);
int free_matrix(Matrix* matrix);
void print_matrix(Matrix* matrix);


//  Math operations
Matrix* transp(const Matrix* matrix);


#endif  // PROJECT_INCLUDE_MATRIX_SERVICE_THREAD_H_
