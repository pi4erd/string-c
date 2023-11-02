#include <stdio.h>

#include "str.h"

int main(int argc, char* argv[]) {
    String str;
    create_with_format(&str, "Hello\n");

    remove_span(&str, 3, 5);

    print_string(&str);

    destroy_str(&str);

    return 0;
}
