#pragma once

#include "vector.h"

typedef struct matrix* matrix_t;

// Creates a matrix.
// Precondition: Vectors are the same type of vector. Vectors is not null.
matrix_t matrix_create(vector_t* vectors, int num_vectors, bool column);
