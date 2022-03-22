#include "../src/matrix.h"
#include <assert.h>
#include <time.h>

static void test_matrix_create_destroy(void)
{
    double arr1[3] = {1, 2, 3};
    double arr2[3] = {2, 3, 4};

    vector_t vector1 = vector_create(arr1, 3, true);
    vector_t vector2 = vector_create(arr2, 3, true);

    vector_t vectors[2] = {vector1, vector2};

    matrix_t matrix1 = matrix_create_from_vectors(vectors, 2, true);

    // matrix_print(matrix1);

    matrix_destroy(matrix1);

    double** arr3 = malloc(sizeof(double*) * 2);
    for (int i = 0; i < 2; i++) {
        arr3[i] = malloc(sizeof(double) * 3);
        for (int j = 0; j < 3; j++) {
            arr3[i][j] = i + (j + 1);
        }
    }

    matrix_t matrix2 = matrix_create_from_array(arr3, 2, 3);

    for (int i = 0; i < 2; i++) {
        free(arr3[i]);
    }
    free(arr3);

    // matrix_print(matrix2);

    matrix_destroy(matrix2);

    printf("%s passed\n", __func__);
}

static void test_matrix_arr(void)
{
    double arr1[3] = {1, 2, 3};
    double arr2[3] = {2, 3, 4};

    vector_t vector1 = vector_create(arr1, 3, true);
    vector_t vector2 = vector_create(arr2, 3, true);

    vector_t* vectors = malloc(sizeof(vector_t) * 2);
    vectors[0] = vector1;
    vectors[1] = vector2;

    matrix_t matrix = matrix_create_from_vectors(vectors, 2, true);

    double arr3[3][2] = {{1, 2}, {2, 3}, {3, 4}};

    double** arr4 = matrix_arr(matrix);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            assert(arr3[i][j] == arr4[i][j]);
        }
    }

    free(arr4);

    matrix_destroy(matrix);

    printf("%s passed\n", __func__);
}

static void test_matrix_at(void)
{

}

static void test_matrix_transpose(void)
{
    
}

int main(void)
{
    printf("-----------\n");
    printf("test-matrix\n");
    printf("-----------\n");

    clock_t begin = clock();

    test_matrix_create_destroy();
    test_matrix_arr();
    test_matrix_at();
    test_matrix_transpose();

    clock_t end = clock();

    double time = ((double) end - begin) / CLOCKS_PER_SEC * 1000;

    printf("\n%g ms elapsed\n\n", time);
}