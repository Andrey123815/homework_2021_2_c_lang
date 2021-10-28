// Copyright 2021 Diakonov Andrey

#include "include/matrix_one_thread.h"

int main() {
    Matrix* m = create_matrix(2, 2);
    const int source_array_size = 4;
    int source_array[4];
    for (int i = 0; i < source_array_size; ++i) {
        source_array[i] = i;
    }
    fill_matrix(m, source_array, source_array_size);
    print_matrix(m);
    print_matrix(transp(m));
    m = create_matrix_from_file("file.tst");
    free_matrix(m);
    return 0;
}
