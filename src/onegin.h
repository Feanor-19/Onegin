#ifndef ONEGIN_H
#define ONEGIN_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

struct ReadFile
{
    const char *name = NULL;
    char **text = NULL;         //< массив строк, из которых состоял текст файла
    unsigned long nLines = 0;   //< кол-во строк в файле, aka размер text[]
};

//---

ReadFile read_file(const char *file_name);

void print_file_text( ReadFile file );

off_t get_file_size(const char *file_name);

//! @brief Reads one line from stream WITHOUT '\n'!
char *read_line(FILE *stream);

#endif
