// Copyright 2021 Diakonov Andrey

#include "../include/lib_generator.h"
#include "../include/lib_stress_test.h"

int main(int argc, char* argv[]) {
    const char* s1 = "one-thread";
    const char* s2 = "multi-thread";

    if (argc < 1 || (strcmp(argv[1], s1) != 0 && strcmp(argv[1], s2) != 0)) {
        return -1;
    }

    const char* common_stress_file = strcat(argv[1], ".txt");
    const char* service_file = "service.txt";
    data_size_t data_size = {.data_row_count = {800, 1600}, .data_col_count = {800, 1600}};

    for (int i = 0; i < 2; ++i) {
        Matrix* M = create_matrix(data_size.data_row_count[i], data_size.data_col_count[i]);
        generate_file(service_file, &data_size, i);
        Matrix* N = create_matrix_from_file(service_file);
        int* source_array = generate_source_array(data_size.data_row_count[i], data_size.data_col_count[i]);
        fill_matrix(M, source_array);

        write_results_to_file(common_stress_file, M);

        Matrix* trasp_M = transp(M);
        write_results_to_file(common_stress_file, trasp_M);

        write_results_to_file(common_stress_file, N);

        free(source_array);
        free_matrix(M);
        free_matrix(trasp_M);
        free_matrix(N);
        remove(service_file);
    }

    return 0;
}
