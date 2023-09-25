#include <stdio.h>

#include "str.h"

int main(int argc, char* argv[]) {
    String astring;
    create_string_from_str(&astring, "Hello, world!\n");

    replace_char_at(&astring, 7, 'g');

    print_string(&astring);

    return 0;
}
