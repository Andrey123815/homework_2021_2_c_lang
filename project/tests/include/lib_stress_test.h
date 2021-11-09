// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_TESTS_SERVICE_MODULE_INCLUDE_LIB_STRESS_TEST_H_
#define PROJECT_TESTS_SERVICE_MODULE_INCLUDE_LIB_STRESS_TEST_H_

#include <string.h>
#include <stdio.h>

#include "../../../include/matrix_processing.h"
#include "test_structures.h"


int write_results_to_file(const char* path, const Matrix* M) {
    FILE* fmatrix = fopen(path, "a+");

    if (fmatrix == NULL || M == NULL) {
        return -1;
    }

    fprintf(fmatrix, "%zu %zu", M->row, M->col);

    for (size_t i = 0; i < M->row; ++i) {
        for (size_t j = 0; j < M->col; ++j) {
            fprintf(fmatrix, "%lf ", M->matr[i][j]);
        }
        fprintf(fmatrix, "\n");
    }
    fprintf(fmatrix, "\n");

    return 0;
}

int read_and_compare() {
    FILE* f_one_thread = fopen("one-thread.txt",  "r");

    if (f_one_thread == NULL) {
        printf("no file\n");
        return -1;
    }

    FILE* f_multi_thread = fopen("multi-thread.txt", "r");

    if (f_multi_thread == NULL) {
        fclose(f_one_thread);
        printf("no file\n");
        return -1;
    }

    fseek(f_one_thread, 0L, SEEK_END);
    size_t size_f_one_thread = ftell(f_one_thread);
    fseek(f_multi_thread, 0L, SEEK_END);
    size_t size_f_multi_thread = ftell(f_multi_thread);

    if (size_f_one_thread != size_f_multi_thread) {
        printf("size wrong\n");
        fclose(f_one_thread);
        fclose(f_multi_thread);
        return -1;
    }

    rewind(f_one_thread);
    rewind(f_multi_thread);

    while (!feof(f_one_thread)) {
        char str_1[1000];
        char str_2[1000];
        fgets(str_1, 1000, f_one_thread);
        fgets(str_2, 1000, f_multi_thread);
        if (strcmp(str_1, str_2) != 0) {
            printf("not equal\n");
            printf("%s\n%s\n", str_1, str_2);
            return -1;
        }
    }

    fclose(f_one_thread);
    fclose(f_multi_thread);

    return 0;
}


#endif  // PROJECT_TESTS_SERVICE_MODULE_INCLUDE_LIB_STRESS_TEST_H_
