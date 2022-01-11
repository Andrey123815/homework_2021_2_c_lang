// Copyright 2021 Diakonov Andrey

#include "matrix_processing.h"

//  Init/release operations
Matrix* create_matrix_from_file(const char* path_file) {
    if (path_file == NULL) {
        return NULL;
    }

    FILE* fmatrix = fopen(path_file, "a+");
    if (fmatrix == NULL) {
        return NULL;
    }

    size_t rows;
    size_t cols;
    if (fscanf(fmatrix, "%zu%zu", &rows, &cols) != 2) {
        fclose(fmatrix);
        return NULL;
    }

    Matrix* M = create_matrix(rows, cols);
    if (M == NULL) {
        fclose(fmatrix);
        return NULL;
    }

    M->row = rows;
    M->col = cols;

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (fscanf(fmatrix, "%lf", &M->matr[i][j]) != 1) {
                fclose(fmatrix);
                free_matrix(M);
                return NULL;
            }
        }
    }
    fclose(fmatrix);
    return M;
}


Matrix* create_matrix(size_t rows, size_t cols) {
    if (rows < 1 || cols < 1) {
        return NULL;
    }

    Matrix* M = malloc(sizeof(Matrix));
    if (M == NULL) {
        return NULL;
    }

    M->row = rows;
    M->col = cols;
    M->matr = calloc(rows, sizeof(double *));
    if (M->matr == NULL) {
        free(M);
        return NULL;
    }

    for (size_t i = 0; i < rows; ++i) {
        M->matr[i] = calloc(cols, sizeof(double));
        if (M->matr[i] == NULL) {
            free_matrix(M);
            return NULL;
        }
    }

    return M;
}


Matrix* fill_matrix(Matrix* matrix, const int source_array[]) {
    for (size_t i = 0; i < matrix->row; ++i) {
        for (size_t j = 0; j < matrix->col; ++j) {
            matrix->matr[i][j] = source_array[i * matrix->col + j];
        }
    }
    return matrix;
}


int free_matrix(Matrix* matrix) {
    if (matrix == NULL) {
        return -1;
    }
    for (size_t i = 0; i < matrix->row; ++i) {
        free(matrix->matr[i]);
    }
    free(matrix->matr);
    free(matrix);
    return 0;
}


Matrix* transp(Matrix* matrix) {
    if (matrix == NULL) {
        return NULL;
    }

    Matrix* new_matrix = create_matrix(matrix->col, matrix->row);
    if (new_matrix == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < matrix->row; ++i) {
        for (size_t j = 0; j < matrix->col; ++j) {
            new_matrix->matr[j][i] = matrix->matr[i][j];
        }
    }

    return new_matrix;
}
