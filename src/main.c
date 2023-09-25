#include <stdio.h>

#include "str.h"

int main(int argc, char* argv[]) {
    String astring;
    create_string_from_str(&astring, "Hello, world!\n");

    remove_span(&astring, 4, 7);

    print_string(&astring);

    return 0;
}
