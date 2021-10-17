#ifndef HW2_C_CPP_MATRIX_ONE_THREAD_H
#define HW2_C_CPP_MATRIX_ONE_THREAD_H

#include <stdio.h>

typedef struct Matrix {
    size_t row;
    size_t col;
    double** matr;
} Matrix;


//  Init/release operations
Matrix* create_matrix_from_file(const char* path_file);
Matrix* create_matrix(size_t rows, size_t cols);
Matrix* fill_matrix(Matrix* matrix, const int source_array[], const int source_array_size);
int free_matrix(Matrix* matrix);
void print_matrix(Matrix* matrix);

//  Math operations
Matrix* transp(const Matrix* matrix);


#endif //HW2_C_CPP_MATRIX_ONE_THREAD_H
