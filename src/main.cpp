#include <stdio.h>

#include "onegin.h"
#include "mystring.h"

int main()
{
    printf("Enter file's name:\n");
    char *file_name = read_line(stdin);

    printf("Entered file name: <%s>\n", file_name);

    ErrorCodes err = ERROR_NO;
    ReadFile file = read_file(file_name, &err); // какого фига не работает без второго аргумента по умолч

    if (err == ERROR_NO) print_file_text(file);
    else printf("Some error occured!\n");

    return 0;
}
