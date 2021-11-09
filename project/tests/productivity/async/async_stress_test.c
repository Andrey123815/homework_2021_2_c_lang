// Copyright 2021 Diakonov Andrey

#include "lib_generator.h"
#include "lib_stress_test.h"

int main() {
    const char* service_file = "service.txt";
    const char* common_stress_file = "multi-thread.txt";

    data_size_t data_size = {.data_row_count = {800, 10000}, .data_col_count = {800, 5000}};

    for (int i = 0; i < 2; ++i) {
        Matrix* simple_matrix = create_matrix(data_size.data_row_count[i], data_size.data_col_count[i]);
        generate_file(service_file, &data_size, i);
        int* source_array = generate_source_array(data_size.data_row_count[i], data_size.data_col_count[i]);
        fill_matrix(simple_matrix, source_array);

        Matrix* matrix_from_file = create_matrix_from_file(service_file);

        write_results_to_file(common_stress_file, simple_matrix);

        Matrix* transposition_matrix = transp(simple_matrix);
        write_results_to_file(common_stress_file, transposition_matrix);

        write_results_to_file(common_stress_file, matrix_from_file);

        free(source_array);
        free_matrix(simple_matrix);
        free_matrix(transposition_matrix);
        free_matrix(matrix_from_file);
        remove(service_file);
    }

    return 0;
}
