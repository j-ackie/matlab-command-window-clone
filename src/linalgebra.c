#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Hello, world!");
    int arr[5] = {1, 2, 3, 4, 5};
    vector_t vector = vector_create(arr, 5, true);
}