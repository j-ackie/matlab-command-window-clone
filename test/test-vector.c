#include "../src/vector.h"
#include <assert.h>
#include <time.h>

#define CLOCKS_PER_SEC 1000000

static void test_vector_create_destroy(void)
{
    double arr[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(5, arr, true);
    vector_destroy(vector);

    printf("%s passed\n", __func__);
}

static void test_vector_arr(void)
{
    double arr1[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(5, arr1, true);

    double* arr2 = vector_arr(vector);

    for (int i = 0; i < 5; i++) {
        
        assert(arr1[i] == arr2[i]);
    }

    free(arr2);

    vector_destroy(vector);
    
    printf("%s passed\n", __func__);
}

static void test_vector_length(void)
{
    double arr1[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(5, arr1, true);

    assert(vector_length(vector) == 5);

    vector_destroy(vector);

    double arr2[4] = {1, 2, 3, 4};
    vector = vector_create(4, arr2, true);
    assert(vector_length(vector) == 4);

    vector_destroy(vector);

    printf("%s passed\n", __func__);
}

static void test_vector_column(void)
{
    double arr[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(5, arr, true);

    assert(vector_column(vector));

    vector_destroy(vector);

    vector = vector_create(5, arr, false);

    assert(!vector_column(vector));

    vector_destroy(vector);

    printf("%s passed\n", __func__);
}

static void test_vector_at(void)
{
    double arr[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(5, arr, true);

    assert(*vector_at(vector, 0) == 1);
    assert(*vector_at(vector, 1) == 2);
    assert(*vector_at(vector, 2) == 3);
    assert(*vector_at(vector, 3) == 4);
    assert(*vector_at(vector, 4) == 5);

    double* p = vector_at(vector, 0);
    *p += 5;
    assert(*vector_at(vector, 0) == 6);

    assert(vector_at(vector, 5) == NULL);

    vector_destroy(vector);

    printf("%s passed\n", __func__);
}

static void test_vector_transpose()
{
    double arr[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(5, arr, true);

    assert(vector_column(vector));

    vector_t transposed_vector = vector_transpose(vector);

    assert(vector_column(vector) == !vector_column(transposed_vector));

    vector_destroy(vector);
    vector_destroy(transposed_vector);

    printf("%s passed\n", __func__);
}

static void test_vector_add()
{
    double arr1[5] = {1, 2, 3, 4, 5};
    double arr2[5] = {2, 3, 4, 5, 6};

    vector_t vector1 = vector_create(5, arr1, true);
    vector_t vector2 = vector_create(5, arr2, true);

    double arr3[5] = {3, 5, 7, 9, 11};
    vector_t vector3 = vector_create(5, arr3, true);

    double arr4[5] = {0, 0, 0, 0, 0};
    vector_t vector4 = vector_create(5, arr4, true);

    double arr5[3] = {2, 3, 4};
    vector_t vector5 = vector_create(3, arr5, true);

    assert(vector_equals(vector_add(vector1, vector4), vector1));

    assert(vector_equals(vector_add(vector1, vector2), vector3));

    assert(vector_equals(vector_add(NULL, vector1), vector1));

    assert(vector_add(vector1, NULL) == NULL);

    assert(vector_add(vector1, vector5) == NULL);

    vector_destroy(vector1);
    vector_destroy(vector2);
    vector_destroy(vector3);
    vector_destroy(vector4);
    vector_destroy(vector5);

    printf("%s passed\n", __func__);
}

static void test_vector_subtract()
{
    double arr1[5] = {4, 5, 6, 7, 8};
    double arr2[5] = {1, 2, 3, 4, 5};

    vector_t vector1 = vector_create(5, arr1, true);
    vector_t vector2 = vector_create(5, arr2, true);

    double arr3[5] = {3, 3, 3, 3, 3};
    vector_t vector3 = vector_create(5, arr3, true);

    double arr4[5] = {0, 0, 0, 0, 0};
    vector_t vector4 = vector_create(5, arr4, true);

    double arr5[3] = {2, 3, 4};
    vector_t vector5 = vector_create(3, arr5, true);

    double arr6[5] = {-4, -5, -6, -7, -8};
    vector_t vector6 = vector_create(5, arr6, true);

    assert(vector_equals(vector_subtract(vector1, vector4), vector1));

    assert(vector_equals(vector_subtract(vector1, vector2), vector3));

    assert(vector_equals(vector_subtract(NULL, vector1), vector6));

    assert(vector_subtract(vector1, NULL) == NULL);

    assert(vector_subtract(vector1, vector5) == NULL);

    vector_destroy(vector1);
    vector_destroy(vector2);
    vector_destroy(vector3);
    vector_destroy(vector4);
    vector_destroy(vector5);
    vector_destroy(vector6);

    printf("%s passed\n", __func__);
}

static void test_vector_dot_product()
{
    double arr1[5] = {1, 2, 3, 4, 5};
    double arr2[5] = {2, 3, 4, 5, 6};

    vector_t vector1 = vector_create(5, arr1, false);
    vector_t vector2 = vector_create(5, arr2, true);

    assert(vector_dot_product(vector1, vector2) == 70);

    vector_destroy(vector1);
    vector_destroy(vector2);

    printf("%s passed\n", __func__);
}

static void test_vector_scalar_product()
{
    double arr1[5] = {1, 2, 3, 4, 5};
    vector_t vector1 = vector_create(5, arr1, true);

    double arr2[5] = {5, 10, 15, 20, 25};
    vector_t vector2 = vector_create(5, arr2, true);

    double arr3[5] = {0, 0, 0, 0 ,0};
    vector_t vector3 = vector_create(5, arr3, true);

    assert(vector_equals(vector_scalar_product(vector1, 5), vector2));

    assert(vector_equals(vector_scalar_product(vector1, 0), vector3));

    // Check that vector1 wasn't directly changed
    for (int i = 0; i < 5; i++) {
        assert(arr1[i] == *vector_at(vector1, i));
    }

    vector_destroy(vector1);
    vector_destroy(vector2);
    vector_destroy(vector3);

    printf("%s passed\n", __func__);
}

static void test_vector_norm()
{
    /// TODO: Add more tests
    double arr1[2] = {3, 2};
    vector_t vector1 = vector_create(2, arr1, true);

    assert(vector_norm(vector1) == sqrt(13));

    vector_destroy(vector1);
    
    printf("%s passed\n", __func__);
}

static void test_vector_insert()
{
    double arr1[5] = {1, 2, 3, 4, 5};
    vector_t vector1 = vector_create(5, arr1, true);

    double arr2[6] = {1, 2, 20, 3, 4 ,5};
    vector_t vector2 = vector_create(6, arr2, true);
    vector_insert(vector1, 20, 2);

    assert(vector_equals(vector1, vector2));
    assert(vector_length(vector1) == 6);

    double arr3[7] = {3, 1, 2, 20, 3, 4, 5};
    vector_t vector3 = vector_create(7, arr3, true);
    vector_insert(vector1, 3, 0);

    assert(vector_equals(vector1, vector3));
    assert(vector_length(vector1) == 7);

    double arr4[8] = {3, 1, 2, 20, 3, 4, 5, -4};
    vector_t vector4 = vector_create(8, arr4, true);
    vector_insert(vector1, -4, 7);

    assert(vector_equals(vector1, vector4));
    assert(vector_length(vector1) == 8);

    vector_destroy(vector1);
    vector_destroy(vector2);
    vector_destroy(vector3);
    vector_destroy(vector4);

    printf("%s passed\n", __func__);
}

static void test_vector_find(void)
{
    double arr1[5] = {1, 2, 3, 4, 5};
    vector_t vector1 = vector_create(5, arr1, true);

    double arr2[5] = {0, 1, 2, 3, 4};
    vector_t vector2 = vector_create(5, arr2, true);

    assert(vector_equals(vector_find(vector1, 5), vector2));

    double arr3[3] = {0, 1, 2};
    vector_t vector3 = vector_create(3, arr3, true);

    assert(vector_equals(vector_find(vector1, 3), vector3));

    double arr4[5] = {0, 0, 0, 0, 0};
    vector_t vector4 = vector_create(5, arr4, false);

    double arr5[] = {};
    vector_t vector5 = vector_create(0, arr5, false);

    assert(vector_equals(vector_find(vector4, 5), vector5));
    assert(vector_length(vector_find(vector4, 5)) == 0);

    vector_destroy(vector1);
    vector_destroy(vector2);
    vector_destroy(vector3);
    vector_destroy(vector4);
    vector_destroy(vector5);

    printf("%s passed\n", __func__);
}

int main(void) {

    printf("-----------\n");
    printf("test-vector\n");
    printf("-----------\n");

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
    test_vector_insert();
    test_vector_find();

    clock_t end = clock();

    double time = ((double) end - begin) / CLOCKS_PER_SEC * 1000;

    printf("\n%g ms elapsed\n\n", time);

    return 0;
}