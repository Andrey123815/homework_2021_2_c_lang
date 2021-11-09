// Copyright 2021 Diakonov Andrey

#include <stdio.h>
#include <string.h>

#include "lib_time_test.h"

int main() {
    flag_mode mode = ONE_THREAD_MODE;

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

