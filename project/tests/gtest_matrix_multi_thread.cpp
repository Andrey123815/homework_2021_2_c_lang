// Copyright 2021 Diakonov Andrey

#include <gtest/gtest.h>
#include <cstring>
#include <fstream>

extern "C" {
#include "../include/matrix_multi_thread.h"
}


TEST(MATRIX_MULTI_THREAD_TEST, INVALID_ROW) {
    EXPECT_EQ(create_matrix(-1, 1), nullptr);
}

TEST(MATRIX_MULTI_THREAD_TEST, INVALID_COL) {
    EXPECT_EQ(create_matrix(1, 0), nullptr);
}

TEST(MATRIX_MULTI_THREAD_TEST, VALID_ROW_COL) {
    auto M = create_matrix(2, 2);
    EXPECT_EQ(M->row, 2);
    EXPECT_EQ(M->col, 2);
    free_matrix(M);
}

TEST(MATRIX_MULTI_THREAD_TEST, READ_FROM_FILE) {
    std::ofstream stream_to_write;
    std::ifstream stream_to_read;
    stream_to_write.open("test.txt", std::ios_base::out);
    stream_to_write << "2 3\n1 2 3\n4 5 6";
    stream_to_write.close();
    int source_array[] = {1, 2, 3, 4, 5, 6};

    Matrix* M = create_matrix_from_file("test.txt");

    EXPECT_EQ(M->row, 2);
    EXPECT_EQ(M->col, 3);

    for (size_t i = 0 ; i < M->row; ++i) {
        for (size_t j = 0; j < M->col; ++j) {
            EXPECT_EQ(M->matr[i][j], source_array[i * M->col + j]);
        }
    }

    free_matrix(M);
    remove("test.txt");
}

TEST(MATRIX_MULTI_THREAD_TEST, FILL_MATRIX) {
    Matrix *m1 = create_matrix(2, 2);
    m1->matr[0][0] = 1;
    m1->matr[0][1] = 2;
    m1->matr[1][0] = 3;
    m1->matr[1][1] = 4;

    Matrix *m2  = create_matrix(2, 2);
    int source_array[] = {1, 2, 3, 4};
    fill_matrix(m2, source_array);

    EXPECT_EQ(m1->row, m2->row);
    EXPECT_EQ(m1->col, m2->col);
    for (size_t i = 0 ; i < m1->row; ++i) {
        for (size_t j = 0; j < m1->col; ++j) {
            EXPECT_EQ(m1->matr[i][j], m2->matr[i][j]);
        }
    }

    free_matrix(m1);
    free_matrix(m2);
}

TEST(MATRIX_MULTI_THREAD_TEST, TRANSP_MATRIX) {
    Matrix *m = create_matrix(3, 4);
    const int input_mas[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    fill_matrix(m, input_mas);
    auto transp_m = transp(m);

    Matrix *m_test = create_matrix(4, 3);
    const int test_mas[] = {1, 5, 9, 2, 6, 10, 3, 7, 11, 4, 8, 12};
    fill_matrix(m_test, test_mas);

    EXPECT_EQ(transp_m->row, m_test->row);
    EXPECT_EQ(transp_m->col, m_test->col);
    for (size_t i = 0 ; i < transp_m->row; ++i) {
        for (size_t j = 0; j < transp_m->col; ++j) {
            EXPECT_EQ(transp_m->matr[i][j], m_test->matr[i][j]);
        }
    }

    free_matrix(m);
    free_matrix(transp_m);
    free_matrix(m_test);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
