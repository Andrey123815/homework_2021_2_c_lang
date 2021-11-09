// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_TESTS_INCLUDE_LIB_GENERATOR_H_
#define PROJECT_TESTS_INCLUDE_LIB_GENERATOR_H_

#include <stdio.h>
#include "test_structures.h"


void generate_file(const char* path_file, data_size_t* data_size, int number_iteration) {
    FILE* fmatrix = fopen(path_file, "w");
    if (fmatrix == NULL) {
        return;
    }

    for (int i = 0; i < data_size->data_row_count[number_iteration]; ++i) {
        for (int j = 0; j < data_size->data_col_count[number_iteration]; ++j) {
            fprintf(fmatrix, "%9.3lf ", (double)(i * data_size->data_col_count[number_iteration] + j));
        }
        fprintf(fmatrix, "\n");
    }
    fclose(fmatrix);
}

int* generate_source_array(int rows, int cols) {
    int* source_array = (int*) malloc(rows * cols * sizeof(int));
    if (source_array == NULL) {
        return source_array;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            source_array[i * cols + j] = i * cols + j;
        }
    }
    return source_array;
}


#endif  // PROJECT_TESTS_INCLUDE_LIB_GENERATOR_H_
