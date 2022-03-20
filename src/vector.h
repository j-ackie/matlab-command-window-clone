#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct vector* vector_t;

// Creates a vector
vector_t vector_create(int* arr, int arr_size, bool column);

// Frees a vector and its arr member
void vector_destroy(vector_t vector);

// Returns a pointer to the index in vector
int* vector_at(vector_t vector, int index);

void vector_transpose(vector_t vector);

vector_t vector_add(vector_t vector1, vector_t vector2);

vector_t vector_subtract(vector_t vector1, vector_t vector2);

int vector_product(vector_t vector1, vector_t vector2);

bool vector_equals(vector_t vector1, vector_t vector2);

bool vector_not_equals(vector_t vector1, vector_t vector2);

// Prints contents of a vector
void vector_print(vector_t vector);