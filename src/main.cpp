#include <stdio.h>

#include "onegin.h"
#include "myqsort.h"
#include "sorttesting.h"
#include "mystring.h"
#include "config.h"

int main(int argc, const char *argv[])
{
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
        //TODO adequate error management

        printf("Some error occurred!\n");
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
        printf("Sorry, not implented yet!\n");

        //my_sort(text.line_array,
        //        text.nLines,
        //        sizeof(text.line_array[0]),
        //        0,
        //        text.nLines - 1,
        //        line_end_cmp,
        //        0);
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
