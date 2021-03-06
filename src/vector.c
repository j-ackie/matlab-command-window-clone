#include "vector.h"
#include "util.h"

#include <errno.h>
#include <string.h>

struct vector
{
    double* arr;
    int length;
    bool column;
};

vector_t vector_create(int length, double arr[length], bool column)
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

vector_t vector_create_from_stdin(char* line)
{
    char contents[strlen(line) - 1];
    strncpy(contents, line + 1, strlen(line) - 1);
    contents[strlen(line) - 2] = '\0';

    char contents_copy[strlen(line)- 1];
    strcpy(contents_copy, contents);

    int length = 0;

    char* split = strtok(contents, " ");

    while (split != NULL) {
        split = strtok(NULL, " ");
        length++;
    }

    split = strtok(contents_copy, " ");

    double arr[length];
    int i = 0;
    while (split != NULL) {
        char* end;

        errno = 0;

        arr[i] = strtod(split, &end);

        if (errno != 0 || *end != '\0') {
            fprintf(stderr, "Invalid expression '%s'.\n", split);
            return NULL;
        } 

        split = strtok(NULL, " ");
        i++;
    }

    return vector_create(length, arr, false);
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
    return vector_create(vector->length, vector->arr, !vector->column);
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
        return vector_create(vector1->length, arr, vector1->column);
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
        return vector_create(vector2->length, arr, vector2->column);
    }
    else if (vector2 == NULL) {
        return NULL;
    }
    else if ((vector1->column && vector2->column) && vector1->length == vector2->length) {
        double arr[vector1->length];
        for (int i = 0; i < vector1->length; i++) {
            arr[i] = vector1->arr[i] - vector2->arr[i];
        }
        return vector_create(vector1->length, arr, vector1->column);
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

    vector_t product = vector_create(vector->length, vector->arr, vector->column);

    for (int i = 0; i < product->length; i++) {
        product->arr[i] *= scalar;
    }

    return product;
}

double vector_norm(vector_t vector)
{
    double magnitude = 0;

    for (int i = 0; i < vector->length; i++) {
        magnitude += pow(vector->arr[i], 2);
    }

    return sqrt(magnitude);
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

vector_t vector_find(vector_t vector, int n)
{
    double arr[n];
    int counter = 0;
    for (int i = 0; i < vector->length; i++) {
        if (vector->arr[i] > 0) {
            arr[counter] = i;
            counter++;
            if (counter >= n) {
                break;
            }
        }
    }
    return vector_create(counter, arr, vector->column);
}

bool vector_equals(vector_t vector1, vector_t vector2)
{
    if (vector1->length == vector2->length && ((vector1->column && vector2->column)
        || (!vector1->column && !vector2->column))) {
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