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

//--- sorting

// Обёртка для тестов, чтобы сигнатура совпадала с сигнатурой библиотечного qsort()
void my_sort_for_testing(   void * first,
                size_t number,
                size_t size,
                int ( * comparator ) ( const void *, const void * ) );

/*
    Важное примечание:
    все функции блока сортировки получают один и тот же arr, n_memb, memb_size,
    а ограничение области, в которой ф-я должна что-то сделать, достигается за счет
    указания left и rigth, которые являются ОБА включительными
*/
void my_sort( void *arr,
                size_t n_memb,
                size_t memb_size,
                size_t left,
                size_t right,
                int (*cmp)(const void *, const void *),
                int do_print = 0 );

size_t partition(   void *arr,
                    size_t n_memb,
                    size_t memb_size,
                    size_t left,
                    size_t right,
                    int (*cmp)(const void *, const void *),
                    int do_print );

void work_with_equal_elems( void *arr,
                            size_t n_memb,
                            size_t memb_size,
                            size_t *p_left,
                            size_t *p_right,
                            size_t middle,
                            int (*cmp)(const void *, const void *),
                            int do_print );

// использовать что-то типа in32_t как буфер, и копировать через него
//(а потом меньше и меньше тип, например char)
void swap( void *a, void *b, size_t memb_size);

int line_start_cmp( const void *line1, const void *line2 );

void print_my_sort_int__(   int *arr,
                            size_t n_memb,
                            size_t left,
                            size_t right,
                            size_t middle);

//---

size_t find_maximum_elem_width(const int *arr, size_t n_memb);

size_t find_num_width(int num);

#endif
