#include "../src/vector.h"
#include <assert.h>
#include <time.h>

#define CLOCKS_PER_SEC 1000000

static void test_vector_create_destroy(void)
{
    int arr[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(arr, 5, true);
    vector_destroy(vector);

    printf("%s passed\n", __func__);
}

static void test_vector_arr(void)
{
    int arr[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(arr, 5, true);

    for (int i = 0; i < 5; i++) {
        assert(arr[i] == vector_arr(vector)[i]);
    }

    vector_destroy(vector);
    
    printf("%s passed\n", __func__);
}

static void test_vector_length(void)
{
    int arr1[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(arr1, 5, true);

    assert(vector_length(vector) == 5);

    vector_destroy(vector);

    int arr2[4] = {1, 2, 3, 4};
    vector = vector_create(arr2, 4, true);
    assert(vector_length(vector) == 4);

    vector_destroy(vector);

    printf("%s passed\n", __func__);
}

static void test_vector_column(void)
{
    int arr[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(arr, 5, true);

    assert(vector_column(vector));

    vector_destroy(vector);

    vector = vector_create(arr, 5, false);

    assert(!vector_column(vector));

    vector_destroy(vector);

    printf("%s passed\n", __func__);
}

static void test_vector_at(void)
{
    int arr[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(arr, 5, true);

    assert(*vector_at(vector, 0) == 1);
    assert(*vector_at(vector, 1) == 2);
    assert(*vector_at(vector, 2) == 3);
    assert(*vector_at(vector, 3) == 4);
    assert(*vector_at(vector, 4) == 5);

    int* p = vector_at(vector, 0);
    *p += 5;
    assert(*vector_at(vector, 0) == 6);

    assert(vector_at(vector, 5) == NULL);

    vector_destroy(vector);

    printf("%s passed\n", __func__);
}

static void test_vector_transpose()
{
    int arr[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(arr, 5, true);

    assert(vector_column(vector));

    vector_transpose(vector);

    assert(!vector_column(vector));

    printf("%s passed\n", __func__);
}

static void test_vector_add()
{
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[5] = {2, 3, 4, 5, 6};

    vector_t vector1 = vector_create(arr1, 5, true);
    vector_t vector2 = vector_create(arr2, 5, true);

    int arr3[5] = {3, 5, 7, 9, 11};
    vector_t vector3 = vector_create(arr3, 5, true);

    int arr4[5] = {0, 0, 0, 0, 0};
    vector_t vector4 = vector_create(arr4, 5, true);

    int arr5[3] = {2, 3, 4};
    vector_t vector5 = vector_create(arr5, 3, true);

    assert(vector_equals(vector_add(vector1, vector4), vector1));

    assert(vector_equals(vector_add(vector1, vector2), vector3));

    assert(vector_equals(vector_add(NULL, vector1), vector1));

    assert(vector_add(vector1, NULL) == NULL);

    assert(vector_add(vector1, vector5) == NULL);

    printf("%s passed\n", __func__);
}

static void test_vector_subtract()
{
    int arr1[5] = {4, 5, 6, 7, 8};
    int arr2[5] = {1, 2, 3, 4, 5};

    vector_t vector1 = vector_create(arr1, 5, true);
    vector_t vector2 = vector_create(arr2, 5, true);

    int arr3[5] = {3, 3, 3, 3, 3};
    vector_t vector3 = vector_create(arr3, 5, true);

    int arr4[5] = {0, 0, 0, 0, 0};
    vector_t vector4 = vector_create(arr4, 5, true);

    int arr5[3] = {2, 3, 4};
    vector_t vector5 = vector_create(arr5, 3, true);

    int arr6[5] = {-4, -5, -6, -7, -8};
    vector_t vector6 = vector_create(arr6, 5, true);

    assert(vector_equals(vector_subtract(vector1, vector4), vector1));

    assert(vector_equals(vector_subtract(vector1, vector2), vector3));

    assert(vector_equals(vector_subtract(NULL, vector1), vector6));

    assert(vector_subtract(vector1, NULL) == NULL);

    assert(vector_subtract(vector1, vector5) == NULL);

    printf("%s passed\n", __func__);
}

static void test_vector_dot_product()
{
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[5] = {2, 3, 4, 5, 6};

    vector_t vector1 = vector_create(arr1, 5, false);
    vector_t vector2 = vector_create(arr2, 5, true);

    assert(vector_dot_product(vector1, vector2) == 70);

    printf("%s passed\n", __func__);
}

static void test_vector_scalar_product()
{
    int arr1[5] = {1, 2, 3, 4, 5};
    vector_t vector1 = vector_create(arr1, 5, true);

    int arr2[5] = {5, 10, 15, 20, 25};
    vector_t vector2 = vector_create(arr2, 5, true);

    int arr3[5] = {0, 0, 0, 0 ,0};
    vector_t vector3 = vector_create(arr3, 5, true);

    assert(vector_equals(vector_scalar_product(vector1, 5), vector2));

    assert(vector_equals(vector_scalar_product(vector1, 0), vector3));

    // Check that vector1 wasn't directly changed
    for (int i = 0; i < 5; i++) {
        assert(arr1[i] == vector_arr(vector1)[i]);
    }

    printf("%s passed\n", __func__);
}

static void test_vector_norm()
{
    /// TODO: Add more tests
    int arr1[2] = {0, 1};
    vector_t vector1 = vector_create(arr1, 2, true);

    assert(vector_equals(vector_norm(vector1), vector1));
    
    printf("%s passed\n", __func__);
}

int main(void) {
    clock_t begin = clock();

    test_vector_create_destroy();
    test_vector_arr();
    test_vector_length();
    test_vector_column();
    test_vector_at();
    test_vector_transpose();
    test_vector_add();
    test_vector_subtract();
    test_vector_dot_product();
    test_vector_scalar_product();
    test_vector_norm();

    clock_t end = clock();

    double time = ((double) end - begin) / CLOCKS_PER_SEC * 1000;

    printf("%g ms elapsed \n", time);
}