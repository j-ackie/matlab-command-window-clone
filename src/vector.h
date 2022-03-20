#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vector* vector_t;

// Creates a vector.
vector_t vector_create(int* arr, int arr_size, bool column);

// Frees a vector and its arr member.
void vector_destroy(vector_t vector);

// Copies and returns a malloced array of a vector.
int* vector_arr(vector_t vector);

// Returns the length of a vector.
int vector_length(vector_t vector);

// Returns the column bool of a vector.
bool vector_column(vector_t vector);

// Returns a pointer to the index in vector.
int* vector_at(vector_t vector, int index);

// Transposes a vector by setting column to opposite bool.
void vector_transpose(vector_t vector);

// Returns the sum of two vectors.
vector_t vector_add(vector_t vector1, vector_t vector2);

// Returns the difference between two vectors.
vector_t vector_subtract(vector_t vector1, vector_t vector2);

// Returns the dot product of two vectors.
// Precondition: vector1 and vector 2 have the same length and are not NULL.
int vector_dot_product(vector_t vector1, vector_t vector2);

// Returns the scalar product of a vector and a scalar.
vector_t vector_scalar_product(vector_t vector, int scalar);

// Returns the normalized vector of a vector.
vector_t vector_norm(vector_t vector);

// Checks if two vectors have same elements, length, and vector type.
bool vector_equals(vector_t vector1, vector_t vector2);

// Checks if two vectors have different elements, length, and vector type.
bool vector_not_equals(vector_t vector1, vector_t vector2);

// Prints contents of a vector
void vector_print(vector_t vector);