#include <stdio.h>

#include "onegin.h"
#include "myqsort.h"
#include "sorttesting.h"
#include "mystring.h"
#include "config.h"

int main(int argc, const char *argv[])
{

    const char str1[] = "But sudden fear assailed Tattiana,";
    const char str2[] = "Tattiana";

    const char *arr[] = {str1, str2};

    //printf("&&& %d\n", my_strcmp(str1, str2));
    //printf("!!! %d\n", cmp_line_end(&arr[0], &arr[1]));

    //printf("%c\n", *( str1 + skip_not_alnum_from_end(str1) + 1 ));

    Config cfg = get_config(argc, argv);

    if (cfg.do_tests)
    {
        // TODO Ввод параметров тестирования?

        int not_passed = test_int_sort(qsort, my_sort_for_testing, 10000, 20, 30);
        if (not_passed != 0) printf("The following number of tests failed: %d\n", not_passed);
        else printf("All tests are passed!\n");

        return not_passed;
    }

    ErrorCodes err = ERROR_NO;
    Text text = read_text_from_file( (!is_str_empty(cfg.data_source) ? cfg.data_source : "input.txt") , &err);
    if (err != ERROR_NO)
    {
        switch (err)
        {
        case ERROR_OPEN_FILE:
            fprintf(stderr, "ERROR: Can't open file!\n");
            break;
        case ERROR_FILE_SIZE:
            fprintf(stderr, "ERROR: Can't get file size!\n");
            break;
        case ERROR_READ_FILE:
            fprintf(stderr, "ERROR: Can't read file!\n");
            break;
        case ERROR_NO:
            assert(0 && "Unreacheable line reached!");
            break;
        default:
            fprintf(stderr, "ERROR: Unknown error occurred!\n");
            break;
        }

        return 0;
    }

    if (cfg.do_sort_begin)
    {
        my_sort(text.line_array,
                text.nLines,
                sizeof(text.line_array[0]),
                0,
                text.nLines - 1,
                cmp_line_beginning,
                0);
    }
    else if (cfg.do_sort_end)
    {
        my_sort(text.line_array,
                text.nLines,
                sizeof(text.line_array[0]),
                0,
                text.nLines - 1,
                cmp_line_end,
                0);
    }

    if (!is_str_empty(cfg.output_destination))
    {
        FILE *file_p = fopen(cfg.output_destination, "w");

        if (file_p == NULL)
        {
            printf("Can't open file <%s>!\n", cfg.output_destination);
            return 0;
        }

        print_file_text(text, file_p, cfg.do_print_addresses);

        fclose(file_p);
    }
    else
    {
        print_file_text(text, stdin, cfg.do_print_addresses);
    }

    return 0;
}
