#include <stdio.h>

#include "str.h"

int main(int argc, char* argv[]) {
    String astring;
    create_string_from_str(&astring, "%d %d %d\n");

    replace_all_found_str(&astring, "%d", "booobooo");

    print_string(&astring);

    return 0;
}
