// Copyright 2021 Diakonov Andrey

#ifndef PROJECT_TESTS_INCLUDE_LIB_TIME_TEST_H_
#define PROJECT_TESTS_INCLUDE_LIB_TIME_TEST_H_

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "matrix_processing.h"
#include "test_structures.h"
#include "lib_generator.h"

#define CREATE_FROM_FILE 1
#define CREATE 2
#define TRANSP 3


Matrix* get_handler(int flag, data_size_t* data_size, int number_iteration) {
    switch (flag) {
        case CREATE_FROM_FILE: {
            Matrix* M = create_matrix_from_file("time_test.txt");
            return M;
        }
        case CREATE: {
            Matrix* M = create_matrix(
                    data_size->data_row_count[number_iteration],
                    data_size->data_col_count[number_iteration]);
            return M;
        }
        case TRANSP: {
            Matrix *M = create_matrix_from_file("time_test.txt");
            Matrix *trasp_M = transp(M);
            free_matrix(trasp_M);
            return M;
        }
        default: {
            printf("Error input flag\n%d", flag);
            return NULL;
        }
    }
}

int time_test(parameters_t* params, flag_mode mode) {
    const char* path_file = "time_test.txt";

    data_size_t data_size = {.data_row_count = {80, 100}, .data_col_count = {80, 500}};

    for (int k = 0; k < 2; ++k) {
        generate_file(path_file, &data_size, k);

        double average_time = 0;

        for (int i = 0; i < 3; ++i) {
            struct timespec start, stop;
            clock_gettime(CLOCK_MONOTONIC, &start);

            Matrix *M = get_handler(params->flag, &data_size, k);

            clock_gettime(CLOCK_MONOTONIC, &stop);

            average_time += (stop.tv_sec - start.tv_sec);
            average_time += (stop.tv_nsec - start.tv_nsec)  / 1000000000.0;

            free_matrix(M);
        }

        const char *s1 = "One-thread version passed test in";
        const char *s2 = "Multi-thread version passed test in";
        const char *s;

        if (mode == ONE_THREAD_MODE) {
            s = s1;
        } else {
            s = s2;
        }

        printf("%s  (Size: %d * %d)\n%36s %9.7lf sec  [PASSED]\n",
               params->function_name,
               data_size.data_row_count[k], data_size.data_col_count[k],
               s, average_time / 3);
    }

    if (remove(path_file) == -1) {
        return -1;
    }

    return 0;
}


#endif  // PROJECT_TESTS_INCLUDE_LIB_TIME_TEST_H_
