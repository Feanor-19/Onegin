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
        int not_passed = test_int_sort(qsort, my_sort_for_testing, 10000, 20, 30);
        if (not_passed != 0) printf("The following number of tests failed: %d\n", not_passed);
        else printf("All tests are passed!\n");

        return not_passed;
    }

    ErrorCodes err = ERROR_NO;
    FileBuf file_buf = read_file_to_buf((!is_str_empty(cfg.data_source) ? cfg.data_source : "input.txt"), &err);
    if (err != ERROR_NO)
    {
        print_error_message(err);
        return 0;
    }

    Text text = parse_buf_to_text(file_buf);

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

    buf_free(&file_buf);

    text_free(&text);

    return 0;
}
