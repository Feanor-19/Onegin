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
    FileBuf file_buf = read_file_to_buf(
        !is_str_empty(cfg.data_source) ? cfg.data_source : "input.txt",
        &err
    );
    if (err != ERROR_NO)
    {
        print_error_message(err);
        return 0;
    }

    Text text_original = parse_buf_to_text(file_buf);

    Text text = text_copy(text_original);

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
        print_text_to_file(cfg.output_destination, text, cfg.do_print_addresses, &err);
        if (err != ERROR_NO)
        {
            print_error_message(err);
            return 0;
        }
    }
    else
    {
        print_text(text, cfg.do_print_addresses);
    }

    print_text_to_file("original_text.txt", text_original, cfg.do_print_addresses, &err);
    if (err != ERROR_NO)
    {
        print_error_message(err);
        return 0;
    }

    buf_free(&file_buf);

    text_free(&text);
    text_free(&text_original);

    return 0;
}
