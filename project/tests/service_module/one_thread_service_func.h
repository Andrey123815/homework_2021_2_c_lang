// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_TESTS_SERVICE_MODULE_ONE_THREAD_SERVICE_FUNC_H_
#define PROJECT_TESTS_SERVICE_MODULE_ONE_THREAD_SERVICE_FUNC_H_

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "../../include/matrix_one_thread.h"


//  Init/release operations
Matrix* one_thread_create_matrix_from_file(const char* path_file) {
    return create_matrix_from_file(path_file);
}

Matrix* one_thread_create_matrix(size_t rows, size_t cols) {
    return create_matrix(rows, cols);
}

Matrix* one_thread_fill_matrix(Matrix* matrix, const int source_array[]) {
    return fill_matrix(matrix, source_array);
}

int one_thread_free_matrix(Matrix* matrix) {
    return free_matrix(matrix);
}

void one_thread_print_matrix(Matrix* matrix) {
    print_matrix(matrix);
}


//  Math operations
Matrix* one_thread_transp(Matrix* matrix) {
    return transp(matrix);
}


#endif  // PROJECT_TESTS_SERVICE_MODULE_ONE_THREAD_SERVICE_FUNC_H_