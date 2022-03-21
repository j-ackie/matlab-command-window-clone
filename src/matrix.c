#include "matrix.h"

struct matrix
{
    double** arr;
    int rows;
    int columns;
};

matrix_t matrix_create(vector_t* vectors, int num_vectors, bool column)
{
    matrix_t matrix = malloc(sizeof(struct matrix));
    if (!matrix) {
        return NULL;
    }

    if (column) {
        matrix->rows = vector_length(vectors[0]);
        matrix->columns = num_vectors;
        matrix->arr = malloc(sizeof(double*) * matrix->rows);
        for (int i = 0; i < matrix->rows; i++) {
            matrix->arr[i] = malloc(sizeof(double) * matrix->columns);
            for (int j = 0; j < matrix->columns; j++) {
                matrix->arr[i][j] = *vector_at(vectors[j], i);
            }
        }
    }
    else {
        matrix->rows = num_vectors;
        matrix->columns = vector_length(vectors[0]);
        matrix->arr = malloc(sizeof(double*) * matrix->rows);
        for (int i = 0; i < matrix->rows; i++) {
            matrix->arr[i] = malloc(sizeof(double) * matrix->columns);
            for (int j = 0; j < matrix->columns; j++) {
                matrix->arr[i][j] = *vector_at(vectors[i], j);
            }
        }
    }
    return matrix;
}

void matrix_destroy(matrix_t matrix)
{
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->arr[i]);
    }
    free(matrix->arr);
    free(matrix);
}

double** matrix_arr(matrix_t matrix)
{
    // Can't return matrix->arr because it would allow 
    // matrix's arr to be modified directly
    double** arr = malloc(sizeof(double*) * matrix->rows);
    for (int i = 0; i < matrix->rows; i++) {
        arr[i] = malloc(sizeof(double) * matrix->columns);
        for (int j = 0; j < matrix->columns; j++) {
            arr[i][j] = matrix->arr[i][j];
        }
    }
    return arr;
}

int matrix_rows(matrix_t matrix)
{
    return matrix->rows;
}

int matrix_columns(matrix_t matrix)
{
    return matrix->columns;
}

double* matrix_at(matrix_t matrix, int row, int column)
{
    if (row >= matrix->rows || row < 0 || 
        column >= matrix->columns || column < 0) {
        return NULL;
    }
    return &matrix->arr[row][column];
}

void matrix_print(matrix_t matrix)
{
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            printf("%lf ", matrix->arr[i][j]);
        }
        printf("\n");
    }
}