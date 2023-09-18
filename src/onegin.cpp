#include "onegin.h"

#include <assert.h>
#include <ctype.h>
#include <stdint.h>

#include "mystring.h"

Text read_text_from_file(const char *file_name, ErrorCodes *err)
{
    assert(file_name);

    FileBuf file_buf = read_file_to_buf(file_name, err);
    if (*err != ERROR_NO)
    {
        Text text = {};
        return text;
    }

    Text text = parse_buf_to_text(file_buf);

    return text;
}

FileBuf read_file_to_buf(const char *file_name, ErrorCodes *err)
{
    FileBuf file_buf = {};

    off_t file_size = get_file_size(file_name);
    if (file_size == -1) {
        *err = ERROR_FILE_SIZE;
        return file_buf;
    }

    FILE *file_p = fopen(file_name, "r");
    if (file_p == NULL) {
        *err = ERROR_OPEN_FILE;
        return file_buf;
    }

    char *buf = (char *) calloc( file_size + 1, sizeof(char) );

    size_t buf_size = fread(buf, sizeof(char), file_size, file_p);
    if ( ferror(file_p) != 0 )
    {
        *err = ERROR_READ_FILE;
        free(buf);
        return file_buf;
    }

    file_buf.buf = buf;
    file_buf.buf_size = buf_size;

    fclose(file_p);
    file_p = NULL;

    return file_buf;
}

Text parse_buf_to_text(FileBuf file_buf)
{
    const size_t DEFAULT_TEXT_SIZE = 10;
    assert(DEFAULT_TEXT_SIZE > 2);

    char **line_array = (char **) calloc(DEFAULT_TEXT_SIZE, sizeof(char *));

    size_t free_place_in_line_arr = DEFAULT_TEXT_SIZE;
    size_t curr_text_size = DEFAULT_TEXT_SIZE;

    line_array[0] = file_buf.buf;
    free_place_in_line_arr--;

    size_t line = 1;
    for (size_t ind = 0; ind < file_buf.buf_size - 1; ind++)
    {
        if ( file_buf.buf[ind] == '\n' )
        {
            file_buf.buf[ind] = '\0';
            line_array[line++] = &file_buf.buf[ind + 1];
            free_place_in_line_arr--;

            if (free_place_in_line_arr == 0)
            {
                realloc_line_array(&line_array, &curr_text_size, &free_place_in_line_arr);
            }
        }
    }

    //printf("Info: curr_text_size = %u, free_place_in_line_arr = %u\n", curr_text_size, free_place_in_line_arr);

    Text text = {};
    text.line_array = line_array;
    text.nLines = line;

    return text;
}

void realloc_line_array(char ***text_p, size_t *curr_text_size_p, size_t* free_place_p)
{
    size_t old_text_size = *curr_text_size_p;

    *curr_text_size_p = 2 * old_text_size;

    *free_place_p = *curr_text_size_p - old_text_size;

    char **new_text = (char **) calloc( *curr_text_size_p, sizeof(char *) );

    for (size_t ind = 0; ind < old_text_size; ind++)
    {
        new_text[ind] = (*text_p)[ind];
    }

    free(*text_p);

    *text_p = new_text;
}

void print_file_text( Text text, FILE *stream, int do_print_addresses )
{
    for (unsigned long ind = 0; ind < text.nLines; ind++ )
    {
        if (do_print_addresses)
        {
            fprintf(stream, "Line at address %p : <%s>\n", &text.line_array[ind], text.line_array[ind]);
        }
        else
        {
            fprintf(stream, "%s\n", text.line_array[ind]);
        }
    }
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

    if ( str[read_bytes - 2] == '\n' ) str[read_bytes - 2] = '\0';

    return str;
}
