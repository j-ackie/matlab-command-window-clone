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

    matrix_t matrix1 = matrix_create_from_vectors(2, vectors, true);

    vector_destroy(vector1);
    vector_destroy(vector2);

    // matrix_print(matrix1);

    matrix_destroy(matrix1);

    double arr3[2][3] = {{1, 2, 3}, {2, 3, 4}};

    matrix_t matrix2 = matrix_create_from_array(2, 3, arr3);

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

    vector_t vectors[2] = {vector1, vector2};

    matrix_t matrix = matrix_create_from_vectors(2, vectors, true);

    vector_destroy(vector1);
    vector_destroy(vector2);

    double arr3[3][2] = {{1, 2}, {2, 3}, {3, 4}};

    double** arr4 = matrix_arr(matrix);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            assert(arr3[i][j] == arr4[i][j]);
        }
    }

    matrix_destroy_arr(arr4, matrix_rows(matrix));

    matrix_destroy(matrix);

    printf("%s passed\n", __func__);
}

static void test_matrix_at(void)
{
    double arr[2][3] = {{1, 2, 3}, {2, 3, 4}};
    matrix_t matrix = matrix_create_from_array(2, 3, arr);

    assert(*matrix_at(matrix, 0, 0) == 1);
    assert(*matrix_at(matrix, 0, 1) == 2);
    assert(*matrix_at(matrix, 0, 2) == 3);
    assert(*matrix_at(matrix, 1, 0) == 2);
    assert(*matrix_at(matrix, 1, 1) == 3);
    assert(*matrix_at(matrix, 1, 2) == 4);

    double* p = matrix_at(matrix, 0, 2);
    *p += 5;
    assert(*matrix_at(matrix, 0, 2) == 8);

    assert(matrix_at(matrix, 5, 5) == NULL);

    matrix_destroy(matrix);

    printf("%s passed\n", __func__);
}

static void test_matrix_transpose(void)
{
    double arr1[2][3] = {{1, 2, 3}, {2, 3, 4}};
    matrix_t matrix = matrix_create_from_array(2, 3, arr1);

    matrix_t tranposed_matrix = matrix_transpose(matrix);

    double arr2[3][2] = {{1, 2}, {2, 3}, {3, 4}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            assert(*matrix_at(tranposed_matrix, i, j) == arr2[i][j]);
        }
    }

    matrix_destroy(matrix);
    matrix_destroy(tranposed_matrix);

    printf("%s passed\n", __func__);
}

static void test_matrix_add(void)
{
    double arr1[2][3] = {{1, 2, 3}, {2, 3, 4}};
    matrix_t matrix1 = matrix_create_from_array(2, 3, arr1);

    double arr2[2][3] = {{2, 3, 4}, {3, 4, 5}};
    matrix_t matrix2 = matrix_create_from_array(2, 3, arr2);

    double arr3[2][3] = {{3, 5, 7}, {5, 7, 9}};
    matrix_t matrix3 = matrix_create_from_array(2, 3, arr3);

    double arr4[2][2] = {{1, 2}, {2, 4}};
    matrix_t matrix4 = matrix_create_from_array(2, 2, arr4);

    matrix_t sum = matrix_add(matrix1, matrix2);

    assert(matrix_equals(matrix3, sum));
    
    assert(matrix_add(matrix1, matrix4) == NULL);

    matrix_destroy(matrix1);
    matrix_destroy(matrix2);
    matrix_destroy(matrix3);
    matrix_destroy(sum);

    printf("%s passed\n", __func__);
}

static void test_matrix_subtract(void)
{
    printf("%s passed\n", __func__);
}

static void test_matrix_scalar_product(void)
{
    double arr1[2][3] = {{1, 2, 3}, {2, 3, 4}};
    matrix_t matrix1 = matrix_create_from_array(2, 3, arr1);

    double arr2[2][3] = {{5, 10, 15}, {10, 15, 20}};
    matrix_t matrix2 = matrix_create_from_array(2, 3, arr2);

    assert(matrix_equals(matrix_scalar_product(matrix1, 5), matrix2));

    matrix_destroy(matrix1);
    matrix_destroy(matrix2);

    printf("%s passed\n", __func__);
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
    test_matrix_add();
    test_matrix_subtract();
    test_matrix_scalar_product();

    clock_t end = clock();

    double time = ((double) end - begin) / CLOCKS_PER_SEC * 1000;

    printf("\n%g ms elapsed\n\n", time);
}