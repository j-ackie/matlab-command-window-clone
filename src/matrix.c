#include "matrix.h"

struct matrix
{
    double** arr;
    int rows;
    int columns;
};

matrix_t matrix_create_from_vectors(int num_vectors, vector_t vectors[num_vectors], bool column)
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


matrix_t matrix_create_from_array(int rows, int columns, double arr[rows][columns])
{
    matrix_t matrix = malloc(sizeof(struct matrix));
    if (!matrix) {
        return NULL;
    }
    matrix->rows = rows;
    matrix->columns = columns;
    matrix->arr = malloc(sizeof(double*) * matrix->rows);
    for (int i = 0; i < matrix->rows; i++) {
        matrix->arr[i] = malloc(sizeof(double) * matrix->columns);
        for (int j = 0; j < matrix->columns; j++) {
            matrix->arr[i][j] = arr[i][j];
        }
    }
    return matrix;
}

void matrix_destroy(matrix_t matrix)
{
    if (matrix == NULL) {
        return;
    }
    matrix_destroy_arr(matrix->arr, matrix->rows);
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

void matrix_destroy_arr(double** arr, int rows)
{
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
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

matrix_t matrix_transpose(matrix_t matrix)
{
    double arr[matrix->columns][matrix->rows];

    for (int i = 0; i < matrix->columns; i++) {
        for (int j = 0; j < matrix->rows; j++) {
            arr[i][j] = matrix->arr[j][i];
        }
    }

    matrix_t transposed_matrix = matrix_create_from_array(matrix->columns,
                                                        matrix->rows, arr);

    return transposed_matrix;
}

matrix_t matrix_add(matrix_t matrix1, matrix_t matrix2)
{
    if (matrix1 == NULL && matrix2 != NULL) {
        return matrix2;
    }
    else if (matrix2 == NULL) {
        return NULL;
    }
    else if (matrix1->rows == matrix2->rows && matrix1->columns == matrix2->columns) {
        double arr[matrix1->rows][matrix1->columns];
        for (int i = 0; i < matrix1->rows; i++) {
            for (int j = 0; j < matrix2->columns; j++) {
                arr[i][j] = matrix1->arr[i][j] + matrix2->arr[i][j];
            }
        }
        return matrix_create_from_array(matrix1->rows, matrix2->columns, arr);
    }
    return NULL;
}

matrix_t matrix_multiplication(matrix_t matrix1, matrix_t matrix2)
{
    if (matrix1->columns != matrix2->rows) {
        return NULL;
    }

    double arr[matrix1->rows][matrix2->columns];

    // for (int i = 0; i < matrix1->rows; i++) {
    //     double product = 0;
    //     for (int j = 0; j < matrix1->columns; j++) {
    //         product += matrix1->arr[i][j] * matrix2->arr[j][i];
    //     }
    //     arr[i][]
    // }
}

matrix_t matrix_subtract(matrix_t matrix1, matrix_t matrix2)
{
    if (matrix1 == NULL && matrix2 != NULL) {
        double arr[matrix2->rows][matrix2->columns];
        for (int i = 0; i < matrix2->rows; i++) {
            for (int j = 0; j < matrix2->columns; j++) {
                arr[i][j] = matrix2->arr[i][j] * -1;
            }
        }
        return matrix_create_from_array(matrix2->rows, matrix2->columns, arr);
    }
    else if (matrix2 == NULL) {
        return NULL;
    }
    else if (matrix1->rows == matrix2->rows && matrix1->columns == matrix2->columns) {
        double arr[matrix1->rows][matrix1->columns];
        for (int i = 0; i < matrix1->rows; i++) {
            for (int j = 0; j < matrix2->columns; j++) {
                arr[i][j] = matrix1->arr[i][j] - matrix2->arr[i][j];
            }
        }
        return matrix_create_from_array(matrix1->rows, matrix2->columns, arr);
    }
    return NULL;
}

matrix_t matrix_scalar_product(matrix_t matrix, double scalar)
{
    if (matrix == NULL) {
        return NULL;
    }

    double arr[matrix->rows][matrix->columns];
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            arr[i][j] = matrix->arr[i][j] * scalar;
        }
    }
    matrix_t product = matrix_create_from_array(matrix->rows, matrix->columns,
                                                arr);
    
    return product;
}

void matrix_row_swap(matrix_t matrix, int row1, int row2) 
{
    if (row1 >= matrix->rows || row2 >= matrix->rows || row1 < 0 || row2 < 0) {
        return;
    }

    double* temp = matrix->arr[row1];
    matrix->arr[row1] = matrix->arr[row2];
    matrix->arr[row2] = temp;
}

void matrix_row_multiply(matrix_t matrix, int row, int scalar)
{
    for (int i = 0; i < matrix->columns; i++) {
        matrix->arr[row][i] *= scalar;
    }
}

void matrix_row_add(matrix_t matrix, int row1, int row2, int scalar)
{
    for (int i = 0; i < matrix->columns; i++) {
        matrix->arr[row2][i] += matrix->arr[row1][i] * scalar;
    }
}

void matrix_rref(matrix_t matrix)
{
    int current_row = 0;
    int current_col = 0;
    while (current_row < matrix->rows && current_col < matrix->columns) {

    }
}

bool matrix_equals(matrix_t matrix1, matrix_t matrix2)
{
    if (matrix1->rows == matrix2->rows && matrix1->columns == matrix2->columns) {
        for (int i = 0; i < matrix1->rows; i++) {
            for (int j = 0; j < matrix1->columns; j++) {
                if (matrix1->arr[i][j] != matrix2->arr[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool matrix_not_equals(matrix_t matrix1, matrix_t matrix2)
{
    return !matrix_equals(matrix1, matrix2);
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