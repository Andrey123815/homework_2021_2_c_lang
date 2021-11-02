// Copyright 2021 Diakonov Andrey

#include <stdio.h>
#include <string.h>

#include "service_module/include/lib_time_test.h"

int main(int argc, const char* argv[]) {
    const char* s1 = "one-thread";
    const char* s2 = "multi-thread";
    flag_mode mode;

    if (strcmp(argv[1], s1) == 0) {
        mode = ONE_THREAD_MODE;
    } else if (strcmp(argv[1], s2) == 0) {
        mode = MULTI_THREAD_MODE;
    } else {
        return -1;
    }

    parameters_t params = {.M = NULL,
                           .flag = CREATE_FROM_FILE,
                           .function_name = "CREATE_MATRIX_FROM_FILE"
    };
    time_test(&params, mode);

    params.M = NULL;
    params.flag = CREATE;
    params.function_name = "CREATE_MATRIX";
    time_test(&params, mode);

    params.M = NULL;
    params.flag = TRANSP;
    params.function_name = "TRANSP_MATRIX";
    time_test(&params, mode);

    return 0;
}
