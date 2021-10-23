// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_INCLUDE_MATRIX_ONE_THREAD_H_
#define PROJECT_INCLUDE_MATRIX_ONE_THREAD_H_

#include <stdio.h>

typedef struct Matrix {
    size_t row;
    size_t col;
    double** matr;
} Matrix;


//  Init/release operations
Matrix* create_matrix_from_file(const char* path_file);
Matrix* create_matrix(size_t rows, size_t cols);
Matrix* fill_matrix(Matrix* matrix, const int source_array[],
                                    const int source_array_size);
int free_matrix(Matrix* matrix);
void print_matrix(Matrix* matrix);

//  Math operations
Matrix* transp(const Matrix* matrix);


#endif  // PROJECT_INCLUDE_MATRIX_ONE_THREAD_H_
