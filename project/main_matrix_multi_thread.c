// Copyright 2021 Diakonov Andrey

#include "include/matrix_multi_thread.h"

int main() {
    Matrix* M = create_matrix_from_file("1.txt");
    print_matrix(M);

    Matrix* new_m = create_matrix(8, 3);
    int array[] = {1, 2, 3, 4, 5, 6,
                   1, 2, 3, 4, 5, 6,
                   1, 2, 3, 4, 5, 6,
                   11, 22, 33, 44, 55, 66,
                   1, 2, 3, 4, 5, 6,
                   1, 2, 3, 4, 5, 6};
    fill_matrix(new_m, array);
    print_matrix(new_m);

    free_matrix(new_m);

    print_matrix(transp(M));

    return 0;
}
