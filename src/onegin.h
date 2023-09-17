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

struct TextFromFile
{
    const char *name = NULL;
    char **text = NULL;         //< массив строк, из которых состоял текст файла
    unsigned long nLines = 0;   //< кол-во строк в файле, aka размер text[]
};

struct Text
{
    char **text;
    size_t nLines;
};

//---

TextFromFile read_text_from_file(const char *file_name, ErrorCodes *err = NULL);

char *read_file_to_buf(const char *file_name, off_t file_size, ErrorCodes *err);

Text *parse_buf_to_text(char *buf, off_t file_size);

void destroy_Text(Text *text);

void realloc_text(char ***text_p, size_t *curr_text_size_p, size_t* free_place_p);

void print_file_text( TextFromFile file );

off_t get_file_size(const char *file_name);

//! @brief Reads one line from stream WITHOUT '\n'!
char *read_line(FILE *stream);

#endif
