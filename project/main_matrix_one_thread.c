#include "include/matrix_one_thread.h"

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
    Matrix* m_new = create_matrix_from_file("file.tst");
    return 0;
}
