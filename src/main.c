#include <stdio.h>

#include "str.h"

int main(int argc, char* argv[]) {
    String astring;
    create_string_from_str(&astring, "Hello, world!\n");

    insert_char(&astring, 3, '#');
    s_insert_string(&astring, 8, "(My GOD)");

    print_string(&astring);

    return 0;
}
