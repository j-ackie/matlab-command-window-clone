#include "linalgebra.h"



int main(void)
{
    double arr1[3] = {1, 2, 3};
    double arr2[3] = {2, 3, 4};

    vector_t vector1 = vector_create(arr1, 3, true);
    vector_t vector2 = vector_create(arr2, 3, true);

    vector_t* vectors = malloc(sizeof(vector_t) * 2);
    vectors[0] = vector1;
    vectors[1] = vector2;

    matrix_t matrix = matrix_create(vectors, 2, true);

    matrix_print(matrix);
}