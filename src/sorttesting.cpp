#include "sorttesting.h"

#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

int test_int_sort(  void sort1( void * first,
                                size_t number,
                                size_t size,
                                int ( * comparator ) ( const void *, const void * )),
                    void sort2( void * first,
                                size_t number,
                                size_t size,
                                int ( * comparator ) ( const void *, const void * )),
                    size_t n_tests, size_t test_size, int max_memb)
{
    assert(sort1);
    assert(sort2);

    const int DO_PRINT_DATA = 0;

    size_t not_passed = 0;

    int *data1 = (int *) calloc(test_size, sizeof(int));
    int *data2 = (int *) calloc(test_size, sizeof(int));

    if (!DO_PRINT_DATA) printf("Testing progress: 00%%");

    for (size_t ind = 0; ind < n_tests; ind++)
    {
        if (!DO_PRINT_DATA) printf("\b\b\b%02u%%", (ind+1)*100/n_tests);

        fill_rand_int_arr(data1, test_size, max_memb);
        memcpy(data2, data1, test_size*sizeof(int));

        if (n_tests < 10 && DO_PRINT_DATA)
        {
            printf("data1 : ");
            print_int_arr(data1, test_size);
            printf("data2 : ");
            print_int_arr(data2, test_size);
        }

        sort1(data1, test_size, sizeof(data1[0]), cmp_int_for_testing);
        sort2(data2, test_size, sizeof(data2[0]), cmp_int_for_testing);

        if (n_tests < 10 && DO_PRINT_DATA)
        {
            printf("sorted data1 : ");
            print_int_arr(data1, test_size);
            printf("sorted data2 : ");
            print_int_arr(data2, test_size);
        }

        if ( !are_data_sets_equal(data1, data2, test_size) ) not_passed++;
    }

    free(data1);
    free(data2);

    printf("\n");

    return not_passed;
}

void fill_rand_int_arr(int *arr, size_t arr_size, int max_memb)
{
    assert(arr);

    srand( time(NULL) );

    for (size_t ind = 0; ind < arr_size; ind++)
    {
        arr[ind] = rand() % max_memb + 1;
    }
}

int are_data_sets_equal(const void *data1, const void *data2, size_t n_bytes)
{
    assert(data1);
    assert(data2);

    // int выбран т.к. с ним сравнение должно быть быстрее всего?
    const int *i_data1 = (const int *) data1;
    const int *i_data2 = (const int *) data2;

    while(n_bytes >= sizeof(int))
    {
        if ( *i_data1 != *i_data2 ) return 0;

        i_data1++;
        i_data2++;

        n_bytes -= sizeof(int);
    }

    const char *c_data1 = (const char *) i_data1;
    const char *c_data2 = (const char *) i_data2;

    while(n_bytes--)
    {
        if (*c_data1 != *c_data2) return 0;

        c_data1++;
        c_data2++;
    }

    return 1;

}

int cmp_int_for_testing(const void *a, const void *b)
{
    assert(a);
    assert(b);

    return *((const int *) a) - *((const int *) b);
}

void print_int_arr(int *arr, size_t arr_len)
{
    for (size_t ind = 0; ind < arr_len; ind++) printf("%d ", arr[ind]);
    printf("\n");
}
