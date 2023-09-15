#include <stdio.h>

#include "onegin.h"
#include "mystring.h"

int cmp_int(const void *a, const void *b);

int main()
{
    /* //ONEGIN
    printf("Enter file's name:\n");
    char *file_name = read_line(stdin);

    printf("Entered file name: <%s>\n", file_name);

    ErrorCodes err = ERROR_NO;
    TextFromFile text = read_text_from_file(file_name, &err); // какого фига не работает без второго аргумента по умолч

    if (err == ERROR_NO) print_file_text(text);
    else printf("Some error occured!\n");
    */

    // TODO std_qsort_wrap, потому что отличается сигнатура у стандартного и моего,
    // а чтобы запихнуть в sorttesting, нужно стандартный привести к моему виду
    // или быстро переделать свою сигнатуру....

    int arr[] = { 5, 2, 15, 3, 1, 16, 10, 5, 10, 3, 4, 12, 6, 6, 22, 20 };
    size_t arr_len = sizeof(arr)/sizeof(arr[0]);
    my_sort(arr, arr_len, sizeof(arr[0]), cmp_int);

    return 0;
}

int cmp_int(const void *a, const void *b)
{
    int i_a = *((const int *) a);
    int i_b = *((const int *) b);
    return ( i_a > i_b ? 1 : (i_a == i_b ? 0 : -1) );
}
