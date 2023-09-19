#ifndef ONEGIN_H
#define ONEGIN_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

enum ErrorCodes
{
    ERROR_NO        = 0,
    ERROR_FILE_SIZE = 1,
    ERROR_OPEN_FILE = 2,
    ERROR_READ_FILE = 3,
};

struct Text
{
    char **line_array = NULL;         //< массив адресов строк
    unsigned long nLines = 0;   //< кол-во строк в файле, aka размер text[]
};

struct FileBuf
{
    char *buf = NULL;
    size_t buf_size = 0;
};

//---

Text read_text_from_file(const char *file_name, ErrorCodes *err = NULL);

FileBuf read_file_to_buf(const char *file_name, ErrorCodes *err);

Text parse_buf_to_text(FileBuf file_buf);

void print_file_text( Text text, FILE *stream, int do_print_addresses );

off_t get_file_size(const char *file_name);

void print_error_message( ErrorCodes err );

//! @brief Reads one line from stream WITHOUT '\n'!
char *read_line(FILE *stream);

int cmp_line_beginning( const void *v_line1, const void *v_line2 );

int cmp_line_end( const void *v_line1, const void *v_line2 );

#endif
