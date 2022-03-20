#include "linalgebra.h"



int main(void)
{
    printf("Hello, world!\n");
    int arr[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(arr, 5, true);

    // vector_print(vector);

    int* a = vector_at(vector, 2);

    *a += 2;
    // vector_print(vector);

    int arr2[5] = {2, 3, 4, 5, 6};
    vector_t vector2 = vector_create(arr2, 5, true);

    // vector_print(vector2);

    vector_t vector3 = vector_add(vector, vector2);

    vector_print(vector3);

    if (!vector_equals(vector, vector2)) {
        printf("False\n");
    }

    int arr3[5] = {2, 3, 4, 5, 6};
    vector_t vector4 = vector_create(arr3, 5, true);
    bool b = vector_equals(vector4, vector2);
    if (b) {
        printf("True\n");
    }

    int a1[3] = {1, 2, 3};
    vector_t vec1 = vector_create(a1, 3, false);
    
    vector_t vec2 = vector_create(a1, 3, true);

    int h = vector_dot_product(vec1, vec2);
    printf("%i", h);

    vector_destroy(vector);
    vector_destroy(vector2);
    vector_destroy(vector3);
    vector_destroy(vector4);
    vector_destroy(vec1);
    vector_destroy(vec2);
    }