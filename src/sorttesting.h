#ifndef SORTTESTING_H
#define SORTTESTING_H

#include <stdlib.h>

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
                    size_t n_tests, size_t test_size);

void fill_rand_int_arr(int *arr, size_t arr_size);

int cmp_int_for_testing(const void *a, const void *b);

#endif
