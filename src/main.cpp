#include <stdio.h>

#include "onegin.h"
#include "mystring.h"

int main()
{
    printf("Enter file's name:\n");
    char *file_name = read_line(stdin);

    printf("Entered file name: <%s>\n", file_name);

    ReadFile file = read_file(file_name);

    print_file_text(file);

    return 0;
}
