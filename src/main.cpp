#include <stdio.h>

#include "onegin.h"
#include "mystring.h"

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

    char str1[10] = "hello";
    char str2[10] = "world";
    swap( str1, str2, sizeof(char)*10 );
    printf("after swap a = %s, b = %s\n", str1, str2);

    return 0;
}
