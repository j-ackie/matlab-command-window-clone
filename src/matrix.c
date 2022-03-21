#include "matrix.h"

struct matrix
{
    double* arr;
    int rows;
    int columns;
};

matrix_t matrix_create(vector_t* vectors, int num_vectors, bool column)
{
    matrix_t matrix = malloc(sizeof(struct matrix));
    if (!matrix) {
        return NULL;
    }

    if (column) {
        matrix->rows = 4;
        matrix->columns = num_vectors;
    }

    vector_print(vectors[0]);
    // else {
    //     matrix->rows = num_vectors;
    //     matrix->columns = vector_length(vectors[0]);
    // }
    // matrix->arr = malloc(sizeof(double) * matrix->rows * matrix->columns);
    return NULL;
}