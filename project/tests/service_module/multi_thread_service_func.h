// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_INCLUDE_MULTI_THREAD_SERVICE_H_
#define PROJECT_INCLUDE_MULTI_THREAD_SERVICE_H_

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "../../include/matrix_multi_thread.h"


//  Init/release operations
Matrix* multi_thread_create_matrix_from_file(const char* path_file) {
    return create_matrix_from_file(path_file);
}

Matrix* multi_thread_create_matrix(size_t rows, size_t cols) {
    return create_matrix(rows, cols);
}

Matrix* multi_thread_fill_matrix(Matrix* matrix, const int source_array[]) {
    return fill_matrix(matrix, source_array);
}

int multi_thread_free_matrix(Matrix* matrix) {
    return free_matrix(matrix);
}

void multi_thread_print_matrix(Matrix* matrix) {
    print_matrix(matrix);
}


//  Math operations
Matrix* multi_thread_transp(Matrix* matrix) {
    return transp(matrix);
}


#endif  // PROJECT_INCLUDE_MULTI_THREAD_SERVICE_H_
