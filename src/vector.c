#include "vector.h"

struct vector
{
    double* arr;
    int length;
    bool column;
};

vector_t vector_create(double arr[], int length, bool column)
{
    vector_t vector = malloc(sizeof(struct vector));
    if (!vector) {
        return NULL;
    }

    vector->arr = malloc(sizeof(double) * length);
    vector->length = length;
    vector->column = column;

    for (int i = 0; i < length; i++) {
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

double* vector_arr(vector_t vector)
{
    // Can't return vector->arr because it would allow 
    // vector's arr to be modified directly
    double* arr = malloc(sizeof(double) * vector->length);
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

double* vector_at(vector_t vector, int index)
{
    if (index >= vector->length || index < 0) {
        return NULL;
    }
    return &vector->arr[index];
}

vector_t vector_transpose(vector_t vector)
{
    return vector_create(vector->arr, vector->length, !vector->column);
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
        double arr[vector1->length];
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
        double arr[vector2->length];
        for (int i = 0; i < vector2->length; i++) {
            arr[i] = vector2->arr[i] * -1;
        }
        return vector_create(arr, vector2->length, vector2->column);
    }
    else if (vector2 == NULL) {
        return NULL;
    }
    else if ((vector1->column && vector2->column) && vector1->length == vector2->length) {
        double arr[vector1->length];
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

double vector_dot_product(vector_t vector1, vector_t vector2)
{
    if (!vector1->column && vector2->column) {
        double product = 0;
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

vector_t vector_scalar_product(vector_t vector, double scalar)
{
    if (vector == NULL) {
        return NULL;
    }

    vector_t product = vector_create(vector->arr, vector->length, vector->column);

    for (int i = 0; i < product->length; i++) {
        product->arr[i] *= scalar;
    }

    return product;
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

    double* arr = vector_arr(vector);

    for (int i = 0; i < vector->length; i++) {
        arr[i] /= magnitude;
    }

    vector_t norm = vector_create(arr, vector->length, vector->column);

    free(arr);

    return norm;
}

void vector_insert(vector_t vector, double value, int index)
{
    double* arr = malloc(sizeof(double) * (vector->length + 1));

    for (int i = 0; i < vector->length + 1; i++) {
        if (i == index) {
            arr[i] = value;
        }
        else if (i > index){
            arr[i] = vector->arr[i - 1];
        }
        else {
            arr[i] = vector->arr[i];
        }
    }

    free(vector->arr);

    vector->arr = arr;
    vector->length += 1;
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
            printf("%lf\n", vector->arr[i]);
        }
    }
    else {
        for (int i = 0; i < vector->length; i++) {
            printf("%lf ", vector->arr[i]);
        }
        printf("\n");
    }
}