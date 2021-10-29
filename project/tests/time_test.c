// Copyright 2021 Diakonov Andrey

#include <stdio.h>

#include "service_module/time_test_func.h"

int main() {
    parameters_t params = {.M = NULL,
                           .flag = CREATE_FROM_FILE,
                           .function_name = "CREATE_MATRIX_FROM_FILE"};
    time_test(&params);

    params.M = NULL;
    params.flag = CREATE;
    params.function_name = "CREATE_MATRIX";
    time_test(&params);

    return 0;
}
