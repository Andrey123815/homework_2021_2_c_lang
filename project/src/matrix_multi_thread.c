// Copyright 2021 Diakonov Andrey

#include "../include/matrix_multi_thread.h"

int flag_cancel = 0;


// Service operations


void* multi_read_from_file(void* data) {
    matrix_data_t* readFileData = (matrix_data_t*)data;
    FILE* fmatrix = fopen(readFileData->path_to_file, "r");
    if (fmatrix == NULL) {
        printf("NULL");
        return NULL;
    }
    size_t i = 0;
    while (!feof(fmatrix) && i < readFileData->start_row) {
        if ((char)fgetc(fmatrix) == '\n') {
            ++i;
        }
    }

    for (i = readFileData->start_row; i < readFileData->final_row
                                                && flag_cancel != 1; ++i) {
        for (size_t j = 0; j < readFileData->row_size
                                                && flag_cancel != 1; ++j) {
            if (fscanf(fmatrix, "%lf",
                       &readFileData->M->matr[i-1][j]) != 1) {
                fclose(fmatrix);
                flag_cancel = 1;
            }
        }
    }
    fclose(fmatrix);
    return readFileData->M;
}

void* multi_calloc_and_check(void* data) {
    matrix_data_t* callocData = (matrix_data_t*)data;
    for (unsigned int i = callocData->start_row;
                                i < callocData->final_row; ++i) {
        callocData->M->matr[i] = calloc(callocData->row_size, sizeof(double));
        if (callocData->M->matr[i] == NULL) {
            flag_cancel = 1;
            return callocData->M;
        }
    }
    return callocData->M;
}

void* multi_fill_matrix(void* data) {
    matrix_data_t* fillData = (matrix_data_t*)data;
    for (unsigned int i = fillData->start_row; i < fillData->final_row; ++i) {
        for (unsigned int j = 0; j < fillData->row_size; ++j) {
            fillData->M->matr[i][j] = fillData->
                    source_array[i * fillData->M->col + j];
        }
    }
    return fillData->M;
}

void* multi_free_matrix(void* data) {
    matrix_data_t* freeData = (matrix_data_t*)data;
    for (unsigned int i = freeData->start_row; i < freeData->final_row; ++i) {
        free(freeData->M->matr[i]);
    }
    return NULL;
}


void* multi_transp_matrix(void* data) {
    matrix_data_t* transpData = (matrix_data_t*)data;
    for (size_t i = 0; i < transpData->M->row; ++i) {
        for (size_t j = 0; j < transpData->M->col; ++j) {
            transpData->New_M->matr[j][i] = transpData->M->matr[i][j];
        }
    }
    return transpData->M;
}

void get_optimal_thread_count(opt_thread_count_t *thread) {
    if (thread->rows_count > 32) {
        // Check count system cores
        thread->need_count_threads = (int)
                sysconf(_SC_NPROCESSORS_ONLN);
        thread->row_count_to_thread =
                thread->rows_count / thread->need_count_threads;
    } else {
        thread->need_count_threads = thread->rows_count / 4 + 1;
        thread->row_count_to_thread = (thread->rows_count < 4)
                * thread->rows_count +(thread->rows_count >= 4) * 4;
    }
}


Matrix* multi_thread_data_processing(void* (*func)(void*), params_t *params) {
    // Expect minimum 4 file_strings to one thread
    opt_thread_count_t thread_params = {.rows_count = params->M->row};
    get_optimal_thread_count(&thread_params);

    // Excluding the main thread
    pthread_t *threads = (pthread_t *)malloc(
            (thread_params.need_count_threads)* sizeof(pthread_t));
    // How many threads - so many thread data structures
    matrix_data_t *threadData = (matrix_data_t *) malloc(
            (thread_params.need_count_threads) * sizeof(matrix_data_t));

    unsigned int j = params->flag_work_with_file;
    for (int i = 0; i < thread_params.need_count_threads; ++i) {
        threadData[i].path_to_file = params->path_file;
        threadData[i].M = params->M;
        threadData[i].start_row = j;
        j += thread_params.row_count_to_thread;
        threadData[i].final_row = j;
        threadData[i].row_size = params->M->col;
        threadData[i].source_array = params->source_array;
        threadData[i].New_M = params->New_M;

        if (i == thread_params.need_count_threads - 1) {
            // The number of lines may not be evenly divisible between threads
            threadData->final_row = params->M->row;
        }

        if (pthread_create(&(threads[i]), NULL, func, &threadData[i]) != 0) {
            free(threads);
            free(threadData);
            // free_matrix(params->M);
            return NULL;
        }
    }

    for (int i = 0; i < thread_params.need_count_threads; i++)
        pthread_join(threads[i], NULL);


    //free(threads);
    free(threadData);

    if (flag_cancel == 1) {
        return NULL;
    }

    if (params->flag_work_with_file == FREE_MATRIX) {
        free(params->M->matr);
        free(params->M);
        return SUCCESS;
    }

    return params->M;
}


//  Init/release operations


Matrix* create_matrix_from_file(const char* path_file) {
    if (path_file == NULL) {
        return NULL;
    }

    FILE* fmatrix = fopen(path_file, "r");
    if (fmatrix == NULL) {
        return NULL;
    }

    size_t rows;
    size_t cols;
    if (fscanf(fmatrix, "%zu%zu", &rows, &cols) != 2) {
        fclose(fmatrix);
        return NULL;
    }

    fclose(fmatrix);

    Matrix* M = create_matrix(rows, cols);
    if (M == NULL) {
        return NULL;
    }

    M->row = rows;
    M->col = cols;

    params_t params = {.M = M,
                       .source_array = NULL,
                       .path_file = path_file,
                       .flag_work_with_file = 1};

    return multi_thread_data_processing(multi_read_from_file, &params);
}


Matrix* create_matrix(size_t rows, size_t cols) {
    if (rows < 1 || cols < 1) {
        return NULL;
    }

    Matrix* M = malloc(sizeof(Matrix));
    if (M == NULL) {
        return NULL;
    }

    M->row = rows;
    M->col = cols;
    M->matr = calloc(rows, sizeof(double *));
    if (M->matr == NULL) {
        free(M);
        return NULL;
    }

    params_t params = {.M = M,
                       .source_array = NULL,
                       .path_file = "",
                       .flag_work_with_file = 0};

    if (multi_thread_data_processing(multi_calloc_and_check, &params) == NULL) {
        free_matrix(M);
        return  NULL;
    }

    return M;
}


Matrix* fill_matrix(Matrix* matrix, const int source_array[]) {
    params_t params = {.M = matrix,
                       .source_array = source_array,
                       .path_file = "",
                       .flag_work_with_file = 0};

    return multi_thread_data_processing(multi_fill_matrix, &params);
}


int free_matrix(Matrix* matrix) {
    if (matrix == NULL) {
        return -1;
    }

    params_t params = {.M = matrix,
                       .source_array = NULL,
                       .path_file = "",
                       .flag_work_with_file = FREE_MATRIX};

    multi_thread_data_processing(multi_free_matrix, &params);

    return 0;
}


void print_matrix(Matrix* matrix) {
    for (size_t i = 0; i < matrix->row; ++i) {
        for (size_t j = 0; j < matrix->col; ++j) {
            printf("%9.3lf ", matrix->matr[i][j]);
        }
        printf("\n");
    }
}


Matrix* transp(Matrix* matrix) {
    if (matrix == NULL) {
        return NULL;
    }

    Matrix* new_matrix = create_matrix(matrix->col, matrix->row);
    if (new_matrix == NULL) {
        return NULL;
    }

    params_t params = {.M = matrix,
                       .flag_work_with_file = 0,
                       .New_M = new_matrix};

    multi_thread_data_processing(multi_transp_matrix, &params);

    return new_matrix;
}
