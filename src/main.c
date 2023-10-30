#include <stdio.h>

#include "str.h"

int main(int argc, char* argv[]) {
    String str;
    create_with_format(&str, "%d\n", -10509992);

    print_string(&str);

    destroy_str(&str);

    return 0;
}
