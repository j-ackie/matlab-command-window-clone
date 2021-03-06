#include "../src/matrix.h"
#include <assert.h>
#include <time.h>

static void test_matrix_create_destroy(void)
{
    double arr1[3] = {1, 2, 3};
    double arr2[3] = {2, 3, 4};

    vector_t vector1 = vector_create(3, arr1, true);
    vector_t vector2 = vector_create(3, arr2, true);

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

    vector_t vector1 = vector_create(3, arr1, true);
    vector_t vector2 = vector_create(3, arr2, true);

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

static void test_matrix_slice(void)
{
    double arr1[2][3] = {{1, 2, 3}, {2, 3, 4}};
    matrix_t matrix1 = matrix_create_from_array(2, 3, arr1);

    double arr2[1][2] = {{3, 4}};
    matrix_t matrix2 = matrix_create_from_array(1, 2, arr2);

    assert(matrix_equals(matrix_slice(matrix1, 1, 1, 1, 2), matrix2));

    matrix_destroy(matrix1);
    matrix_destroy(matrix2);

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
    double arr1[2][3] = {{1, 2, 3}, {2, 3, 4}};
    matrix_t matrix1 = matrix_create_from_array(2, 3, arr1);

    double arr2[2][3] = {{1, 2, 3}, {0, 4, 1}};
    matrix_t matrix2 = matrix_create_from_array(2, 3, arr2);

    double arr3[2][3] = {{0, 0, 0}, {2, -1, 3}};
    matrix_t matrix3 = matrix_create_from_array(2, 3, arr3);

    assert(matrix_equals(matrix_subtract(matrix1, matrix2), matrix3));

    matrix_destroy(matrix1);
    matrix_destroy(matrix2);
    matrix_destroy(matrix3);

    printf("%s passed\n", __func__);
}

static void test_matrix_multiply(void)
{
    double arr1[2][3] = {{1, 2, 3}, {2, 3, 4}};
    matrix_t matrix1 = matrix_create_from_array(2, 3, arr1);

    double arr2[3][2] = {{1, 2}, {2, 3}, {3, 4}};
    matrix_t matrix2 = matrix_create_from_array(3, 2, arr2);

    double arr3[2][2] = {{14, 20}, {20, 29}};
    matrix_t matrix3 = matrix_create_from_array(2, 2, arr3);

    double arr4[2][3] = {{4, 5, 6}, {6, 7, 8}};
    matrix_t matrix4 = matrix_create_from_array(2, 3, arr4);

    assert(matrix_equals(matrix_product(matrix1, matrix2), matrix3));
    
    assert(matrix_product(matrix1, matrix4) == NULL);

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

static void test_matrix_row_swap(void)
{
    double arr1[2][3] = {{1, 2, 3}, {2, 3, 4}};
    matrix_t matrix1 = matrix_create_from_array(2, 3, arr1);

    double arr2[2][3] = {{2, 3, 4}, {1, 2, 3}};
    matrix_t matrix2 = matrix_create_from_array(2, 3, arr2);

    assert(matrix_equals(matrix_row_swap(matrix1, 0, 1), matrix2));

    matrix_destroy(matrix1);
    matrix_destroy(matrix2);

    printf("%s passed\n", __func__);
}

static void test_matrix_row_multiply(void)
{
    double arr1[2][3] = {{1, 2, 3}, {2, 3, 4}};
    matrix_t matrix1 = matrix_create_from_array(2, 3, arr1);

    double arr2[2][3] = {{5, 10, 15}, {2, 3, 4}};
    matrix_t matrix2 = matrix_create_from_array(2, 3, arr2);

    assert(matrix_equals(matrix_row_multiply(matrix1, 0, 5), matrix2));

    matrix_destroy(matrix1);
    matrix_destroy(matrix2);

    printf("%s passed\n", __func__);
}

static void test_matrix_row_add(void)
{
    double arr1[2][3] = {{1, 2, 3}, {2, 3, 4}};
    matrix_t matrix1 = matrix_create_from_array(2, 3, arr1);

    double arr2[2][3] = {{1, 2, 3}, {7, 13, 19}};
    matrix_t matrix2 = matrix_create_from_array(2, 3, arr2);

    assert(matrix_equals(matrix_row_add(matrix1, 0, 1, 5), matrix2));

    matrix_destroy(matrix1);
    matrix_destroy(matrix2);

    printf("%s passed\n", __func__);
}

static void test_matrix_rref(void)
{
    double arr1[3][3] = {{4, 5, 7}, {-4, 7, 2}, {8, 2 ,1}};
    matrix_t matrix1 = matrix_create_from_array(3, 3, arr1);

    double arr2[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    matrix_t matrix2 = matrix_create_from_array(3, 3, arr2);

    assert(matrix_equals(matrix_rref(matrix1), matrix2));

    matrix_destroy(matrix1);
    matrix_destroy(matrix2);

    printf("%s passed\n", __func__);
}

static void test_matrix_max(void)
{
    double arr1[2][3] = {{1, 2, 3}, {2, 3, 4}};
    matrix_t matrix1 = matrix_create_from_array(2, 3, arr1);

    double arr2[2][3] = {{2, 3, 4}, {1, 1, 1}};
    matrix_t matrix2 = matrix_create_from_array(2, 3, arr2);

    assert(matrix_equals(matrix_max(matrix1, 1), matrix2));

    double arr3[2][2] = {{3, 4}, {2, 2}};
    matrix_t matrix3 = matrix_create_from_array(2, 2, arr3);

    assert(matrix_equals(matrix_max(matrix1, 0), matrix3));

    matrix_destroy(matrix1);
    matrix_destroy(matrix2);
    matrix_destroy(matrix3);
    
    printf("%s passed\n", __func__);
}

static void test_matrix_abs(void)
{
    double arr1[2][3] = {{1, 2, 3}, {-2, -3, -4}};
    matrix_t matrix1 = matrix_create_from_array(2, 3, arr1);

    double arr2[2][3] = {{1, 2, 3}, {2, 3, 4}};
    matrix_t matrix2 = matrix_create_from_array(2, 3, arr2);

    assert(matrix_equals(matrix_abs(matrix1), matrix2));

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
    test_matrix_slice();
    test_matrix_at();
    test_matrix_transpose();
    test_matrix_add();
    test_matrix_subtract();
    test_matrix_multiply();
    test_matrix_scalar_product();
    test_matrix_row_swap();
    test_matrix_row_multiply();
    test_matrix_row_add();
    test_matrix_rref();
    test_matrix_max();
    test_matrix_abs();

    clock_t end = clock();

    double time = ((double) end - begin) / CLOCKS_PER_SEC * 1000;

    printf("\n%g ms elapsed\n\n", time);

    return 0;
}