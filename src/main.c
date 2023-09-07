#include <stdio.h>

#include "str.h"

int main(int argc, char* argv[]) {
    String* str = str_new();
    String* other = str_new();

    s_append_string(str, "thisisthelimitofthisprogram");
    s_append_string(other, ", well, kinda anyway, i hope a "
        "new allocation method works\n");

    for(int i = 0; i < 1000; i++)
        append_string(str, other);

    free_str(other);

    print_string(str);

    return 0;
}
