#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vector* vector_t;

// Creates a vector.
vector_t vector_create(int length, double arr[], bool column);

// Frees a vector and its arr member.
void vector_destroy(vector_t vector);

// Copies and returns a malloced array of a vector.
double* vector_arr(vector_t vector);

// Returns the length of a vector.
int vector_length(vector_t vector);

// Returns the column bool of a vector.
bool vector_column(vector_t vector);

// Returns a pointer to the index in a vector.
double* vector_at(vector_t vector, int index);

// Returns the transpose of a vector by setting column to opposite bool.
vector_t vector_transpose(vector_t vector);

// Returns the sum of two vectors.
vector_t vector_add(vector_t vector1, vector_t vector2);

// Returns the difference between two vectors.
vector_t vector_subtract(vector_t vector1, vector_t vector2);

// Returns the dot product of two vectors.
// Precondition: vector1 and vector 2 have the same length and are not NULL.
double vector_dot_product(vector_t vector1, vector_t vector2);

// Returns the scalar product of a vector and a scalar.
vector_t vector_scalar_product(vector_t vector, double scalar);

// Returns the normalized vector of a vector.
// Precondition: vector is not NULL.
double vector_norm(vector_t vector);

// Inserts an element at a specified index of a vector.
// Precondition: index is valid.
void vector_insert(vector_t vector, double value, int index);

vector_t vector_find(vector_t vector, int n);

// Checks if two vectors have same elements, length, and vector type.
bool vector_equals(vector_t vector1, vector_t vector2);

// Checks if two vectors have different elements, length, and vector type.
bool vector_not_equals(vector_t vector1, vector_t vector2);

// Prints contents of a vector
void vector_print(vector_t vector);