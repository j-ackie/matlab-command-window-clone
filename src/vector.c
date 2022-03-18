#include "vector.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct vector
{
    int* arr;
    int length;
    bool column;
};

typedef struct vector vector;

vector_t vector_create(int* arr, int arr_size, bool column)
{
    vector* vector = malloc(sizeof(vector));
    if (!vector) {
        return NULL;
    }

    vector->arr = malloc(sizeof(int) * arr_size);
    vector->length = arr_size;
    vector->column = column;

    for (int i = 0; i < arr_size; i++) {
        vector->arr[i] = arr[i];
    }

    return vector;
}
