#include "sorttesting.h"

#include <time.h>

int test_int_sort(  void (*sort1)(  void *arr,
                                    size_t n_memb,
                                    size_t memb_size,
                                    size_t left,
                                    size_t right,
                                    int (*cmp1)(const void *, const void *) ),
                    void (*sort2)(  void *arr,
                                    size_t n_memb,
                                    size_t memb_size,
                                    size_t left,
                                    size_t right,
                                    int (*cmp1)(const void *, const void *) ),
                    size_t n_tests, size_t test_size)
{
    size_t not_passed = 0;

    int *data1 = (int *) calloc(test_size, sizeof(int));
    int *data2 = (int *) calloc(test_size, sizeof(int));

    for (size_t ind = 0; ind < n_tests; ind++)
    {
        fill_rand_int_arr(data1, test_size);
        fill_rand_int_arr(data2, test_size);

        sort1(data1, test_size, sizeof(int), 0, test_size - 1, cmp_int_for_testing);

    }

    free(data1);
    free(data2);

    return not_passed;
}

void fill_rand_int_arr(int *arr, size_t arr_size)
{

}

int cmp_int_for_testing(const void *a, const void *b)
{
    return *((const int *) a) - *((const int *) b);
}
