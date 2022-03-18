#pragma once

#include <stdbool.h>

typedef struct vector* vector_t;

vector_t vector_create(int* arr, int arr_size, bool column);