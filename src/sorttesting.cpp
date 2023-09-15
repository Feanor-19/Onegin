#include "sorttesting.h"

#include <time.h>
#include <assert.h>

int test_int_sort(  void sort1( void * first,
                                size_t number,
                                size_t size,
                                int ( * comparator ) ( const void *, const void * )),
                    void sort2( void * first,
                                size_t number,
                                size_t size,
                                int ( * comparator ) ( const void *, const void * )),
                    size_t n_tests, size_t test_size)
{
    assert(sort1);
    assert(sort2);

    size_t not_passed = 0;

    int *data1 = (int *) calloc(test_size, sizeof(int));
    int *data2 = (int *) calloc(test_size, sizeof(int));

    for (size_t ind = 0; ind < n_tests; ind++)
    {
        fill_rand_int_arr(data1, test_size);
        fill_rand_int_arr(data2, test_size);

        sort1(data1, test_size, sizeof(data1[0]), cmp_int_for_testing);
        sort2(data1, test_size, sizeof(data1[0]), cmp_int_for_testing);

        if ( !are_data_sets_equal(data1, data2, test_size) ) not_passed++;
    }

    free(data1);
    free(data2);

    return not_passed;
}

void fill_rand_int_arr(int *arr, size_t arr_size)
{
    assert(arr);

    srand( time(NULL) );

    for (size_t ind = 0; ind < arr_size; ind++)
    {
        arr[ind] = rand();
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
