// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_INCLUDE_MATRIX_ONE_THREAD_H_
#define PROJECT_INCLUDE_MATRIX_ONE_THREAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "../include/structures.h"

//  Init/release operations
Matrix* create_matrix_from_file(const char* path_file);
Matrix* create_matrix(size_t rows, size_t cols);
Matrix* fill_matrix(Matrix* matrix, const int source_array[]);
int free_matrix(Matrix* matrix);
void print_matrix(Matrix* matrix);

//  Math operations
Matrix* transp(Matrix* matrix);


#endif  // PROJECT_INCLUDE_MATRIX_ONE_THREAD_H_
