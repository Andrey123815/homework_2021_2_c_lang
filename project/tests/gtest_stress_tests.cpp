// Copyright 2021 Diakonov Andrey

#include <gtest/gtest.h>
#include <cstring>
#include <fstream>

extern "C" {
#include "service_module/one_thread_service_func.h"
#include "service_module/multi_thread_service_func.h"
#include "../include/matrix_one_thread.h"
#include "../include/matrix_multi_thread.h"
}


TEST(MATRIX_STRESS_TEST, INVALID_ROW) {
    EXPECT_EQ(one_thread_create_matrix(-1, 1),
                    multi_thread_create_matrix(-1, 1));
}

TEST(MATRIX_STRESS_TEST, INVALID_COL) {
    EXPECT_EQ(one_thread_create_matrix(1, 0),
                    multi_thread_create_matrix(1, 0));
}

TEST(MATRIX_STRESS_TEST, VALID_ROW_COL) {
    auto matrix_one_thread = one_thread_create_matrix(2, 2);
    auto matrix_multi_thread = multi_thread_create_matrix(2, 2);

    EXPECT_EQ(matrix_one_thread->row, matrix_multi_thread->row);
    EXPECT_EQ(matrix_one_thread->col, matrix_multi_thread->col);

    one_thread_free_matrix(matrix_one_thread);
    multi_thread_free_matrix(matrix_multi_thread);
}

TEST(MATRIX_STRESS_TEST, READ_FROM_FILE) {
    std::ofstream stream_to_write;
    std::ifstream stream_to_read;

    stream_to_write.open("test.txt", std::ios_base::out);
    stream_to_read.open("test.txt", std::ios_base::in);

    stream_to_write << "2 3\n1 2 3\n4 5 6";
    stream_to_write.close();

    int row, col;
    stream_to_read >> row >> col;

    auto matrix_one_thread = one_thread_create_matrix_from_file("test.txt");
    auto matrix_multi_thread = multi_thread_create_matrix_from_file("test.txt");

    EXPECT_EQ(matrix_one_thread->row, matrix_multi_thread->row);
    EXPECT_EQ(matrix_one_thread->col, matrix_multi_thread->col);

    for (size_t i = 0 ; i < matrix_one_thread->row; ++i) {
        for (size_t j = 0; j < matrix_one_thread->col; ++j) {
            EXPECT_EQ(matrix_one_thread->matr[i][j],
                                matrix_multi_thread->matr[i][j]);
        }
    }

    one_thread_free_matrix(matrix_one_thread);
    multi_thread_free_matrix(matrix_multi_thread);

    stream_to_read.close();
    remove("test.txt");
}

TEST(MATRIX_STRESS_TEST, FILL_MATRIX) {
    auto matrix_one_thread = one_thread_create_matrix(2, 2);
    auto matrix_multi_thread = multi_thread_create_matrix(2, 2);
    int source_array[] = {1, 2, 3, 4};

    one_thread_fill_matrix(matrix_one_thread, source_array);
    multi_thread_fill_matrix(matrix_multi_thread, source_array);

    EXPECT_EQ(matrix_one_thread->row, matrix_multi_thread->row);
    EXPECT_EQ(matrix_one_thread->col, matrix_multi_thread->col);

    for (size_t i = 0 ; i < matrix_one_thread->row; ++i) {
        for (size_t j = 0; j < matrix_one_thread->col; ++j) {
            EXPECT_EQ(matrix_one_thread->matr[i][j],
                                matrix_multi_thread->matr[i][j]);
        }
    }

    one_thread_free_matrix(matrix_one_thread);
    multi_thread_free_matrix(matrix_multi_thread);
}

TEST(MATRIX_STRESS_TEST, TRANSP_MATRIX) {
    auto matrix_one_thread = one_thread_create_matrix(3, 4);
    auto matrix_multi_thread = multi_thread_create_matrix(3, 4);
    const int input_mas[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    one_thread_fill_matrix(matrix_one_thread, input_mas);
    multi_thread_fill_matrix(matrix_multi_thread, input_mas);

    auto transp_matrix_one_thread = one_thread_transp(matrix_one_thread);
    auto transp_matrix_multi_thread = multi_thread_transp(matrix_multi_thread);

    EXPECT_EQ(transp_matrix_one_thread->row, transp_matrix_multi_thread->row);
    EXPECT_EQ(transp_matrix_one_thread->col, transp_matrix_multi_thread->col);

    for (size_t i = 0 ; i < transp_matrix_one_thread->row; ++i) {
        for (size_t j = 0; j < transp_matrix_one_thread->col; ++j) {
            EXPECT_EQ(transp_matrix_one_thread->matr[i][j],
                                transp_matrix_multi_thread->matr[i][j]);
        }
    }

    one_thread_free_matrix(matrix_one_thread);
    multi_thread_free_matrix(matrix_multi_thread);

    one_thread_free_matrix(transp_matrix_one_thread);
    multi_thread_free_matrix(transp_matrix_multi_thread);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
