#include <stdio.h>

#include "onegin.h"
#include "mystring.h"

int cmp_int(const void *a, const void *b);

int main()
{
    /*
    printf("Enter file's name:\n");
    char *file_name = read_line(stdin);

    printf("Entered file name: <%s>\n", file_name);

    ErrorCodes err = ERROR_NO;
    TextFromFile text = read_text_from_file(file_name, &err); // какого фига не работает без второго аргумента по умолч

    if (err == ERROR_NO) print_file_text(text);
    else printf("Some error occured!\n");
    */

   /*
    int arr[] = { 5, 2, 15, 3, 1, 16, 10, 5, 10, 3, 4, 12, 6, 6, 22, 20 };
    size_t arr_len = sizeof(arr)/sizeof(arr[0]);
    my_sort(arr, arr_len, sizeof(arr[0]), 0, arr_len - 1, cmp_int);
    */

    /*
    //print sort test
    int arr[] = { 1, 2, 3, 19, 5, 6, 755, 8, 9 };
    print_my_sort_int( arr, sizeof(arr)/sizeof(arr[0]), 2, 6, 4 );

    arr[2] = 755;
    arr[6] = 3;

    print_my_sort_int( arr, sizeof(arr)/sizeof(arr[0]), 3, 7, 5 );

    swap(arr + 2, arr + 5, sizeof(int));

    print_my_sort_int( arr, sizeof(arr)/sizeof(arr[0]), 3, 7, 7 );
    */

    return 0;
}

int cmp_int(const void *a, const void *b)
{
    int i_a = *((const int *) a);
    int i_b = *((const int *) b);
    return ( i_a > i_b ? 1 : (i_a == i_b ? 0 : -1) );
}
