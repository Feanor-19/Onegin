#ifndef SORTTESTING_H
#define SORTTESTING_H

#include <stdlib.h>

int test_int_sort(  void sort1( void * first,
                                size_t number,
                                size_t size,
                                int ( * comparator ) ( const void *, const void * )),
                    void sort2( void * first,
                                size_t number,
                                size_t size,
                                int ( * comparator ) ( const void *, const void * )),
                    size_t n_tests, size_t test_size, int max_memb = RAND_MAX);

void fill_rand_int_arr(int *arr, size_t arr_size, int max_memb = RAND_MAX);

// @brief Returns 1 if data sets are equal, 0 otherwise.
int are_data_sets_equal(const void *data1, const void *data2, size_t n_bytes);

int cmp_int_for_testing(const void *a, const void *b);

void print_int_arr(int *arr, size_t arr_len);

#endif
