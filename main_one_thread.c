#include "project/include/matrix_one_thread.h"

int main() {
    Matrix* m = create_matrix(2,2);
    int source_array_size = m->row * m->col;
    int source_array[source_array_size];
    for (int i = 0; i < source_array_size; ++i) {
        source_array[i] = i;
    }
    fill_matrix(m, source_array, source_array_size);
    print_matrix(m);
    print_matrix(transp(m));

    return 0;
}
