// Copyright 2021 Diakonov Andrey

#include "../include/lib_generator.h"

void generate_file(const char* path_file, data_size_t* data_size, int number_iteration) {
    FILE* fmatrix = fopen(path_file, "w");
    if (fmatrix == NULL) {
        return;
    }

    for (int i = 0; i < data_size->data_row_count[number_iteration]; ++i) {
        for (int j = 0; j < data_size->data_col_count[number_iteration]; ++j) {
            fprintf(fmatrix, "%9.3lf ", (double)(i * j + j));
        }
        fprintf(fmatrix, "\n");
    }
    fclose(fmatrix);
}

int* generate_source_array(int rows, int cols) {
    int* ptr = (int*) malloc(rows * cols * sizeof(int));
    if (ptr == NULL) {
        return ptr;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            ptr[i * j + j] = i * j + j;
        }
    }
    return ptr;
}
