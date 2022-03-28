#include "../src/command.h"

#include <stdio.h>
#include <assert.h>
#include <time.h>

static void test_check_vector(void)
{
    char str1[] = "[4 2 4]";
    assert(check_vector(str1));

    char str2[] = "[4 2 4";
    assert(!check_vector(str2));

    char str3[] = "4 2 4";
    assert(!check_vector(str3));

    char str4[] = "[]";
    assert(check_vector(str4));

    printf("%s passed\n", __func__);
}

int main(void)
{
    // int a = 4;

    // int* b = &a;

    // void* ptr = b;

    // printf("%i", *(int*)ptr);

    printf("------------\n");
    printf("test-command\n");
    printf("------------\n");

    clock_t begin = clock();

    
    test_check_vector();

    clock_t end = clock();

    double time = ((double) end - begin) / CLOCKS_PER_SEC * 1000;

    printf("\n%g ms elapsed\n\n", time);

    return 0;
}