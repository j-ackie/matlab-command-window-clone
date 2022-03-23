#pragma once

#include "vector.h"

typedef struct matrix* matrix_t;

// Creates a matrix.
// Precondition: Vectors are the same type of vector. Vectors is not null.
matrix_t matrix_create_from_vectors(int num_vectors, vector_t vectors[num_vectors], bool column);

// Creates a matrix.
matrix_t matrix_create_from_array(int rows, int columns, double arr[rows][columns]);

// Frees a matrix and its arr member.
void matrix_destroy(matrix_t matrix);

// Copies and returns a malloced array of a matrix.
double** matrix_arr(matrix_t matrix);

// Frees the malloced array.
void matrix_destroy_arr(double** arr, int rows);

// Returns the number of rows in a matrix.
int matrix_rows(matrix_t matrix);

// Returns the number of columns in a matrix.
int matrix_columns(matrix_t matrix);

// Returns a pointer to the index in a matrix.
double* matrix_at(matrix_t matrix, int row, int column);

// Transposes a matrix.
matrix_t matrix_transpose(matrix_t matrix);

// Returns the sum of two matrices.
matrix_t matrix_add(matrix_t matrix1, matrix_t matrix2);

// Returns the difference between two matrices.
matrix_t matrix_subtract(matrix_t matrix1, matrix_t matrix2);

// Returns the scalar product of a matrix and a scalar.
matrix_t matrix_scalar_product(matrix_t matrix1, double scalar);

// Checks if two matrices have same elements, number of rows, 
// and number of columns. 
bool matrix_equals(matrix_t matrix1, matrix_t matrix2);

// Checks if two matrices have different elements, number of rows,
// and number of columns.
bool matrix_not_equals(matrix_t matrix1, matrix_t matrix2);

// Prints contents of a matrix.
void matrix_print(matrix_t matrix);
