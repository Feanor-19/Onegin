#include "myqsort.h"

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include "mystring.h"

void my_sort_for_testing(
                void * first,
                size_t number,
                size_t size,
                int ( * comparator ) ( const void *, const void * ) )
{
    assert(first);
    assert(comparator);

    my_sort(first, number, size, 0, number - 1, comparator, 0);
}

inline void *get_elem_pnt(size_t ind, void *arr, size_t memb_size)
{
    assert(arr);
    return (void *) (( (char *) arr ) + memb_size*ind);
}

inline int compare(   void *arr,
                        size_t memb_size,
                        size_t ind_a,
                        size_t ind_b,
                        int (*cmp)(const void *, const void *),
                        int do_print)
{
    assert(arr);

    assert( get_elem_pnt(ind_a, arr, memb_size) );
    assert( get_elem_pnt(ind_b, arr, memb_size) );

    if (do_print) printf("ind_a = %u, ind_b = %u\n", ind_a, ind_b);

    return cmp( get_elem_pnt(ind_a, arr, memb_size), get_elem_pnt(ind_b, arr, memb_size) );
}

void my_sort( void *arr,
                size_t n_memb,
                size_t memb_size,
                size_t left,
                size_t right,
                int (*cmp)(const void *, const void *),
                int do_print)
{
    assert(arr);
    assert(cmp);

    if (n_memb == 1) return;

    if (right - left == 1) // простой частный случай
    {
        if ( compare(arr, memb_size, left, right, cmp, do_print) > 0 )
        {
            swap( get_elem_pnt(left, arr, memb_size), get_elem_pnt(right, arr, memb_size), memb_size );

            if (do_print) printf("Simple swap case\n");
            if (do_print) print_my_sort_int__((int *) arr, n_memb, left, right, n_memb+1);
        }
    }
    else
    {

        if (do_print) printf("Entering partition from index %u to index %u\n", left, right);
        size_t mid = partition(arr, n_memb, memb_size, left, right, cmp, do_print);
        if (do_print) printf("Left partition from index %u to index %u, mid = %u\n", left, right, mid);

        if ( mid > left )
        {
            if (do_print) printf("!Entering sorting from index %u to index %u\n", left, mid);
            my_sort(arr, n_memb, memb_size, left, mid, cmp, do_print);
            if (do_print) printf("!Leaving sorting from index %u to index %u\n", left, mid);
        }
        if ( (right > mid + 1) )
        {
            if (do_print) printf("@Entering sorting from index %u to index %u\n", mid + 1, right);
            my_sort(arr, n_memb, memb_size, mid + 1, right, cmp, do_print);
            if (do_print) printf("@Leaving sorting from index %u to index %u\n", mid + 1, right);
        }
    }

}

size_t partition(   void *arr,
                    size_t n_memb,
                    size_t memb_size,
                    size_t left,
                    size_t right,
                    int (*cmp)(const void *, const void *),
                    int do_print)
{
    assert(arr);
    assert(cmp);

    size_t middle = (right + left) / 2;

    if (do_print) print_my_sort_int__((int *) arr, n_memb, left, right, middle);

    while( left < right )
    {

        if ( compare(arr, memb_size, left, right, cmp, do_print) == 0 )
        {
            work_with_equal_elems(arr, n_memb, memb_size, &left, &right, middle, cmp, do_print);
        }

        while ( compare(arr, memb_size, left, middle, cmp, do_print) < 0 )
        {
            left++;

            if (left == right)
            {
                return left;
            }

            if ( compare(arr, memb_size, left, right, cmp, do_print) == 0 )
            {
                work_with_equal_elems(arr, n_memb, memb_size, &left, &right, middle, cmp, do_print);
            }

            if (do_print) print_my_sort_int__((int *) arr, n_memb, left, right, middle);
        }

        while ( compare(arr, memb_size, middle, right, cmp, do_print) < 0 )
        {
            right--;

            if ( left == right )
            {
                return left;
            }

            if ( compare(arr, memb_size, left, right, cmp, do_print) == 0 )
            {
                work_with_equal_elems(arr, n_memb, memb_size, &left, &right, middle, cmp, do_print);
            }

            if (do_print) print_my_sort_int__((int *) arr, n_memb, left, right, middle);
        }

        swap( get_elem_pnt(left, arr, memb_size), get_elem_pnt(right, arr, memb_size), memb_size );
        if (do_print) printf("Swap done: at index %u exchanged with at index %u\n", left, right);

        if (do_print) print_my_sort_int__((int *) arr, n_memb, left, right, middle);

        if (left == middle) middle = right;
        else if (right == middle) middle = left;

        if (right - left == 1) return left;
        //left++;
        //right--;

        if (do_print) print_my_sort_int__((int *) arr, n_memb, left, right, middle);

    }

    return left;
}

void work_with_equal_elems( void *arr,
                            size_t n_memb,
                            size_t memb_size,
                            size_t *p_left,
                            size_t *p_right,
                            size_t middle,
                            int (*cmp)(const void *, const void *),
                            int do_print )
{
    if (do_print) print_my_sort_int__((int *) arr, n_memb, *p_left, *p_right, middle);

    if ( compare(arr, memb_size, *p_left, middle, cmp, do_print) >= 0 )
    {
        if (do_print) printf("Elements at left and at right are equal, swapping is unnecessary. "
            "Also element at left >= at middle, so we need to swap it later, "
            "and elem at right is already good. "
            "Moving right pointer in order to avoid endless cycle.\n");
        (*p_right)--;
    }
    else
    {
        if (do_print) printf("Elements at left and at right are equal, swapping is unnecessary. "
            "Also element at right < at middle, so we need to swap it later, "
            "and elem at left is already good. "
            "Moving left pointer in order to avoid endless cycle.\n");
        (*p_left)++;
    }
}


/*
    define ниже нужен только для swap, и это мотивация объявить его именно здесь
*/

#define swap__(__type__) while ( left_bytes >= sizeof(__type__) )       \
    {                                                                   \
        __type__ buf = *( (__type__ *) a );                             \
        *( (__type__ *) a ) = *( (__type__ *) b );                      \
        *( (__type__ *) b ) = buf;                                      \
                                                                        \
        a = ( (__type__ *) a ) + 1;                                     \
        b = ( (__type__ *) b ) + 1;                                     \
                                                                        \
        left_bytes -= sizeof(__type__);                                 \
    }

void swap( void *a, void *b, size_t memb_size )
{
    assert(a);
    assert(b);

    size_t left_bytes = memb_size;

    swap__(int64_t);

    swap__(int32_t);

    swap__(int16_t);

    swap__(int8_t);

    swap__(char);

}

int line_start_cmp( const void *v_line1, const void *v_line2 )
{
    assert(v_line1 != NULL);
    assert(v_line2 != NULL);

    const char *line1 = *((const char * const *) v_line1);
    const char *line2 = *((const char * const *) v_line2);

    //printf("~~~\nv_line1 = %p\nline1 = %p\nv_line2 = %p\nline2 = %p\n~~~\n", v_line1, line1, v_line2, line2);

    return my_strcmp(line1, line2);
}


inline void put_n_spaces(size_t n)
{
    while(n--) putchar(' ');
}

void print_my_sort_int__(   int *arr,
                            size_t n_memb,
                            size_t left,
                            size_t right,
                            size_t middle)
{
    assert(arr);

    size_t width = find_maximum_elem_width(arr, n_memb);

    size_t curr_space = 0;
    for (size_t ind = 0; ind < n_memb; ind++)
    {
        curr_space = width + 5;
        if (ind == left)    curr_space--;
        if (ind == right)   curr_space--;
        if (ind == middle)  curr_space-=2;

        curr_space -= find_num_width(arr[ind]);
        put_n_spaces(curr_space);

        if (ind == left)    putchar('<');
        if (ind == middle)  putchar('[');
        printf("%d", arr[ind]);
        if (ind == middle)  putchar(']');
        if (ind == right)   putchar('>');

    }

    printf("\n");
}

size_t find_maximum_elem_width(const int *arr, size_t n_memb)
{
    assert(arr != NULL);

    size_t ans = 0;
    for (size_t ind = 0; ind < n_memb; ind++)
    {
        size_t res = find_num_width( arr[ind] );
        if (res > ans) ans = res;
    }
    return ans;
}

size_t find_num_width(int num)
{
    size_t res = 0;

    if (num < 0)
    {
        res++;
        num = -num;
    }

    while( num > 0 )
    {
        res++;
        num = num/10;
    }

    return res;
}
