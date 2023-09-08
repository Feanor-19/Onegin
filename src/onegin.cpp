#include "onegin.h"

#include <assert.h>
#include <ctype.h>

#include "mystring.h"

#define MAX_NUMBER_OF_LINES 100

ReadFile read_file(const char *file_name)
{
    assert(file_name);

    ReadFile read_file = {};

    off_t file_size = get_file_size(file_name);
    if (file_size == -1) return read_file; //!!! TODO ERORR CODES !!!

    char *buf = (char *) calloc( file_size + 1, sizeof(char) );

    FILE *file_p = fopen(file_name, "r");
    if (file_p == NULL) return read_file; //!!! TODO ERORR CODES !!!

    fread(buf, sizeof(char), file_size, file_p);
    //!!! TODO FEOF FERROR !!!

    fclose(file_p);
    file_p = NULL;

    printf("! buf: <%s>\n", buf);

    char *text[MAX_NUMBER_OF_LINES] = {};

    text[0] = buf;
    size_t line = 1;
    for (off_t ind = 0; ind < file_size - 1; ind++)
    {
        if ( buf[ind] == '\n' )
        {
            buf[ind] = '\0';
            text[line++] = &buf[ind + 1];
        }
    }

    read_file.name = file_name;
    read_file.text = text;
    read_file.nLines = line;

    return read_file;

    free(buf);
}

void print_file_text( ReadFile file )
{
    printf("Here is the text in file %s:\n", file.name);

    for (unsigned long ind = 0; ind < file.nLines; ind++ )
    {
        printf("Line at address %p : <%s>\n", &file.text[ind], file.text[ind]);
    }

    printf("The END!\n");
}

//! @brief Returns file's (of name 'file_name') size or -1 in case of error.
off_t get_file_size(const char *file_name)
{
    assert(file_name);

    struct stat st_buf = {};

    if ( stat(file_name, &st_buf) == -1) return -1;

    return st_buf.st_size;
}

char *read_line(FILE *stream)
{
    assert(stream);

    const size_t START_STR_SIZE = 16;

    char *str = (char *) calloc( START_STR_SIZE, sizeof(char) );
    if (str == NULL) return NULL;

    size_t curr_size = START_STR_SIZE;
    size_t read_bytes = my_getline(&str, &curr_size, stream);

    //printf("! read_bytes = %u\n", read_bytes);

    //printf("!!! %d, %d\n", str[read_bytes - 2], str[read_bytes - 1]);

    if ( str[read_bytes - 2] == '\n' ) str[read_bytes - 2] = '\0';

    return str;
}
