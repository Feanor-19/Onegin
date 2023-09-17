#ifndef MYQSORT_H
#define MYQSORT_H

#include <stdlib.h>

// Обёртка для тестов, чтобы сигнатура совпадала с сигнатурой библиотечного qsort()
void my_sort_for_testing(   void * first,
                size_t number,
                size_t size,
                int ( * comparator ) ( const void *, const void * ) );

/*
    Важное примечание:
    все функции блока сортировки получают один и тот же arr, n_memb, memb_size,
    а ограничение области, в которой ф-я должна что-то сделать, достигается за счет
    указания left и rigth, которые являются ОБА включительными
*/
void my_sort( void *arr,
                size_t n_memb,
                size_t memb_size,
                size_t left,
                size_t right,
                int (*cmp)(const void *, const void *),
                int do_print = 0 );

size_t partition(   void *arr,
                    size_t n_memb,
                    size_t memb_size,
                    size_t left,
                    size_t right,
                    int (*cmp)(const void *, const void *),
                    int do_print );

void work_with_equal_elems( void *arr,
                            size_t n_memb,
                            size_t memb_size,
                            size_t *p_left,
                            size_t *p_right,
                            size_t middle,
                            int (*cmp)(const void *, const void *),
                            int do_print );

// использовать что-то типа in32_t как буфер, и копировать через него
//(а потом меньше и меньше тип, например char)
void swap( void *a, void *b, size_t memb_size);

int line_start_cmp( const void *line1, const void *line2 );

void print_my_sort_int__(   int *arr,
                            size_t n_memb,
                            size_t left,
                            size_t right,
                            size_t middle);

//---

size_t find_maximum_elem_width(const int *arr, size_t n_memb);

size_t find_num_width(int num);

#endif
