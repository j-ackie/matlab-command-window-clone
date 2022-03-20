#include "vector.h"

struct vector
{
    int* arr;
    int length;
    bool column;
};

typedef struct vector vector;

vector_t vector_create(int* arr, int arr_size, bool column)
{
    vector_t vector = malloc(sizeof(vector));
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

void vector_destroy(vector_t vector)
{
    if (vector == NULL) {
        return;
    }
    free(vector->arr);
    free(vector);
}

int* vector_at(vector_t vector, int index)
{
    if (index >= vector->length || index < 0) {
        return NULL;
    }
    return &vector->arr[index];
}

void vector_transpose(vector_t vector)
{
    vector->column = !vector->column;
}

vector_t vector_add(vector_t vector1, vector_t vector2)
{
    if (vector1 == NULL && vector2 != NULL) {
        return vector2;
    }
    if ((vector1->column && vector2->column) && vector1->length == vector2->length) {
        int arr[vector1->length];
        for (int i = 0; i < vector1->length; i++) {
            arr[i] = vector1->arr[i] + vector2->arr[i];
        }
        return vector_create(arr, vector1->length, vector1->column);
    }
    else if (vector1->length == vector2->length) {
        /// TODO: Implement matrices
    }
    return NULL;
}

vector_t vector_subtract(vector_t vector1, vector_t vector2)
{
    if (vector1 == NULL && vector2 != NULL) {
        int arr[vector2->length];
        for (int i = 0; i < vector2->length; i++) {
            arr[i] = vector2->arr[i] * -1;
        }
        return vector_create(arr, vector2->length, vector2->column);
    }
    else if ((vector1->column && vector2->column) && vector1->length == vector2->length) {
        int arr[vector1->length];
        for (int i = 0; i < vector1->length; i++) {
            arr[i] = vector1->arr[i] - vector2->arr[i];
        }
        return vector_create(arr, vector1->length, vector1->column);
    }
    else if (vector1->length == vector2->length) {
        /// TODO: Implement matrices
    }
    return NULL;
}

int vector_product(vector_t vector1, vector_t vector2)
{
    if (vector1->length == vector2->length) {
        if (!vector1->column && vector2->column) {
            int product = 0;
            for (int i = 0; i < vector1->length; i++) {
                product += vector1->arr[i] * vector2->arr[i];
            }
            return product;
        }
        else if (vector1->column && !vector2->column) {
            /// TODO: Implement matrices
        }
    }
}

vector_t vector_scalar_product(vector_t vector, int scalar)
{
    for (int i = 0; i < vector->length; i++) {
        
    }
}

bool vector_equals(vector_t vector1, vector_t vector2)
{
    if (vector1->length == vector2->length && (vector1->column && vector2->column)) {
        for (int i = 0; i < vector1->length; i++) {
            if (vector1->arr[i] != vector2->arr[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool vector_not_equals(vector_t vector1, vector_t vector2)
{
    return !vector_equals(vector1, vector2);
}

void vector_print(vector_t vector)
{
    if (vector->column) {
        for (int i = 0; i < vector->length; i++) {
            printf("%i\n", vector->arr[i]);
        }
    }
    else {
        for (int i = 0; i < vector->length; i++) {
            printf("%i ", vector->arr[i]);
        }
        printf("\n");
    }
}