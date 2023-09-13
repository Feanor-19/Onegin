#include "onegin.h"

#include <assert.h>
#include <ctype.h>
#include <stdint.h>

#include "mystring.h"

TextFromFile read_text_from_file(const char *file_name, ErrorCodes *err)
{
    assert(file_name);

    TextFromFile read_file = {};

    off_t file_size = get_file_size(file_name);
    if (file_size == -1) {
        *err = ERROR_FILE_SIZE;
        return read_file;
    }

    char *buf = read_file_to_buf(file_name, file_size, err);
    if (buf == NULL) return read_file;

    printf("! buf: <%s>\n", buf);

    Text *text_p = parse_buf_to_text(buf, file_size);

    read_file.name = file_name;
    read_file.text = text_p->text;
    read_file.nLines = text_p->nLines;

    free(buf);

    destroy_Text(text_p);

    return read_file;
}

char *read_file_to_buf(const char *file_name, off_t file_size, ErrorCodes *err)
{
    FILE *file_p = fopen(file_name, "r");
    if (file_p == NULL) {
        *err = ERROR_OPEN_FILE;
        return NULL;
    }

    char *buf = (char *) calloc( file_size + 1, sizeof(char) );

    fread(buf, sizeof(char), file_size, file_p);
    if ( ferror(file_p) != 0 )
    {
        *err = ERROR_READ_FILE;
        free(buf);
        return NULL;
    }

    fclose(file_p);
    file_p = NULL;

    return buf;
}

Text *parse_buf_to_text(char *buf, off_t file_size)
{
    assert(buf);

    const size_t DEFAULT_TEXT_SIZE = 10;
    assert(DEFAULT_TEXT_SIZE > 2);

    char **text = (char **) calloc(DEFAULT_TEXT_SIZE, sizeof(char *));

    size_t free_place_in_text = DEFAULT_TEXT_SIZE;
    size_t curr_text_size = DEFAULT_TEXT_SIZE;

    text[0] = buf;
    free_place_in_text--;

    size_t line = 1;
    for (off_t ind = 0; ind < file_size - 1; ind++)
    {
        if ( buf[ind] == '\n' )
        {
            buf[ind] = '\0';
            text[line++] = &buf[ind + 1];
            free_place_in_text--;

            if (free_place_in_text == 0)
            {
                realloc_text(&text, &curr_text_size, &free_place_in_text);
            }
        }
    }

    printf("Info: curr_text_size = %u, free_place_in_text = %u\n", curr_text_size, free_place_in_text);

    Text *text_p = (Text *) calloc(1, sizeof(Text));
    text_p->text = text;
    text_p->nLines = line;

    return text_p;
}

void destroy_Text(Text *text_p)
{
    assert(text_p);

    if (text_p->text != NULL) free(text_p->text);
    free(text_p);
}

void realloc_text(char ***text_p, size_t *curr_text_size_p, size_t* free_place_p)
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

void print_file_text( TextFromFile file )
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

    if ( str[read_bytes - 2] == '\n' ) str[read_bytes - 2] = '\0';

    return str;
}

//--- sorting

void my_sort(   void *arr,
                size_t n_memb,
                size_t memb_size,
                size_t left,
                size_t rigth,
                int (*cmp)(const void *, const void *) )
{

}

size_t partition( void *arr, size_t n_memb, size_t memb_size, size_t left, size_t rigth)
{

}

/*
    define ниже нужен только для swap, и это мотивация объявить его именно здесь
*/

#define swap__(__type__) while ( left_bytes >= sizeof(__type__) )    \
    {                                                           \
        __type__ buf = *( (__type__ *) a );                       \
        *( (__type__ *) a ) = *( (__type__ *) b );                \
        *( (__type__ *) b ) = buf;                               \
                                                                \
        a = ( (__type__ *) a ) + 1;                              \
        b = ( (__type__ *) b ) + 1;                              \
                                                                \
        left_bytes -= sizeof(__type__);                          \
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

int line_start_cmp( const void *line1, const void *line2 )
{

}

void print_my_sort( void *arr,
                    size_t n_memb,
                    size_t memb_size,
                    size_t left,
                    size_t right,
                    PrintSortTypes type)
{

}
