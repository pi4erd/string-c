#include <stdio.h>

#include "str.h"

int main(int argc, char* argv[]) {
    String* str = from_c_str("Hello,,.afhpiushfioushefipdasfhiosdfdho        ");

    for(int i = 0; i < 10000; i++)
        append_char(str, ' ');

    trim_end_string(str);
    reallocate_string_by_size(str);

    print_string(str);

    free_str(str);

    return 0;
}
