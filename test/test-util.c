#include "../src/util.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

static void test_lstrip(void)
{
    char str1[] = "abc";
    lstrip(str1);
    assert(strcmp("abc", str1) == 0);

    char str2[] = "  abc";
    lstrip(str2);
    assert(strcmp("abc", str2) == 0);

    char str3[] = "  abc  ";
    lstrip(str3);
    assert(strcmp("abc  ", str3) == 0);


    char str4[] = "   ";
    lstrip(str4);
    assert(strcmp("", str4) == 0);

    printf("%s passed\n", __func__);
}



static void test_rstrip(void)
{
    char str1[] = "abc";
    rstrip(str1);
    assert(strcmp("abc", str1) == 0);

    char str2[] = "abc  ";
    rstrip(str2);
    assert(strcmp("abc", str2) == 0);

    char str3[] = "  abc  ";
    rstrip(str3);
    assert(strcmp("  abc", str3) == 0);

    char str4[] = "   ";
    rstrip(str4);
    assert(strcmp("", str4) == 0);

    printf("%s passed\n", __func__);
}

static void test_strip(void)
{
    char str1[] = "abc";
    strip(str1);
    assert(strcmp("abc", str1) == 0);

    char str2[] = "abc  ";
    strip(str2);
    assert(strcmp("abc", str2) == 0);

    char str3[] = "  abc";
    strip(str3);
    assert(strcmp("abc", str3) == 0);

    char str4[] = "  abc  ";
    strip(str4);
    assert(strcmp("abc", str4) == 0);

    char str5[] = "   ";
    strip(str5);
    assert(strcmp("", str5) == 0);

    printf("%s passed\n", __func__);
}

static void test_check_exit(void)
{
    assert(check_quit("quit"));
    assert(check_quit("exit"));
    assert(!check_quit("hi"));
    assert(!check_quit("ddquit"));
    printf("%s passed\n", __func__);
}



int main(void)
{   
    printf("---------\n");
    printf("test-util\n");
    printf("---------\n");

    clock_t begin = clock();

    test_lstrip();
    test_rstrip();
    test_strip();
    test_check_exit();

    clock_t end = clock();

    double time = ((double) end - begin) / CLOCKS_PER_SEC * 1000;

    printf("\n%g ms elapsed\n\n", time);

    return 0;
}