// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_TESTS_SERVICE_MODULE_TIME_TEST_FUNC_H_
#define PROJECT_TESTS_SERVICE_MODULE_TIME_TEST_FUNC_H_

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "./one_thread_service_func.h"
#include "./multi_thread_service_func.h"
#include "../../include/matrix_one_thread.h"
#include "../../include/matrix_multi_thread.h"

#define CREATE_FROM_FILE 1
#define CREATE 2
#define FILL 3

typedef struct {
    int flag;
    Matrix* M;
    char* function_name;
} parameters_t;

typedef enum {
    ONE_THREAD_MODE,
    MULTI_THREAD_MODE
} flag_mode;

typedef struct {
    int data_row_count[2];
    int data_col_count[2];
} data_size_t;

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

Matrix* get_handler(int flag, flag_mode mode, data_size_t* data_size, int number_iteration) {
    if (mode == ONE_THREAD_MODE) {
        switch (flag) {
            case CREATE_FROM_FILE: {
                Matrix* M = one_thread_create_matrix_from_file("time_test.txt");
                return M;
            }
            case CREATE: {
                Matrix* M = one_thread_create_matrix(
                        data_size->data_row_count[number_iteration],
                        data_size->data_col_count[number_iteration]);
                return M;
            }
            case FILL: {
                Matrix* M = one_thread_create_matrix(
                        data_size->data_row_count[number_iteration],
                        data_size->data_col_count[number_iteration]);
                int* source_array = generate_source_array(
                        data_size->data_row_count[number_iteration],
                        data_size->data_col_count[number_iteration]);
                one_thread_fill_matrix(M, source_array);
                free(source_array);
                return M;
            }
            default: {
                printf("Error input flag\n");
                return NULL;
            }
        }
    }
    if (mode == MULTI_THREAD_MODE) {
        switch (flag) {
            case CREATE_FROM_FILE: {
                Matrix* M = multi_thread_create_matrix_from_file("time_test.txt");
                return M;
            }
            case CREATE: {
                Matrix* M = multi_thread_create_matrix(
                        data_size->data_row_count[number_iteration],
                        data_size->data_col_count[number_iteration]);
                return M;
            }
            case FILL: {
                Matrix* M = multi_thread_create_matrix(
                        data_size->data_row_count[number_iteration],
                        data_size->data_col_count[number_iteration]);

                int* source_array = generate_source_array(
                        data_size->data_row_count[number_iteration],
                        data_size->data_col_count[number_iteration]);

                multi_thread_fill_matrix(M, source_array);
                free(source_array);
                return M;
            }
            default: {
                printf("Error input flag\n");
                return NULL;
            }
        }
    }
    return NULL;
}

int time_test(parameters_t* params) {
    clock_t start, stop;
    double average_time_one_thread = 0;

    struct timespec begin, finish;
    double average_time_multi_thread = 0;

    const char* path_file = "time_test.txt";

    data_size_t data_size = {.data_row_count= {10, 400}, .data_col_count = {10, 400}};

    for (int k = 0; k < 2; ++k) {
        generate_file(path_file, &data_size, k);

        for (int i = 0; i < 3; ++i) {
            start = clock();

            Matrix *M1 = get_handler(params->flag, ONE_THREAD_MODE, &data_size, k);

            stop = clock();
            average_time_one_thread += (double) (stop - start) / CLOCKS_PER_SEC / 3;

            one_thread_free_matrix(M1);
        }

        for (int i = 0; i < 3; ++i) {
            clock_gettime(CLOCK_MONOTONIC, &begin);

            Matrix *M2 = get_handler(params->flag, MULTI_THREAD_MODE, &data_size, k);

            clock_gettime(CLOCK_MONOTONIC, &finish);

            average_time_multi_thread += (double)(finish.tv_sec - begin.tv_sec);
            average_time_multi_thread += (double)(finish.tv_nsec - begin.tv_nsec) / 1000000000.0;

            multi_thread_free_matrix(M2);
        }

        average_time_multi_thread /= 3;

        const char *s1 = "One-thread version passed test in";
        const char *s2 = "Multi-thread version passed test in";

        printf("%s  (Size: %d * %d)\n%36s %9.7lf sec  [PASSED]\n"
                                            "%36s %9.7lf sec  [PASSED]\n",
               params->function_name,
               data_size.data_row_count[k], data_size.data_col_count[k],
               s1, average_time_one_thread,
               s2, average_time_multi_thread);
    }

    if (remove(path_file) == -1) {
        return -1;
    }

    return 0;
}

#endif  // PROJECT_TESTS_SERVICE_MODULE_TIME_TEST_FUNC_H_
