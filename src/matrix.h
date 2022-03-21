#pragma once

#include "vector.h"

typedef struct matrix* matrix_t;

// Creates a matrix.
// Precondition: Vectors are the same type of vector. Vectors is not null.
matrix_t matrix_create(vector_t* vectors, int num_vectors, bool column);

void matrix_destroy(matrix_t matrix);

double** matrix_arr(matrix_t matrix);

int matrix_rows(matrix_t matrix);

int matrix_columns(matrix_t matrix);

double* matrix_at(matrix_t matrix, int row, int column);

void matrix_print(matrix_t matrix);
