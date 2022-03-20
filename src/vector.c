#include "vector.h"

/// TODO: Make double arrays instead
struct vector
{
    int* arr;
    int length;
    bool column;
};

vector_t vector_create(int* arr, int arr_size, bool column)
{
    vector_t vector = malloc(sizeof(struct vector));
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

int* vector_arr(vector_t vector)
{
    // Can't return vector->arr because it would allow 
    // vector's arr to be modified directly
    int* arr = malloc(sizeof(int) * vector->length);
    for (int i = 0; i < vector->length; i++) {
        arr[i] = vector->arr[i];
    }
    return arr;
}


int vector_length(vector_t vector)
{
    return vector->length;
}

bool vector_column(vector_t vector)
{
    return vector->column;
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
    else if (vector2 == NULL) {
        return NULL;
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
    else if (vector2 == NULL) {
        return NULL;
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

int vector_dot_product(vector_t vector1, vector_t vector2)
{
    if (!vector1->column && vector2->column) {
        int product = 0;
        for (int i = 0; i < vector1->length; i++) {
            product += vector1->arr[i] * vector2->arr[i];
        }
        return product;
    }
    else {
        return 0;
        /// TODO: Implement matrices
    }
}

vector_t vector_scalar_product(vector_t vector, int scalar)
{
    if (vector == NULL) {
        return NULL;
    }

    int* arr = vector_arr(vector);

    for (int i = 0; i < vector->length; i++) {
        arr[i] *= scalar;
    }
    
    return vector_create(arr, vector->length, vector->column);
}

vector_t vector_norm(vector_t vector)
{
    if (vector == NULL) {
        return NULL;
    }

    double magnitude = 0;

    for (int i = 0; i < vector->length; i++) {
        magnitude += pow(vector->arr[i], 2);
    }

    magnitude = sqrt(magnitude);

    int* arr = vector_arr(vector);
    for (int i = 0; i < vector->length; i++) {
        arr[i] /= magnitude;
    }

    return vector_create(arr, vector->length, vector->column);
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