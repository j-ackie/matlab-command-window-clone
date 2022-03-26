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

matrix_t matrix_slice(matrix_t matrix, int row_start, int row_end, int col_start, int col_end)
{
    if (row_start >= matrix->rows || row_start < 0 || row_end >= matrix->rows ||
        row_end < 0 || col_start >= matrix->columns || col_start < 0 ||
        col_end >= matrix->columns || col_end < 0) {
        
        return NULL;
    }
    double arr[row_end - row_start + 1][col_end - col_start + 1];
    for (int i = row_start; i <= row_end; i++) {
        for (int j = col_start; j <= col_end; j++) {
            arr[i - row_start][j - col_start] = matrix->arr[i][j];
        }
    }
    return matrix_create_from_array(row_end - row_start + 1, col_end - col_start + 1, arr);
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

matrix_t matrix_product(matrix_t matrix1, matrix_t matrix2)
{
    if (matrix1->columns != matrix2->rows) {
        return NULL;
    }

    double arr[matrix1->rows][matrix2->columns];

    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix2->columns; j++) {
            double product = 0;
            for (int k = 0; k < matrix1->columns; k++) {
                product += matrix1->arr[i][k] * matrix2->arr[k][j];
            }
            arr[i][j] = product;
        }
    }

    return matrix_create_from_array(matrix1->rows, matrix2->columns, arr);
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

matrix_t matrix_row_swap(matrix_t matrix, int row1, int row2) 
{
    if (row1 >= matrix->rows || row2 >= matrix->rows || row1 < 0 || row2 < 0) {
        return NULL;
    }

    // Copy the matrix so original matrix is not modified
    double arr[matrix->rows][matrix->columns];
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            arr[i][j] = matrix->arr[i][j];
        }
    }
    matrix_t copy = matrix_create_from_array(matrix->rows, matrix->columns, arr);

    double* temp = copy->arr[row1];
    copy->arr[row1] = copy->arr[row2];
    copy->arr[row2] = temp;

    return copy;
}

matrix_t matrix_row_multiply(matrix_t matrix, int row, double scalar)
{
    double arr[matrix->rows][matrix->columns];
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            arr[i][j] = matrix->arr[i][j];
        }
    }

    matrix_t copy = matrix_create_from_array(matrix->rows, matrix->columns, arr);

    for (int i = 0; i < matrix->columns; i++) {
        copy->arr[row][i] *= scalar;
    }
    return copy;
}

matrix_t matrix_row_add(matrix_t matrix, int row1, int row2, double scalar)
{
    double arr[matrix->rows][matrix->columns];
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            arr[i][j] = matrix->arr[i][j];
        }
    }

    matrix_t copy = matrix_create_from_array(matrix->rows, matrix->columns, arr);

    for (int i = 0; i < copy->columns; i++) {
        copy->arr[row2][i] += copy->arr[row1][i] * scalar;
    }
    
    return copy;
}

matrix_t matrix_rref(matrix_t matrix)
{
    double arr1[matrix->rows][matrix->columns];
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            arr1[i][j] = matrix->arr[i][j];
        }
    }

    matrix_t copy = matrix_create_from_array(matrix->rows, matrix->columns, arr1);

    int pivot_row_indices[matrix->columns];
    for (int i = 0; i < matrix->columns; i++) {
        pivot_row_indices[i] = -1;
    }

    // Row echelon form
    int current_row = 0;
    int current_col = 0;
    while (current_row < copy->rows && current_col < copy->columns) {
        matrix_t submatrix = matrix_slice(copy, current_row, copy->rows - 1,
                                            current_col, copy->columns - 1);

        matrix_t max = matrix_max(matrix_abs(submatrix), 1);
        vector_t max_of_cols = vector_create(copy->columns, max->arr[0], false);
        vector_t max_row_indices = vector_create(copy->columns, max->arr[1], false);
        vector_t pivot_col_index = vector_find(max_of_cols, 1);

        if (vector_length(pivot_col_index) == 0) {
            matrix_destroy(submatrix);
            matrix_destroy(max);
            vector_destroy(max_of_cols);
            vector_destroy(max_row_indices);
            vector_destroy(pivot_col_index);
            break;
        }

        matrix_t temp = matrix_row_swap(copy, current_row, *vector_at(max_row_indices,
                                    (int) *vector_at(pivot_col_index, 0)) + current_row);
        matrix_destroy(copy);
        copy = temp;

        for (int i = current_row + 1; i < copy->rows; i++) {
            if (*matrix_at(copy, i, current_col) != 0) {
                matrix_t temp = matrix_row_add(copy, current_row, i, -(*matrix_at(copy, i, current_col) /
                                                            *matrix_at(copy, current_row, current_col)));
                matrix_destroy(copy);
                copy = temp;
            }
        }
        if (*vector_at(max_of_cols, 0) == 0) {
            current_col += *vector_at(vector_find(max_of_cols, 1), 0);
        }

        pivot_row_indices[current_col] = current_row;

        current_row++;
        current_col++;

        matrix_destroy(submatrix);
        matrix_destroy(max);
        vector_destroy(max_of_cols);
        vector_destroy(max_row_indices);
        vector_destroy(pivot_col_index);
    }

    // Reduced row echelon form
    for (int i = 0; i < copy->columns; i++) {
        if (pivot_row_indices[i] != -1) {
            matrix_t temp = matrix_row_multiply(copy, pivot_row_indices[i], 
                            1.0 / *matrix_at(copy, pivot_row_indices[i], i));
            matrix_destroy(copy);
            copy = temp;
            for (int j = 0; j < pivot_row_indices[i]; j++) {
                matrix_t temp = matrix_row_add(copy, pivot_row_indices[i], j, 
                                                    -(*matrix_at(copy, j, i)));
                matrix_destroy(copy);
                copy = temp;
            }
        }
    }
    return copy;
}

matrix_t matrix_max(matrix_t matrix, int dim)
{
    if (dim == 0) {
        double arr[2][matrix->rows];
        for (int i = 0; i < matrix->rows; i++) {
            double max = 0;
            double max_index = 0;
            for (int j = 0; j < matrix->columns; j++) {
                if (matrix->arr[i][j] > max) {
                    max = matrix->arr[i][j];
                    max_index = j;
                }
            }
            arr[0][i] = max;
            arr[1][i] = max_index;
        }
        return matrix_create_from_array(2, matrix->rows, arr);
    }
    else if (dim == 1) {
        double arr[2][matrix->columns];
        for (int i = 0; i < matrix->columns; i++) {
            double max = 0;
            double max_index = 0;
            for (int j = 0; j < matrix->rows; j++) {
                if (matrix->arr[j][i] > max) {
                    max = matrix->arr[j][i];
                    max_index = j;
                }
            }
            arr[0][i] = max;
            arr[1][i] = max_index;
        }
        return matrix_create_from_array(2, matrix->columns, arr);
    }
    else {
        return NULL;
    }
}

matrix_t matrix_abs(matrix_t matrix)
{
    double arr[matrix->rows][matrix->columns];
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            arr[i][j] = fabs(matrix->arr[i][j]);
        }
    }
    return matrix_create_from_array(matrix->rows, matrix->columns, arr);
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